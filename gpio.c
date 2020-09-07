/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#include "reg_gpio.h"

#include "gpio.h"

void gpio_init(void)
{
	GPIO_PINDIR_REG|=(1<<PIN_LED);
}

unsigned char is_reset_button_pressed(void)
{
	return !(GPIO_DATA_INP_REG&(1<<PIN_RESET_BUTTON));
}

void led_on_off(const unsigned char onoff)
{
	//inverted logic, LED is connected between Vcc and pin!
	if(onoff)
		GPIO_DATA_CLR_REG|=(1<<PIN_LED);
	else
		GPIO_DATA_SET_REG|=(1<<PIN_LED);
}
