#include <iostream>

#include "crc8.hpp"

using namespace std;

int main()
{
        cout.setf(ios::hex, ios::basefield);
    for (int i=0; i < 256; ++i)
    {
        cout << i << ":" << (int)CRC8::table_[i];
        if (i % 10 == 0)
        {
            cout << endl;
        }
        else
        {
            cout << "\t";
        }
    }
}