/*
(c) 2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS CODE COMES WITHOUT ANY WARRANTY!
*/

#ifndef __REG_SSPC_H__
#define __REG_SSPC_H__

//BIT DEFINITIONS MIGHT BE WRONG, UNTESTED!!

#define SSP_CTRL_REG0 (*(volatile unsigned int*)0x98b00000)

#define SSP_CTRL_REG1 (*(volatile unsigned int*)0x98b00004)

#define SSP_CTRL_REG2 (*(volatile unsigned int*)0x98b00008)
#define SSP_TX_FIFO_CLR 3
#define SSP_RX_FIFO_CLR 2
#define SSP_TX_DATA_OUT_ENABLE 1
#define SSP_ENABLE 0

#define SSP_STATUS_REG (*(volatile unsigned int*)0x98b0000c)
#define SSP_MASK_TX_FIFO_ENTRIES 0x1f000
#define SSP_MASK_RX_FIFO_ENTRIES 0x1f0
#define SSP_IS_BUSY 2
#define SSP_TX_FIFO_NOT_FULL 1
#define SSP_RX_FIFO_NOT_FULL 0

#define SSP_INT_CTRL_REG (*(volatile unsigned int*)0x98b00010)
#define SSP_INT_STATUS_REG (*(volatile unsigned int*)0x98b00014)
#define SSP_DATA_REG (*(volatile unsigned int*)0x98b00018)
#define SSP_INFO_REG (*(volatile unsigned int*)0x98b0001c)
#define SSP_AC_SLOT_VALID_REG (*(volatile unsigned int*)0x98b00020)

#endif
