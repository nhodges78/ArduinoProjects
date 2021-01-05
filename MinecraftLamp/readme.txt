--Minecraft RGB Lamp--

* 3D model and printing files by jorgenp on Thingiverse: https://www.thingiverse.com/thing:3625720

* RGB code developed and tested first on Uno R3 before using on Nano

* First circuit developed (see pic and schematic) 

** Components: (4) 220 ohm resistors, (1) 10 kohm resistor, (1) common-cathode RGB LED, (1) pushbutton

** (1) 220 ohm resistor for each (R, G, B) pin of the LED, common pin to ground, each RGB pin controlled by a PWM output pin (9, 10, 11, respectively)

** pushbutton connected to 10 kohm pulldown resistor; when pushed, connects 5V through 220 ohm resistor to digital input pin 8

** First circuit has a white "test" LED with a 220 ohm resistor to make sure a signal is indeed sent to the input pin (lights up when button is pressed)

** Pushing the button cycles through all major colors of ore (brownish, yellow, cyan, green, red, blue) and one extra color (purple) just for fun

** A second pushbutton with connections identical to the first is connected to digital input pin 7 to control brightness of the lamp by tweaking PWM output values