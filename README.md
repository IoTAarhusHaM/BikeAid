# BikeAid
Project for IoT class, fall semester 2017/18

## Meeting the requirements
sensors- light sensor (photoresistor), fsr (pressure sensor) on bike handle


actuator- a bike light that we can control from photon


using web data- weather conditions in the area where the photon is


technical platform- photon


## BikeAid
BikeAid device will have a touch sensor on bike handle. 


When a client holds the handle, Photon will read input from light sensor and if wifi is not available, it will use photoresistor to check how much light there is.


If lighting is bad it will turn on bike light.


If on the other hand there is wifi, Photon will connect to the internet to check weather conditions in current location and adjust bike light accordingly.

![projectSchema](https://user-images.githubusercontent.com/20126908/30375465-e9b5b3c0-9888-11e7-8ca1-4efdb8320327.png)

## State Diagram
![Alt text](State_Diagram.jpg?raw=true "State Diagram for the product")


questions and problems


... checking wifi connectivity- is this generally done? (maybe this approach: https://community.zerynth.com/discussion/322/function-for-checking-wifi-connection ?)


... connecting photon and all the sensors and components to the breadbord (for now led light that's supposed to be lit while the program runs tends to go out because the wire connecting it to power doesn't touch photon's power supply at all times)
