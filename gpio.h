/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#ifndef __GPIO_H__
#define __GPIO_H__

void gpio_init(void);

unsigned char is_reset_button_pressed(void);

void led_on_off(const unsigned char onoff); 

#endif
