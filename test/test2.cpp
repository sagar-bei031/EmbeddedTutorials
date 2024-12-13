#include <iostream>
#include <cstdint>

#include "crc8.hpp"

using namespace std;

int main()
{
    uint8_t data[] = {0xc2};
    uint8_t crc = CRC8::Instance.get_hash(data, sizeof(data));
    cout.setf(ios::hex, ios::basefield);
    cout << "CRC: " << (int)crc << endl;
}