#include "crc8.hpp"

struct Twist {
  float vx;
  float vy;
  float w;
};

const uint8_t START_BYTE = 0xA5;
const uint8_t LED_PIN = 13;

Twist twist = {0.0f, 0.0f, 0.0f};
uint8_t receiving_packet[sizeof(Twist) + 2];

uint32_t last_received_tick = 0;
uint32_t last_blinked_tick = 0;
uint32_t last_printed_tick = 0;

bool is_waiting_for_start_byte = true;

char print_buffer[100];

void blink_led();
void print_twist();

void blink_led()
{
  if (millis() - last_blinked_tick < 100)
    return;

  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  last_blinked_tick = millis();
}

void print_twist()
{
  if (millis() - last_printed_tick < 100)
    return;

  Serial.print("vx: ");
  Serial.print(twist.vx);
  Serial.print("\t vy: ");
  Serial.print(twist.vy);
  Serial.print("\t w");
  Serial.println(twist.w);

  last_printed_tick = millis();
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  delay(100);
}

void loop() {
  if (is_waiting_for_start_byte)
  {
    if (Serial1.available() < 1)
      return;

      uint8_t received_start_byte = Serial1.read();
      if (received_start_byte == START_BYTE)
      {
        is_waiting_for_start_byte = false;
      }
      else
      {
        Serial.println("Start Byte Error!");
        blink_led(); // blink led to show error
      }
  }
  else
  {
    if (Serial1.available() < (sizeof(receiving_packet) -1))
      return;

    Twist received_twist;
    Serial1.readBytes((uint8_t*)&received_twist, sizeof(received_twist));
    uint8_t received_hash = Serial1.read();
    uint8_t calculated_hash = CRC8::get_hash((uint8_t*)&received_twist, sizeof(twist));

    if (received_hash == calculated_hash)
    {
      twist = received_twist;
      print_twist();
      last_received_tick = millis();
    }
    else
    {
      Serial.println("CRC Error");
      blink_led(); // blink led to show error
    }

    is_waiting_for_start_byte = true;
  }
}
