#include <stdio.h>
#include <stdint.h>

uint8_t getAddBasedChecksum(uint8_t *data, size_t len)
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
   uint8_t data[] = {11, 22, 33, 44, 55, 66, 79, 89, 99, 100};

   uint32_t checksum = getAddBasedChecksum(data, sizeof(data));
   printf("checksum: %02X\n", checksum);

   return 0;
}