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


20.10.17 status report: action skeleton

22.11.17 status report: all sensors read correctly, weather webhook is configured so that it works as expected (requested response body template works well); 

12.12.17 status report: finishing touches, WiFi checks, testing

to be done: 

+ DONE! making everything connect well


+ DONE! getting the touch sensor


+ DONE! inspecting web api, managing webhook


+ DONE! parsing visibility (from string to int) and setting some treshold


+ DONE! checking wifi


+ DONE! getting it all together
