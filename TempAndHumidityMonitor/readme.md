# Temperature and Humidity Monitor

**This is an active project, details will change as new developments occur.**

## Project Summary

Whenever winter rolls around, I find that my nose bleeds much more often because of the drier air, courtesy of my heater. Essentially, the air has a moisture saturation point that varies by temperature. Warm air can carry more moisture than cold air, so when you heat cold air, the moisture content stays relatively the same, resulting in a decrease in relative humidity of the air. Anyways, I found an old Elegoo temperature/humidity module in my circuit box and thought it'd be a shame if it kept sitting in there unused. So, here we are.

## Circuit Connections

*Future*

## Program Information

*Future*

### Accessing DHT Sensor Data

The DHT11 sensor stores temperature and humidity data as integer variables. I created a new library called `DHT11` in my Arduino root directory and included the C++ and header file provided by Mark Ruys [on Github](https://github.com/markruys/arduino-DHT). To access sensor data, a `DHT` class needs to be instantiated so that `temperature` and `humidity` attributes can be accessed directly and worked with. The code was created to automatically recognize the DHT sensor (11, 21, etc.), so all that is required in the `setup` portion of the Arduino program is to specify which Arduino pin is used as the data pin for the DHT sensor and to allow enough setup time for the sensor to stabilize before beginning data communications with it. This argument is passed as an integer to the `setup` attribute of the `DHT` class instance. In the `loop` section, temperature and humidity data can be accessed using 'getTemperature()` and 'getHumidity()` respectively.  

I did not change much of the example code provided for controlling the DHT sensor (if it ain't broke don't fix it). I changed the first line of `loop` to be a simple delay of 1050 ms rather than relying on `getMinimumSamplingPeriod()` because I'm using a DHT11 sensor and do not have any other humidity sensors. The extra 50 ms is just for good measure when allowing the sensor to stabilize between reads. Eventually, the serial prints will be changed to prints for an LCD or other display device when I choose one that I would like to use.

## Resources

* General information about using the DHT11 resistive-type temperature/humidity module: https://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
** Note that the connections on this site tutorial do not follow the datasheet's layout - look at your component and the datasheet to ensure you're connecting properly 
** Note I am not using the same DHT program that this tutorial uses, the creater of that code points to another one [here](https://github.com/markruys/arduino-DHT).
*About Humidity Sensors: https://in.element14.com/sensor-humidity-sensor-technology
* About Temperature Sensors: https://in.element14.com/sensor-temperature-sensor-technology?ICID=I-CT-TP-BROWSE-8


# Notes for Ongoing Development

* Need a 5k pull-up resistor between data line and 5V line for connection lenghts < 20 m - a 10k pull-up is actually included on the pcb of the sensor itself
* Need to install `DHTLib` library or another equivalent library on arduino to make use of sensor output - developed by Rob Tillaart on github at https://github.com/RobTillaart/DHTlib and has further explanation on Arduino's website [here](https://playground.arduino.cc/Main/DHTLib/)
* From the datasheet, make sure that the sampling period of the DHT11 sensor **is NO LESS than 1000 ms**. This also means that you must allow at least 1000 ms at the start of your program before attempting to read the sensor or you will generate a timeout error
