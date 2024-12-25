#include <stdio.h>
#include <string.h>
#include "crc.hpp"

int main()
{
    CRC<uint32_t> crc(0xF4ACFB13, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    crc.print_table();
    printf("check: %08X\n", crc.get_check());

    char data[] = "Hello World";
    printf("hash: %08X\n", crc.compute_hash((uint8_t*)data, strlen(data)));
    return 0;
}