# ATtiny_blink

This is a Solar balcony blinker. A solar cell charging a super capacitor and at the dawn, slowy blink a blue Led.

![IMG_0838.png](/Pict/IMG_0838.png)

I have put it in a jam pot and hope it can blink for years...

![IMG_0840.png](/Pict/IMG_0840.png)

Here you can find the schematics for this really simple project. Do note that I don't use the pcb but instead strip board.

![attiny_blink_schema.jpg](/Pict/attiny_blink_schema.jpg)

the solar cell deliver about 4 volts, maybe more during sunny time. I have put a 5.1 v Zener diode in parallel to protect the circuit. following a simple diode 1n4148 (better one is BAT41) that is block the capacitor to flow on the solar cell. at the connection between Zener and diode, use take a voltage mesure for sensing the dark status, going to attiny analog ADC3 (pin 2)

The output is on PB0 (pin 5). 

Code put ATtiny in deep sleep mode for about 50 seconds, check the dark status (solar cell volts > 0) and blink (or not) the Led.


The Pcb board could be like this one.

![attiny_blink_pcb.jpg](/Pict/attiny_blink_pcb.jpg)

I use also strip board for this


x

