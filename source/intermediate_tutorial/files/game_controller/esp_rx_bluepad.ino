#include <Bluepad32.h>
#include "joy_msg.hpp"
#include "crc8.hpp"

#define IN_BUILT_LED_BLUE 2
#define IN_BUILT_LED_BLUE 2
#define RXD2 16
#define TXD2 17
#define START_BYTE 0xA5

bool connected = false;

namespace BPB {
enum BluePadButtonsMask {
  Cross = 0x1,
  Circle = 0x2,
  Square = 0x04,
  Triangle = 0x08,
  Share = 0x02,
  Power = 0x01,
  Option = 0x04,
  L3 = 0x100,
  R3 = 0x200,
  L1 = 0x10,
  R1 = 0x20,
  Up = 0x01,
  Down = 0x02,
  Left = 0x08,
  Right = 0x04
  // Touch
};
}

ControllerPtr myControllers[BP32_MAX_GAMEPADS];
CRC8 crc(7);
JoyData jdata;
bool isBraked = false;
uint32_t last_transmit = 0;

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  // for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[0] == nullptr) {
      Serial.printf("CALLBACK: Controller is connected, index=%d\n", 0);
      // Additionally, you can get certain gamepad properties like:
      // Model, VID, PID, BTAddr, flags, etc.
      ControllerProperties properties = ctl->getProperties();
      Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                    properties.product_id);
      myControllers[0] = ctl;
      foundEmptySlot = true;
      connected = true;
      digitalWrite(IN_BUILT_LED_BLUE, HIGH);
      ctl->setColorLED(0, 255, 0);
      // break;
    // }
  }
  if (!foundEmptySlot) {
    Serial.println("CALLBACK: Controller connected, but could not found empty slot");
  }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundController = false;

  // for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[0] == ctl) {
      Serial.printf("CALLBACK: Controller disconnected from index=%d\n", 0);
      myControllers[0] = nullptr;
      foundController = true;
      connected = false;
      digitalWrite(IN_BUILT_LED_BLUE, LOW);
      // break;
    // }
  }

  if (!foundController) {
    Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
  }
}

void blinkColorLED(ControllerPtr ctl) {
  static bool isRed = false;
  static uint32_t last_blink = 0;
  uint32_t now = millis();
  if (now - last_blink > 1000) {
    if (isRed) {
      if (isBraked) {
        ctl->setColorLED(255, 0, 255);
      } else {
        ctl->setColorLED(0, 255, 0);
      }
    } else {
      ctl->setColorLED(50, 0, 0);
    }

    isRed = !isRed;
    last_blink = now;
  }
}

void dumpGamepad(ControllerPtr ctl) {
  Serial.printf(
    "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
    "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d bat:%d\n",
    ctl->index(),        // Controller Index
    ctl->dpad(),         // D-pad
    ctl->buttons(),      // bitmask of pressed buttons
    ctl->axisX(),        // (-511 - 512) left X Axis
    ctl->axisY(),        // (-511 - 512) left Y axis
    ctl->axisRX(),       // (-511 - 512) right X axis
    ctl->axisRY(),       // (-511 - 512) right Y axis
    ctl->brake(),        // (0 - 1023): brake button
    ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
    ctl->miscButtons(),  // bitmask of pressed "misc" buttons
    ctl->gyroX(),        // Gyro X
    ctl->gyroY(),        // Gyro Y
    ctl->gyroZ(),        // Gyro Z
    ctl->accelX(),       // Accelerometer X
    ctl->accelY(),       // Accelerometer Y
    ctl->accelZ(),       // Accelerometer Z
    ctl->battery());
}

void dumpJoyData(JoyData &jd) {
  Serial.printf("JoyData:: lx:%d ly:%d rx:%d ry:%d lt:%u rt:%u bt:%04x\n",
                jd.lx,
                jd.ly,
                jd.rx,
                jd.ry,
                jd.lt,
                jd.rt,
                jd.buttons);
}

template<typename T>
T map(T in, T inMin, T inMid, T inMax, T outMin, T outMid, T outMax) {
  T out;
  if (in <= inMid) {
    // Map from [inMin, inMid] to [outMin, outMid]
    T inRange = inMid - inMin;
    T outRange = outMid - outMin;
    out = (in - inMin) * outRange / inRange + outMin;
  } else {
    // Map from [inMid, inMax] to [outMid, outMax]
    T inRange = inMax - inMid;
    T outRange = outMax - outMid;
    out = (in - inMid) * outRange / inRange + outMid;
  }
  return out;
}

void processControllers() {
  auto myController = myControllers[0];
  if (myController && myController->isConnected() && myController->hasData()) {
    if (myController->isGamepad()) {
      //  dumpGamepad(myController);

      jdata.lx = map(myController->axisX(), -508, -12, 512, -127, 0, 127);
      jdata.ly = map(myController->axisY(), -508, 8, 512, -127, 0, 127);
      jdata.rx = map(myController->axisRX(), -508, -32, 512, -127, 0, 127);
      jdata.ry = map(myController->axisRY(), -508, 18, 512, -127, 0, 127);
      jdata.lt = map(myController->brake(), 0, 1020, 0, 255);
      jdata.rt = map(myController->throttle(), 0, 1020, 0, 255);

      jdata.buttons = 0;
      if (myController->buttons() & BPB::Cross) jdata.buttons |= BUTTONS(myPS4::CROSS);
      if (myController->buttons() & BPB::Circle) jdata.buttons |= BUTTONS(myPS4::CIRCLE);
      if (myController->buttons() & BPB::Square) jdata.buttons |= BUTTONS(myPS4::SQUARE);
      if (myController->buttons() & BPB::Triangle) jdata.buttons |= BUTTONS(myPS4::TRIANGLE);
      if (myController->miscButtons() & BPB::Share) jdata.buttons |= BUTTONS(myPS4::SHARE);
      if (myController->miscButtons() & BPB::Power) jdata.buttons |= BUTTONS(myPS4::PS_BUTTON);
      if (myController->miscButtons() & BPB::Option) jdata.buttons |= BUTTONS(myPS4::OPTION);
      if (myController->buttons() & BPB::L3) jdata.buttons |= BUTTONS(myPS4::L3);
      if (myController->buttons() & BPB::R3) jdata.buttons |= BUTTONS(myPS4::R3);
      if (myController->buttons() & BPB::L1) jdata.buttons |= BUTTONS(myPS4::L1);
      if (myController->buttons() & BPB::R1) jdata.buttons |= BUTTONS(myPS4::R1);
      if (myController->dpad() & BPB::Up) jdata.buttons |= BUTTONS(myPS4::UP);
      if (myController->dpad() & BPB::Down) jdata.buttons |= BUTTONS(myPS4::DOWN);
      if (myController->dpad() & BPB::Left) jdata.buttons |= BUTTONS(myPS4::LEFT);
      if (myController->dpad() & BPB::Right) jdata.buttons |= BUTTONS(myPS4::RIGHT);

      if (myController->miscButtons() & BPB::Power) {
        if (myController->buttons() & BPB::L1 && myController->buttons() & BPB::R1) {
          myController->setColorLED(0, 255, 0);
          isBraked = false;
        } else {
          myController->setColorLED(255, 0, 255);
          isBraked = true;
        }
      }

      if (myController->battery() < 100)
        blinkColorLED(myController);
    }
  }
}

void sendPacket() {
  uint32_t now = millis();

  if (now - last_transmit >= 10) {
    uint8_t packet[sizeof(jdata) + 2];
    packet[0] = START_BYTE;
    memcpy((uint8_t *)packet + 1, (uint8_t *)&jdata, sizeof(jdata));
    packet[9] = crc.get_hash(packet + 1, sizeof(jdata));

    // Finally send packet to STM32 through UART2
    Serial2.write(packet, sizeof(packet));
    // Serial.printf("%lu\t", now - last_transmit);
    last_transmit = now;
    // dumpJoyData(jdata);
  }
}
// Arduino setup function. Runs in CPU 1
void setup() {
  pinMode(IN_BUILT_LED_BLUE, OUTPUT);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t *addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  // Setup the Bluepad32 callbacks
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // "forgetBluetoothKeys()" should be called when the user performs
  // a "device factory reset", or similar.
  // Calling "forgetBluetoothKeys" in setup() just as an example.
  // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
  // But it might also fix some connection / re-connection issues.
  BP32.forgetBluetoothKeys();


  // Enables mouse / touchpad support for gamepads that support them.
  // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
  // - First one: the gamepad
  // - Second one, which is a "virtual device", is a mouse.
  // By default, it is disabled.
  BP32.enableVirtualDevice(false);

  BP32.enableNewBluetoothConnections(false);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
  // This call fetches all the controllers' data.
  // Call this function in your main loop.
  if (BP32.update()) {
    processControllers();
    if (connected)
      sendPacket();
  }
  // The main loop must have some kind of "yield to lower priority task" event.
  // Otherwise, the watchdog will get triggered.
  // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
  // Detailed info here:
  // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

  vTaskDelay(1);
  // delay(150);
}