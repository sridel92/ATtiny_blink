# ATtiny_blink

This is a Solar balcony blinker. A solar cell charge a super capacitor and at the dusk, make a blue led slowly blinking.

![IMG_0838.png](/Pict/IMG_0838.png)

I have put it in a jam pot and hope it can blink for years...

![IMG_0840.png](/Pict/IMG_0840.png)

Here you can find the schematics for this really simple project. Do note that I don't use the pcb but instead strip board.

![attiny_blink_schema.jpg](/Pict/attiny_blink_schema.jpg)

List of material
1 x ATTINY85V-10P (the V series act with low voltage from 1.8 to 5.5 volts)
1 x Super capacitor 4 farads, 5,5 volts (or higher capacity)
1 x 5.1 v Zener
1 x 1n4148 (or BAT41)
1 x 4 volts Solar cell
a piece of strip board
a STK500 programmer or Arduino Uno (the programming part is not shown in this git)

The solar cell deliver about 4 volts, maybe more during sunny time. I have put a 5.1 v Zener diode in parallel to protect the circuit. A diode 1n4148 ( better will be BAT41 ) block a reverse voltage flow from the the capacitor to the solar cell. at the connection between Zener and diode, we take voltage mesure for sensing the dark status, going to attiny analog ADC3 (pin 2)

The output is on PB0 (pin 5). 

the embedded code is putting the ATtiny in deep sleep mode for about 50 seconds, check the dark status (solar cell volts > 0) and blink (or not) the Blue Led. No more, no less.

The Pcb board could be like this one.

![attiny_blink_pcb.jpg](/Pict/attiny_blink_pcb.jpg)

I use also strip board for this

this video doesn't says more about this... The fun is to learn and share.

https://www.youtube.com/watch?v=GBdv9fyUcHE


