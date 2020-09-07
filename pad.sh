#! /bin/sh

#This script adds nullbytes to the binary firmware file to make its size
#a multiple of 4kB. This seems to be needed for the update process to work.
#(c) 2020 by kitten_nb_five
#freenode #lkv373a

#licence: AGPL v3 or later

#THIS CODE COMES WITHOUT ANY WARRANTY!

SIZE=`stat -c "%s" firmware.bin`
MOD=`expr $SIZE % 4096`
if [ $MOD -eq 0 ]; then
echo "adding 0 bytes"
exit 0
fi
BYTES_TO_PAD=`expr 4096 - $MOD`
echo "adding $BYTES_TO_PAD bytes"
truncate -s +$BYTES_TO_PAD firmware.bin

