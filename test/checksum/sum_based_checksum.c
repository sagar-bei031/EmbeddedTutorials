#include <stdio.h>
#include <stdint.h>

uint8_t getSumBasedChecksum(uint8_t *data, size_t len)
{
   uint8_t checksum = 0;
   size_t i;

   for (i = 0; i < len; ++i)
   {
      checksum += data[i];
   }

   return checksum;
}

int main()
{
   uint8_t data[] = {0x11, 0x22, 0x33, 0x44, 0x55};

   uint32_t checksum = getSumBasedChecksum(data, sizeof(data));
   printf("checksum: %02X\n", checksum);

   return 0;
}