#include <SoftwareSerial.h> // If you only have one hardware serial like UNO
#include "crc8.hpp"

struct Twist {
  float vx;
  float vy;
  float w;
};

const uint8_t START_BYTE = 0xA5;
const uint8_t LED_PIN = 13;
const uint8_t RX_PIN = 4;
const uint8_t TX_PIN = 5;

SoftwareSerial soft_serial(RX_PIN, TX_PIN);
Twist twist = {0.0f, 0.0f, 0.0f};
uint8_t receiving_packet[sizeof(Twist) + 2];

uint32_t last_received_tick = 0;
uint32_t last_blinked_tick = 0;
uint32_t last_printed_tick = 0;

bool is_waiting_for_start_byte = true;

char print_buffer[100];

void blink_led()
{
  if (millis() - last_blinked_tick < 100)
    return;

  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  last_blinked_tick = millis();
}

void print_twist()
{
  if (last_printed_tick < 100)
    return;

  snprintf(print_buffer, sizeof(print_buffer), "vx: %f, vy: %f, w: %f\n", twist.vx, twist.vy, twist.w);
  Serial.write(print_buffer, strlen(print_buffer));

  last_printed_tick = millis();
}

void setup() {
  Serial.begin(115200);
  soft_serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  delay(100);
}

void loop() {
  if (is_waiting_for_start_byte)
  {
    if (soft_serial.available() < sizeof(START_BYTE))
      return;

      uint8_t received_start_byte = soft_serial.read();
      if (received_start_byte == START_BYTE)
      {
        is_waiting_for_start_byte = false;
      }
      else
      {
        blink_led(); // blink led to show error
      }
  }
  else
  {
    if (soft_serial.available() < (sizeof(receiving_packet) -1))
      return;

    Twist received_twist;
    soft_serial.readBytes((uint8_t*)&received_twist, sizeof(received_twist));
    uint8_t received_hash = soft_serial.read();
    uint8_t calculated_hash = CRC8::get_hash((uint8_t*)&received_twist, sizeof(twist));

    if (received_hash == calculated_hash)
    {
      twist = received_twist;
      print_twist();
      last_received_tick = millis();
    }
    {
      blink_led(); // blink led to show error
    }

    is_waiting_for_start_byte = true;
  }
}
