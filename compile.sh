#! /bin/sh

#This is just a shortcut for compiling, translating to binary and padding...
#(c) 2020 by kitten_nb_five
#freenode #lkv373a

#licence: AGPL v3 or later

#THIS CODE COMES WITHOUT ANY WARRANTY!

nds32le-elf-gcc -Wall -mno-ext-perf -mno-ext-string -mno-v3push -march=v2 -Wl,--script=lkv373.ld $* && nds32le-elf-objcopy -d binary a.out firmware.bin && ./pad.sh && rm a.out

