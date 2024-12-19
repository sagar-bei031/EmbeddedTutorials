#include <stdio.h>
#include <string.h>
#include "crc.hpp"

int main()
{
    CRC<uint32_t> crc(0xF4ACFB13, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    crc.print_table();
    printf("check: %08X\n", crc.get_check());

    uint8_t data[] = {0xff, 0x19, 0x00, 0x66, 0x11};
    printf("hash: %08X\n", crc.compute_hash((uint8_t*)data, sizeof(data)));
    return 0;
}