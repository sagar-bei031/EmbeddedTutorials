#include "main.h"
#include "matrix32.hpp"

#include "app.h"

Matrix32<3, 3> m1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
Matrix32<3, 3> m2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
Matrix32<3, 3> result;

void init()
{
    // nothing to do here
}

void run()
{
    printf("Adding m1 and m2, result:\n");
    result = m1 + m2;
    result.printData();
    HAL_Delay(1000);

    printf("Subtracting m1 and m2, result:\n");
    result = m1 - m2;
    result.printData();
    HAL_Delay(1000);

    printf("Multiplying m1 and m2, result:\n");
    result = m1 * m2;
    result.printData();
    HAL_Delay(1000);

    printf("Multiplying m1 by 2\n");
    result = m1.scale(2);
    result.printData();
    HAL_Delay(1000);

    printf("Transposing m1\n");
    result = m1.trans();
    result.printData();
    HAL_Delay(1000);

    printf("Inverting m1\n");
    result = m1.inverse();
    result.printData();
    HAL_Delay(1000);
}