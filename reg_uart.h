/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#ifndef __REG_UART_H__
#define __REG_UART_H__

//WRITE
#define TRANSMITTER_HOLDING_REG (*(volatile unsigned int*)0x99600000)

#define INT_ENABLE_REG (*(volatile unsigned int*)0x99600004)
#define INT_RX_DATA_AVAILABLE 0

#define FIFO_CTRL_REG (*(volatile unsigned int*)0x99600008)
#define ENABLE_FIFO 1

#define LINE_CONTROL_REG (*(volatile unsigned int*)0x9960000c)
#define DIVISOR_LATCH_ACCESS_BIT 7
//with enabled access bit:
#define BAUD_RATE_DIVISOR_LSB_REG (*(volatile unsigned int*)0x99600000)
#define BAUD_RATE_DIVISOR_MSB_REG (*(volatile unsigned int*)0x99600004)
#define PRESCALER_REG (*(volatile unsigned int*)0x99600008)

#define MODEM_CTRL_REG (*(volatile unsigned int*)0x99600010)

#define TESTING_REG (*(volatile unsigned int*)0x99600014)

#define SCRATCH_PAD_REG (*(volatile unsigned int*)0x9960001C)

//READ
#define RECEIVER_BUFFER_REG (*(volatile unsigned char*)0x99600000)

#define INT_IDENT_REG (*(volatile unsigned int*)0x99600008)

#define LINE_STATUS_REG (*(volatile unsigned int*)0x99600014)
#define STATUS_REG_DATA_READY 0
#define STATUS_REG_THR_EMPTY 5

#define MODEM_STATUS_REG (*(volatile unsigned int*)0x99600018)

#endif
