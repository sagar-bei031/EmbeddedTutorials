#include "stm32f1xx_hal.h"

#define USE_USB_CDC
#ifdef USE_USB_CDC

#include "usbd_cdc_if.h"

int _write(int file, char *data, int len)
{
    CDC_Transmit_FS((uint8_t*)data, (uint16_t)len);
    return len;
}

#else

int _write(int file, char *data, int len)
{
    for (int i = 0; i < len; ++i)
    {
        ITM_SendChar(data[i]);
    }
    return len;
}

#endif