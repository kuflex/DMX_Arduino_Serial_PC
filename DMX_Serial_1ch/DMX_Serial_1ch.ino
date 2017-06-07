/*
# DMX_Arduino_Serial_PC

Here is a sketch which allows to control 1-st DMX channel from PC using Arduino DMX shield.

Controlling DMX devices from PC using Arduino DMX shield.
Using this sketch, you can send data to Arduino from USB PC to control DMX device on the 1st channel.
You can modify the code to control many DMX channels.

## Requirements 
* Arduino Mega
 (We will use Serial for connecting with PC, 
 so we are required use Serial 1 to send data to DMX. It's presented in Arduino Mega, but not presented in Arduino Uno)
* using DMX shield 3-pin, https://www.dfrobot.com/product-984.html, (in Russia, we bought it on devicter.ru)
* Conceptinetic library https://sourceforge.net/projects/dmxlibraryforar/?source=typ_redirect
(Modified copy included together with our sketch)

## Installation

1. Unpack Conceptinetics_RDM_alpha3_2.zip, in Conceptinetics.h comment USE_DMX_SERIAL_0 and uncomment USE_DMX_SERIAL_1

```
//#define USE_DMX_SERIAL_0
#define USE_DMX_SERIAL_1
//#define USE_DMX_SERIAL_2
//#define USE_DMX_SERIAL_3
```

(Or use library included here Conceptinetics_RDM_alpha3_2_Serial1.zip)

2. Install this library to Arduino IDE, using "Add library from ZIP...

3. Set jumpers on shield: RX-io, TX-io, DE, EN (near Slave)

4. Connect (by wire!) PIN 4 (marked as TX-io on the shield legend) with TXD1 on Arduino Mega.
This will allow shield to send DMX TX signal via Serial1.

5. Upload this sketch to Arduino.

6. Now you can use it. You can send bytes to Serial from PC, and this bytes will transmit to 1-st DMX channel!
To test it, open Arduino Console and type several symbols.

Also, you can test overall DMX setup, by uncommenting code masred at //TEST in this sketch:
```
  //TEST
  set_dmx_ch(1,test++);
  test %= 256;
  delay(3);
```

This code sends periodical increasing values to the first channel.

Have fun!

Kuflex team.
*/

#include <Conceptinetics.h>

#define DMX_MASTER_CHANNELS   100 
#define RXEN_PIN                2
DMX_Master        dmx_master ( DMX_MASTER_CHANNELS, RXEN_PIN );
int led_on = 0;

void set_dmx_ch(int i, int v) {
  dmx_master.setChannelValue ( 1, v++ );
  led_on = 1-led_on;
  if (led_on) digitalWrite(LED_BUILTIN,HIGH);
  else digitalWrite(LED_BUILTIN,LOW);
}


void setup() {
  dmx_master.enable (); 

  pinMode(LED_BUILTIN, OUTPUT);  
  Serial.begin(9600);
  Serial.println("1-channel DMX control");

  //dmx_master.setChannelRange ( 1, 25, 0 );
  set_dmx_ch(1,0);
} 

int test=0;

void loop() {
int v = Serial.read(); 
  if (v>=0) { 
    set_dmx_ch(1,v);        
  }
  delay(1);

  //TEST
  //set_dmx_ch(1,test++);
  //test %= 256;
  //delay(3);
             
}
