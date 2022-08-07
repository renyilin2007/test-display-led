#ifndef __BSP_DISPLAY_LED_H__
#define __BSP_DISPLAY_LED_H__
#include "stdint.h"
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

void bsp_display_led_init(void);
int bsp_set_display_led_val(uint8_t index, uint8_t val);
int _bsp_set_displays_led_level(int level);
int bsp_set_display_led_allon(void);
int bsp_set_display_led_alloff(int opt);

#endif /* __BSP_DISPLAY_LED_H__ */
