--Minecraft RGB Lamp--

* 3D model and printing files by jorgenp on Thingiverse: https://www.thingiverse.com/thing:3625720

* RGB code developed and tested first on Uno R3 before using on Nano

* Circuit controlled by Arduino Uno R3 (Elegoo equivalent). See circuit pic and schematic in Circuit folder for details

** Components: (5) 220 ohm resistors, (2) 10 kohm resistors, (1) common-cathode RGB LED, (2) pushbuttons

** (1) 220 ohm resistor for each (R, G, B) pin of the LED, common pin to ground, each RGB pin controlled by a PWM output pin (9, 10, 11, respectively)

** (2) pushbuttons connected to pin 7 (brightness control) and pin 8 (color cycle) with internal 20 kohm - 50 kohm pull-up resistors enabled for the input pins.

** Pushing the left-hand button (closer to RGB LED) cycles through all major colors of "ore blocks" (brownish, yellow, cyan, green, red, blue) and one extra color (purple) just for fun

** A second pushbutton with connections identical to the first is connected to digital input pin 7 to control brightness of the LED by tweaking PWM output values to a duty cycle of 10%

* Program developed in Arduino IDE ver. 1.8.13 on 8 JAN 2021

** Program begins by declaring necessary globals:

*** Pin numbers for RGB pins of LED and for the color cycle and brightness pushbuttons

*** Variables of tracking presses on the first (left-hand) and second (right hand) pushbuttons

*** Two 3-element arrays for current and updated RGB values for use in brightness-tweaking function

*** Two variables for holding the current and previous "ore block" color values for use in brightness-tweaking function

** Setup code block sets the RGB-control pins as outputs and the button-reader pins as inputs

** Main loop block contains two primary if blocks, one for detecting the color cycle button pushes and the other for brightness button pushes

*** The first block begins with a 250 ms delay to mitigate bouncing of the pushbutton when pressed. It then checks to see if the number of logged presses is beyond the number of 
	available color options (6) and resets to 0 if it is. The number of logged presses is put into a switch statement that sequentially chooses a set of RGB values to generate a 
	color based on how many times the button has been pressed. The set of colors loops back to the start and repeats after the end of the switch statements is reached. The number 
	of button presses is incremented and the if block exits. The reason the block is post-incremented is so that the color-selection of the switch statement starts at index 0 rather 
	than 1. A function called setRGB is created to handle adjusting the RGB values sent to the LED in order to create the ore colors from the three arguments (R, G, B) given to it.
	The function also saves the three values in order (R, G, B) to indices [0-2] of the currentRGB integer array to make note of the RGB values currently in use. This array is used in 
	the next primary if block for adjusting brightness.

*** The second block begins with a delay as with the first block. Following this, the current color selection is noted by checking the current number of color cycle button presses
	(corresponds to the case numbers in the switch statement of the first block). After that, the press count of the second button is checked, though the name of the variable is
	a little misleading. Rather than store the number of presses of the button directly, the pressCount2 variable alternates between 0 (initial value) and 1 depending on certain
	conditions. The first if statment of the block executes be default on the first pass of the program and is responsible for dimming the light of the LED. To do that, the current
	RGB values (in currentRGB array) are assigned divided by a constant to adjust the duty cycle of each RGB component. The resulting values are put into the same indices of the newRGB
	float array and are typecasted to integer values when passed as arguments to the setRGB function, used to enact the brightness change. Dividing all RGB values by the same constant
	ensures that the RGB value ratio is held constant, maintaining the same color when dimming the LED. The reason newRGB's elements are typecasted to integers rather than saving them
	directly as integers in the array is because the floating-point value resulting from the intitial dimming operation are needed to simplify the reversing (brightening) process. In
	other words, multiplying the floating point result of the intitial division by the constant is was divided by results in the exact original answer. The first if statement ends by 
	changing the pressCount2 variable to 1 so that the next push of the brightness button triggers the second conditional block, and saves the current color selection to the previous
	color selection variable. THe second if statement of the primary block (else if) triggers when the button has been pressed once before (pressCount2 == 1). In order to prevent errors
	in color selection and dimming, this block uses an if-else pair to determing if the current color selection matches the previous color selection. If it does, then the current color
	selection is the dimmed version of the color selection and needs to be brightened back to full brightness, which is done by multiplying the float values in newRGB by the same constant
	they were divided by when dimming the LED. If the previous and current color selection do not match, then a new color is currently in use which is not currently in dim mode, meaning
	that the current color must be dimmed before it can be returned to full brightness. After one of the two cases executes, the previous color is updated to the current color and the 
	else-if block exits.