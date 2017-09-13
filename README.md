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
