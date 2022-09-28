#  Automatic Smart Water Tank System

Water is an essential element of life.  Due to the global environmental situation,  water management and conservation are vital for human survival.  Considering this,  the interest in the field of consumer-based humanitarian researches with the aid of the  Internet of  Things  (IoT) technology is rapidly developing. This paper discusses an IoT based water tank monitoring system that measures water level, temperature, low tank alert, over-temperature alarm and auto water pump on/off in real-time, using an ultrasonic sensor, temperature sensor, water mother and relay while calculating the volume of the water in real-time.
<img src="images\cover.png">

## Problem
Many people are prone to certain diseases due to not checking the quality 
of the water they use.

By a normal water tank,

* Existing water level
* Temperature that changes from moment to moment
* pH value of water
* Is there solids or debris
* water analysis reports unable to look.

## Proposed System
This Automatic Water Tank System is suggested as a solution to the above 
problems.

Mainly by this method,

* The water level in the water tank,
* Temperature, 
* pH of water, 
* Is there solids or debris,

Accordingly, by the system,

* Filling the water tank automatically
* Existing water temperature
* Recommending whether the available water is suitable for consumption
* Issues water analysis reports

Performs the actions.

When the water in the water tank drops to a certain level, the water motor starts 
running and automatically stops when the tank is full.

## Functions of the System
* The water level in the water tank, Detection by ultrasonic sensors.
* Detection of available water temperature by temperature sensors.
* Over temperature alarm.
* Automatic ON / OFF water motor by relay.
* Any time view database.

## Components Needed
 
### NodeMCU
NodeMCU is an open source firmware for which open source 
prototyping board designs are available. The firmware uses the Lua 
scripting language. The firmware is based on the eLua project, and built 
on the Espressif Non-OS SDK for ESP8266. It uses many open source 
projects, such as lua-cjson and SPIFFS. On board Wi-Fi
<img src="images\nodemcu.png">

### Ultrasonic Sensor
An ultrasonic sensor is an instrument that measures the distance to an 
object using ultrasonic sound waves. An ultrasonic sensor uses a 
transducer to send and receive ultrasonic pulses that relay back 
information about an object's proximity.

<img src="images\ultrasonic_sensor.png">

### Temperature sensor
A temperature sensor is an electronic device that measures the 
temperature of its environment and converts the input data into 
electronic data to record, monitor, or signal temperature changes. ... 
Among the contact temperature sensors are thermocouples and thermistors.

<img src="images\temperature_sensor.png">

### Relay
Connect power(center) pin of module to positive terminal of battery and
gnd(right) of module to breadboard which in turn will be connected to
negative terminal of battery and gnd of arduino board. And relay signal 
pin connect to arduino digital pin 10.
(Note:- We are using a breadboard because we have to connect gnd pin 
of relay module to negative terminal of battery and also with gnd of 
Arduino board.Remember we have to always connect negative terminal 
of external power supply(like battery) to gnd.)
_
Now replace the switch of the water pump with relay by connecting the 
two wires of switch to normally closed(left) and common(center) outlet 
of the relay module.
<img src="images\relay.png">

### Water Tank
A water storage tank holds clean water from your reverse osmosis 
system until demand for water is initiated in the house or business. 
Water is pumped into the tank from the water source, like a well or a 
reverse osmosis system. The tank accumulates water until it is full.
<img src="images\water_tank.png">

### Water Motor
Its function is to slow down the water and increase the pressure. The 
pumped water–new water that's drawn from the well by the suction at 
the jet–then combines with the drive water to discharge into the 
plumbing system at high pressure.
<img src="images\water_motor.png">

## Apps and Online Services

### Arduino IDE
Write and upload programs to Arduino compatible boards, but also, with 
the help of third-party cores, other vendor development boards.
<img src="images\arduino_ide.png">

### Database
For data can then be easily accessed, managed, modified, updated, 
controlled, and organized. Using thingspeak for database.
<img src="images\database.png">

### Wi Fi
For connection between nodemcu and database.
<img src="images\wi_fi.png">

## Block Diagram
<img src="images\block_diagram.png">


## Working
Place the ultrasonic sensor on top of the tank. Ultrasonic sensor calculates the 
distance and according to the code if distance is less than or equal to 5cm it 
switch offs the pump and if the distance is greater than 80(which is 
recommended to be changed according to your need) the relay turn on the 
pump. 
_
(Note:- Ultrasonic sensor is placed at the top hence if the distance 
increases it means the level of water is decreasing and vice-versa.)

## Discussion
In the beginning I planned to use the pH sensor along with the turbidity and 
temperature sensors. But I could not find the pH sensors and turbidity sensors in 
the stores. So I completed the project only using ultrasonic and temperature 
sensors.

Although it was previously reported that the Arduino would use a Nano, it was 
concluded that a Nano was not needed, despite the ability to mount and operate 
all components on the NodeMCU.

Although it was mentioned earlier that Google Firebase will be used for the 
database, it was later used because a cleaner and more user friendly database 
was found than Firebase.
