**What is this?**  
This is mostly a proof of concept, an EXPERIMENTAL and MINIMALISTIC firmware for the LKV373 *V2*. As usual it comes WITHOUT ANY WARRANTY! YOU MAY BRICK YOUR DEVICE OR IT MAY EXPLODE! **USE AT YOUR OWN RISK!** You should have block2 of the original firmware handy and maybe a way to reflash the entire memory if something goes really wrong.  

**What does work?**  
You can stream video and use the serial interface. See MANUAL.txt.  
  
**What does NOT work? / What must be improved?**  
-no audio  
-no interlaced video  (<some_resolution>**i**)   
-no webinterface, not even ARP or PING  
-HDCP? needs testing  
-the ITE6604 is NOT initialized. Initializing it according to the (leaked) doc we have makes the system stop working... TODO: Find correct configuration (or copy from output of simulator with standard firmware) and especially poll status flags and adjust video size and maybe other parameters if something changes.  
-lots of other stuff...
  
**How to flash?**  
Use the webinterface at 192.168.168.55 or .221 if in bootloader mode.  
  
**How to use?**  
Connect via serial 115200 8N1. Plug in a video source and network, wait a few seconds and type `stream start`. <s>Report any bugs here or on IRC even if i am offline.</s> You can report bugs but because nobody seems to care about this old device i don't think i will continue this work.  
  
**How to get rid of this firmware again?**  
Hold the reset button and send any character over serial. Wait for the bootloader and reflash original firmware (block2!!) using the webinterface on .221. If the firmware crashed power-cycle. You can also hold the reset button while power-cycling and keep pressed for a few seconds to go into bootloader mode.
