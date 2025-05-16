#define DEBUG // Disable it by commenting in actual implementation

#include <PS4Controller.h>
#include "crc8.hpp"
#include "joy_msg.hpp"
using namespace myPS4;

/** @brief Pins assignments of ESP32 */
#define IN_BUILT_LED_BLUE 2
#define RXD2 16
#define TXD2 17

/** @brief Start byte of packet */
#define START_BYTE 0xA5

CRC8 crc(7);

JoyData jdata;
bool is_flash_set = false;
bool is_braked;

uint32_t last_transmit = 0;

/** @brief Initialize controller parameters */
void setup() {

  Serial.begin(115200, SERIAL_8N1);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  pinMode(IN_BUILT_LED_BLUE, OUTPUT);
  digitalWrite(IN_BUILT_LED_BLUE, LOW);

  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);

  PS4.begin();
  Serial.print("ESP32 MAC: ");
  Serial.println(PS4.getAddress());
}

/** @brief Operation */
void loop() {
  if (!PS4.isConnected())
    return;

  uint32_t now = millis();
  if (now - last_transmit < 10)
    return;

  uint8_t packet[10];
  jdata.lx = PS4.LStickX();
  jdata.ly = -PS4.LStickY();
  jdata.rx = PS4.RStickX();
  jdata.ry = -PS4.RStickY();
  jdata.lt = PS4.L2Value();
  jdata.rt = PS4.R2Value();

  jdata.buttons = 0;

  if (PS4.Cross()) jdata.buttons |= BUTTONS(CROSS);
  if (PS4.Circle()) jdata.buttons |= BUTTONS(CIRCLE);
  if (PS4.Square()) jdata.buttons |= BUTTONS(SQUARE);
  if (PS4.Triangle()) jdata.buttons |= BUTTONS(TRIANGLE);

  if (PS4.Share()) jdata.buttons |= BUTTONS(SHARE);
  if (PS4.PSButton()) jdata.buttons |= BUTTONS(PS_BUTTON);
  if (PS4.Options()) jdata.buttons |= BUTTONS(OPTION);

  if (PS4.L3()) jdata.buttons |= BUTTONS(L3);
  if (PS4.R3()) jdata.buttons |= BUTTONS(R3);
  if (PS4.L1()) jdata.buttons |= BUTTONS(L1);
  if (PS4.R1()) jdata.buttons |= BUTTONS(R1);

  if (PS4.Up()) jdata.buttons |= BUTTONS(UP);
  if (PS4.UpLeft()) jdata.buttons |= (BUTTONS(UP) | BUTTONS(LEFT));
  if (PS4.Left()) jdata.buttons |= BUTTONS(LEFT);
  if (PS4.DownLeft()) jdata.buttons |= (BUTTONS(LEFT) | BUTTONS(DOWN));
  if (PS4.Down()) jdata.buttons |= BUTTONS(DOWN);
  if (PS4.DownRight()) jdata.buttons |= (BUTTONS(DOWN) | BUTTONS(RIGHT));
  if (PS4.Right()) jdata.buttons |= BUTTONS(RIGHT);
  if (PS4.UpRight()) jdata.buttons |= (BUTTONS(UP) | BUTTONS(RIGHT));
  
  if (PS4.Touchpad()) jdata.buttons |= BUTTONS(TOUCH);

  packet[0] = START_BYTE;
  memcpy((uint8_t*)packet + 1, (uint8_t*)&jdata, sizeof(jdata));
  packet[9] = crc.get_hash(packet + 1, sizeof(jdata));

  // Finally send packet to STM32 through UART2
  Serial2.write(packet, sizeof(packet));

  if (PS4.PSButton()) {
    if (PS4.L1() && PS4.R1()) {
      if (is_braked) {
        PS4.setLed(0, 255, 0);
        PS4.sendToController();
        // Serial.println("Brake removed");
        is_braked = false;
      }
    } else {
      if (!is_braked) {
        PS4.setLed(255, 0, 255);
        PS4.sendToController();
        // Serial.println("Braked");
        is_braked = true;
      }
    }
  }

#ifdef DEBUG
  Serial.printf("%lu: %hd %hd %hd %hd %hu %hu %04X\n",
                now - last_transmit, jdata.lx, jdata.ly, jdata.rx, jdata.ry, jdata.lt, jdata.rt, jdata.buttons);
#endif

  last_transmit = now;
}

/** @brief Callback on connect */
void onConnect() {
  digitalWrite(IN_BUILT_LED_BLUE, HIGH);
  Serial.printf("Battery: %d\n", PS4.Battery());
  PS4.setLed(0, 255, 0);
  PS4.sendToController();
  Serial.println("PS4 Connected.");
}

/** @brief Callback on disconnect */
void onDisConnect() {
  digitalWrite(IN_BUILT_LED_BLUE, LOW);
  Serial.println("!!PS4 Disconnected!!");
}