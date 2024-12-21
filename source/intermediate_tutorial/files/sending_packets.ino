#include "crc8.hpp"

struct Twist {
  float vx;
  float vy;
  float w;
};

const uint8_t START_BYTE = 0xA5;
const uint8_t LED_PIN = 13;

Twist twist;
uint8_t sending_packet[sizeof(Twist) + 2];
uint32_t last_sent_tick = 0;
uint32_t last_blinked_tick = 0;

void blink_led()
{
  if (millis() - last_blinked_tick < 100)
    return;

  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  last_blinked_tick = millis();
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  delay(100);
}

void loop() {
  uint32_t now = millis();
  if (now - last_sent_tick < 10)
    return;

  twist.vx = 0.5f;
  twist.vy = 0.5f;
  twist.w = 0.0f;

  sending_packet[0] = START_BYTE;
  memcpy(sending_packet, &twist, sizeof(twist));
  sending_packet[sizeof(sending_packet) -1] = CRC8::get_hash((uint8_t*)(&twist), sizeof(twist));

  Serial.write(sending_packet, sizeof(sending_packet));
  blink_led();

  last_sent_tick = now;
}
