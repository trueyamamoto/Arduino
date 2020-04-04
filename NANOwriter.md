<h1>How to write Arduino sketches to ATmega328P with Arduino Nano compatibles</h1>

<h2>Materials</h2>
<ul>
         <li>PC (enable to running avrdude-command and Arduino software / USB2 port)</li>
         <li>Arduino Nano or compatibles</li>
         <li>USB cable (for connecting PC and Arduino)</li>
         <li>ATmega328P-PU (28pin DIP)</li>
         <li>prototyping board / breadboard</li>
         <li>wire</li>
         <li>LED with resistor</li>
         <li>(28pin ZIF socket / 28P IC socket, if available)</li>
</ul>

<h2>Process</h2>
<ol>
         <li>Set fuse bytes of the ATmega328P (use avrdude-command)</li>
         <li>Write a bootloader to the ATmega328P (use Arduino software)</li>
         <li>Write an Arduino sketch to the ATmega328P (use Arduino software)</li>
</ol>

<h2>Enable to avrdude-command on the host PC</h2>
<p>on Windows, install <a href="http://winavr.sourceforge.net/" target="_blank">WinAVR</a> and set the path of avrdude command to command prompt</p>

<h2>Enable to set ATmega328P on Arduino software</h2>
<ol>
         <li>Install <a href="https://www.arduino.cc/en/main/software" target="_blank">Arduino IDE</a> to the host PC</li>
         <li>Download and extract <a href="https://www.arduino.cc/en/Tutorial/ArduinoToBreadboard" target="_blank">hardware configuration archive</a> (e.g. breadboard-1-6-x.zip)</li>
         <li>move the extracted archive (breadboard directory) to the install directory of Arduino IDE
                  (e.g. C:/Program Files (x86)/Arduino/hardware/) on the host PC</li>
         <li>check "ATmega328 on a breadboard (8 MHz internal clock)" is added in Arduino IDE Tools >> Board</li>
</ol>

<h2>Make an Arduino ISP gadget</h2>
<img src="./img_nanowriter/writer_diagram.png" width="30%">
<img src="./img_nanowriter/writer_parts.jpg" width="30%">
<img src="./img_nanowriter/writer.jpg" width="30%">
<p>(that LED is for test)</p>
<ol>
         <li>assemble the gadget</li>
         <li>connect the gadget to the host PC
         <li>run <a href="https://www.arduino.cc/en/main/software" target="_blank">Arduino IDE</a> 
                  and open the sketch of ArduinoISP<br>
                  File >> Examples >> 11.ArduinoISP >> ArduinoISP<br>
                  <img src="./img_nanowriter/arduinoisp_load.png" width="30%"></li>
         <li>set configurations of the gadget<br>(In case the gadget is connected in COM18 USB port)<br>
                  Board : Arduino Nano<br>
                  Processor : ATmega328P<br>
                  Programmer : USBasp<br>
                  <img src="./img_nanowriter/arduinoisp_set.png" width="30%"></li>
         <li>write the sketch of ArduinoISP<br>Sketch >> Upload</li>
</ol>

<h2>Set fuse bytes of the ATmega328P</h2>
<p>in case the Arduino ISP gadget is connected in COM18 USB port</p>
<ol>
         <li>check the default setting<br># avrdude -c arduino -p m328p -P COM18 -b 19200 -v</li>
<pre>
c:\>avrdude -c arduino -p m328p -P COM18 -b 19200 -v

avrdude: Version 5.10, compiled on Jan 19 2010 at 10:45:23
         Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
         Copyright (c) 2007-2009 Joerg Wunsch

         System wide configuration file is "C:\WinAVR-20100110\bin\avrdude.conf"


         Using Port                    : COM18
         Using Programmer              : arduino
         Overriding Baud Rate          : 19200
         AVR Part                      : ATMEGA328P
         Chip Erase delay              : 9000 us
         PAGEL                         : PD7
         BS2                           : PC2
         RESET disposition             : dedicated
         RETRY pulse                   : SCK
         serial program mode           : yes
         parallel program mode         : yes
         Timeout                       : 200
         StabDelay                     : 100
         CmdexeDelay                   : 25
         SyncLoops                     : 32
         ByteDelay                     : 0
         PollIndex                     : 3
         PollValue                     : 0x53
         Memory Detail                 :

                                  Block Poll               Page      Polled
           Memory Type Mode Delay Size  Indx Paged  Size   Size #Pages MinW  MaxW   ReadBack

           ----------- ---- ----- ----- ---- ------ ------ ---- ------ ----- ----- ---------

           eeprom        65     5     4    0 no       1024    4      0  3600  3600 0xff 0xff
           flash         65     6   128    0 yes     32768  128    256  4500  4500 0xff 0xff
           lfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           hfuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           efuse          0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           lock           0     0     0    0 no          1    0      0  4500  4500 0x00 0x00
           calibration    0     0     0    0 no          1    0      0     0     0 0x00 0x00
           signature      0     0     0    0 no          3    0      0     0     0 0x00 0x00


         Programmer Type : Arduino
         Description     : Arduino
         Hardware Version: 2
         Firmware Version: 1.18
         Topcard         : Unknown
         Vtarget         : 0.0 V
         Varef           : 0.0 V
         Oscillator      : Off
         SCK period      : 0.1 us

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.01s

avrdude: Device signature = 0x1e950f
avrdude: safemode: lfuse reads as 62
avrdude: safemode: hfuse reads as D9
avrdude: safemode: efuse reads as 7

avrdude: safemode: lfuse reads as 62
avrdude: safemode: hfuse reads as D9
avrdude: safemode: efuse reads as 7
avrdude: safemode: Fuses OK

avrdude done.  Thank you.
</pre>

<li>set fuse bytes<br>
         # avrdude -c arduino -p m328p -P COM18 -b 19200 -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0x7:m<br>
         In this example, low fuse byte is set to 0xE2 (0b11100010) in order to drive the ATmega328P at 8MHz.</li>

<p><table border="1">
         <caption>Fuse Low Byte</caption>
         <tr><th>Low Fuse Byte</th><th>Bit No</th><th>Description</th><th>Value</th></tr>
         <tr><td>CKDIV8</td><td>7</td><td>Divide clock by 8</td><td>1</td></tr>
         <tr><td>CKOUT</td><td>6</td><td>Clock output</td><td>1</td></tr>
         <tr><td>SUT1</td><td>5</td><td>Select start-up time</td><td>1</td></tr>
         <tr><td>SUT0</td><td>4</td><td>Select start-up time</td><td>0</td></tr>
         <tr><td>CKSEL3</td><td>3</td><td>Select Clock source</td><td>0</td></tr>
         <tr><td>CKSEL2</td><td>2</td><td>Select Clock source</td><td>0</td></tr>
         <tr><td>CKSEL1</td><td>1</td><td>Select Clock source</td><td>1</td></tr>
         <tr><td>CKSEL0</td><td>0</td><td>Select Clock source</td><td>0</td></tr>
</table></p>

<p><table border="1">
         <caption>CKSEL options of Fuse Low Byte</caption>
         <tr><th>Device Clocking Option</th><th>CKSEL3..0</th></tr>
         <tr><td>Low Power Crystal Oscillator</td><td>1111 - 1000</td></tr>
         <tr><td>Full Swing Crystal Oscillator</td><td>0111 - 0110</td></tr>
         <tr><td>Low Frequency Crystal Oscillator</td><td>0101 - 0100</td></tr>
         <tr><td>Internal 128 kHz RC Oscillator</td><td>0011</td></tr>
         <tr><td>Calibrated Internal RC Oscillator</td><td>0010</td></tr>
         <tr><td>External Clock</td><td>0000</td></tr>
         <tr><td>Reserved</td><td>0001</td></tr>
</table></p>

<pre>
c:\>avrdude -c arduino -p m328p -P COM18 -b 19200 -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0x7:m

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.01s

avrdude: Device signature = 0x1e950f
avrdude: reading input file "0xe2"
avrdude: writing lfuse (1 bytes):

Writing | ################################################## | 100% 0.03s

avrdude: 1 bytes of lfuse written
avrdude: verifying lfuse memory against 0xe2:
avrdude: load data lfuse data from input file 0xe2:
avrdude: input file 0xe2 contains 1 bytes
avrdude: reading on-chip lfuse data:

Reading | ################################################## | 100% 0.01s

avrdude: verifying ...
avrdude: 1 bytes of lfuse verified

avrdude: safemode: Fuses OK

avrdude done.  Thank you.
</pre>
</ol>

<h2>Write a bootloader to the ATmega328P</h2>
<p>Tool >> Burn Bootloader</p>

<h2>Write an Arduino sketch to the ATmega328P</h2>
Board : ATmega328 on a breadboard (8 MHz internal clock)<br>
Programmer : Arduino as ISP<br>
<p><img src="./img_nanowriter/sketch_set.png" width="30%"></p>
<p>Sketch >> <b>Upload Using Programmer</b></p>
https://github.com/trueyamamoto/Arduino/blob/master/led_blink.ino
