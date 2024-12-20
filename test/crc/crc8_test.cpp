#include <iostream>
#include "crc8.hpp"

int main()
{
    CRC8::print_table();
    uint8_t data[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << "CRC-8 hash: " << (int)CRC8::Instance.get_hash(data, sizeof(data)) << std::endl;
    return 0;
}