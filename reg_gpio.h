/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#ifndef __REG_GPIO_H__
#define __REG_GPIO_H__

#define GPIO_DATA_OUT_REG (*(volatile unsigned int*)0x99300000) //RW
#define GPIO_DATA_INP_REG (*(volatile unsigned int*)0x99300004) //R
#define GPIO_PINDIR_REG (*(volatile unsigned int*)0x99300008) //RW, 1==output
#define GPIO_DATA_SET_REG (*(volatile unsigned int*)0x99300010) //W
#define GPIO_DATA_CLR_REG (*(volatile unsigned int*)0x99300014) //W (but is read in firmware - ??)
#define GPIO_PULL_ENABLE_REG (*(volatile unsigned int*)0x99300018) //RW
#define GPIO_PULL_TYPE_REG (*(volatile unsigned int*)0x9930001C) //RW
#define GPIO_INT_ENABLE_REG (*(volatile unsigned int*)0x99300020) //RW
//...

#define PIN_LED 14
#define PIN_RESET_BUTTON 16

#endif
