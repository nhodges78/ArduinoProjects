# RGB Minecraft Ore Block Lamp

This project uses 3D model and printing files created by [jorgenp on Thingiverse](https://www.thingiverse.com/thing:3625720). The current build of this project uses an Elegoo Uno R3 (equivalent to Arduino Uno R3) with the control program developed in Arduino IDE ver. 1.8.13. The final build of this project will utilize an Arduino Nano (or clone equivalent) to take advantage of the smaller footprint.

## Circuit Description

The circuit is controlled by an Elegoo Uno R3 and is shown in [this image](https://github.com/nhodges78/ArduinoProjects/blob/master/MinecraftLamp/Circuit/Circuit_Rev1.jpg), detailed further in the corresponding [schematic](https://github.com/nhodges78/ArduinoProjects/blob/master/MinecraftLamp/Circuit/Circuit_Rev1.png).

### Components
* (5) 220 ohm resistors
* (2) 10 kohm resistors
* (1) common-cathode RGB LED
* (2) pushbuttons

### Connections and Functionality
* (1) 220 ohm resistor for each (R, G, B) pin of the LED with common pin to ground. Each RGB pin is controlled by a PWM output pin (9, 10, 11, respectively).

* (2) pushbuttons connected to unique 10 kohm pulldown resistors. When pushed, each connects 5V through unique 220 ohm resistors to digital input pins 8 (color cycle) and 7 (brightness cycle).

* Pushing the left-hand button (digital pin 8, closer to RGB LED) cycles through all major colors of "ore blocks" (brownish, yellow, cyan, green, red, blue) and one extra color (purple) just for fun.

* A second pushbutton (digital pin 7, further from RGB LED) with connections identical to the first cycles through brightness levels of the LED by tweaking PWM output values of pins 9, 10, and 11 to alternate between duty cycles of 100% (full bright) and 10% (dimmed).

## Program Description
The program begins by declaring necessary globals:
* Pin numbers for RGB pins of LED and for the color cycle and brightness pushbuttons
* Variables for tracking presses on the first (left-hand) and second (right hand) pushbuttons
* Two 3-element arrays for current and updated RGB values (used in brightness-changing function)
* Two variables for holding the current and previous "ore block" color values (used in brightness-changing function)

The `setup` code block sets the RGB-control pins as outputs and the button-reader pins as inputs before the main looping block begins. The main `loop` block contains two primary `if` blocks, one for detecting the color cycle button pushes and the other for brightness button pushes. The first block begins with a 250 ms delay to mitigate bouncing of the pushbutton when pressed. It then checks to see if the number of logged presses is beyond the number of available color options (6) and resets presses to 0 if it is. The number of logged presses is put into a `switch` statement that sequentially chooses a set of RGB values to generate a color based on how many times the button has been pressed. The set of colors loops back to the start and repeats after the end of the `switch` statements is reached. At the end of the first `if` block, the number of button presses is incremented and the block is exited. The reason the number of presses is post-incremented is so that the color-selection of the `switch` statement starts at index 0 rather than 1. A function called `setRGB` is created to handle adjusting the RGB values sent to the LED in order to create the ore colors from the three arguments (R, G, B) given to it. The function also saves the three values in order (R, G, B) to indices 0-2 of the `currentRGB` integer array to make note of the RGB values currently in use. This array is used in the next primary `if` block for adjusting brightness.

The second primary `if` block begins with a delay as with the first block. Following this, the current color selection is noted by checking the current number of color cycle button presses (corresponds to the case numbers in the `switch` statement of the first `if` block). After that, the press count of the second button is checked, though the name of the variable is a little misleading. Rather than store the number of presses of the button directly, the `pressCount2` variable alternates between 0 (initial value) and 1 depending on certain conditions. The first `if` statment of the block executes be default on the first pass of the program and is responsible for dimming the light of the LED. To do that, the current RGB values (in `currentRGB` array) are divided by a constant to adjust the duty cycle of each RGB component. The resulting values are put into the same indices of the `newRGB` float array and are typecasted to integer values when passed as arguments to the `setRGB` function, used to enact the brightness change. Dividing all RGB values by the same constant ensures that the RGB value ratio is held constant, maintaining the same color when dimming the LED. The reason `newRGB`'s elements are typecasted to integers rather than saving them directly as integers in the array is because the floating-point values resulting from the intitial dimming operation are needed to simplify the reversing (brightening) process. In other words, multiplying the floating point result of the intitial division by the constant it was divided by results in the exact original value. The first `if` statement ends by changing the `pressCount2` variable to 1 so that the next push of the brightness button triggers the second conditional block, and saves the current color selection to the previous color selection variable. The second `if` statement of the primary block (`else if`) triggers when the button has been pressed once before (`pressCount2 == 1`). In order to prevent errors in color selection and dimming, this block uses an `if-else` pair to determine if the current color selection matches the previous color selection. If it does, then the current color selection is the dimmed version of the color selection and needs to be brightened back to full brightness, which is done by multiplying the float values in `newRGB` by the same constant they were divided by when dimming the LED. If the previous and current color selection do not match, then a new color is currently in use which is not currently in dimmed mode, meaning that the current color must be dimmed before it can be returned to full brightness. After one of the two cases executes, the previous color is updated to the current color and the `else-if` block exits. Once the entire `if` block executes, the program loops back to the start and repeats.
