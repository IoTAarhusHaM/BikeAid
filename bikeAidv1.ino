//based on https://docs.particle.io/guide/getting-started/examples/core/#read-your-photoresistor-function-and-variable

int led = D0; // This is where LED is plugged in. The other side goes to a resistor connected to GND.

int photoresistor = A0; // This is where photoresistor is plugged in. The other side goes to the "power" pin (below).

int power = A5; // This is the other end of the photoresistor. The other side is plugged into the "photoresistor" pin (above).

const int LIGHT_THRESHOLD = 100; //if there is that little light, we want to turn bike light on
const int CHECKS_DELAY = 1000; // number of miliseconds to wait between consecutive state checks 

void setup() {

    // First, declare all of pins.
    pinMode(led,OUTPUT); // LED pin is output (lighting up the LED)
    pinMode(photoresistor,INPUT);  //  photoresistor pin is input (reading the photoresistor)
    pinMode(power,OUTPUT); // The pin powering the photoresistor is output (sending out consistent power)

    //write one pin of the photoresistor to be the maximum possible, so that it can be used for power.
    digitalWrite(power,HIGH);

    
    //managing serial connection for debugging purposes   
    Serial.begin(9600);   // open serial over USB
    // wait up to 10 seconds for USB host to connect
    // requires firmware >= 0.5.3
    waitFor(Serial.isConnected, 10000);
    
}

void d_log(char *msg, int val){
    //TODO for debugging only
    //printing message to serial usb output

   // publishData(eventName, val);
    Serial.printf("%s [%d] ",msg, val);
    Serial.println();
    
}

bool checkBikeHandle(){
    //returns true if bike handle is touched
    //false otherwise
    
    //TODO reading touch sensor data
    return true;
}

bool checkLight(){
    //returns true if there is enough light
    //false otherwise
    bool isMuchLight = true;
    //checking photoresistor value
    int analogValue = analogRead(photoresistor);
    
    if(analogValue < LIGHT_THRESHOLD){
        isMuchLight = false; 
    }
    
    //TODO debugging part
    d_log("checkLight(): read photoresistor value = ", analogValue);
    //end of debugging part
    
    return isMuchLight;
}

bool checkWiFi(){
    //returns true if WiFi is available
    //false otherwise
    return false;
}

bool checkWeather(){
    //returns true if weather is so bad, that it bike light is needed
    //false otherwise
    return false;
}

void turnOnLight(bool turnOn){
    //turning on the actuator
    if(turnOn){
        digitalWrite(led,HIGH);
    }else{
        digitalWrite(led,LOW);
    }
}

void loop() {
    //TODO we chould change nested ifs into two chained conditions

    //check if the client is touching the bike handle
    bool handleTouched = checkBikeHandle();
    if(handleTouched){
        //client is using the bike
        //check light conditions
        d_log("handle is touched ",1);
        bool isLightOutside = checkLight();
        if(isLightOutside){
            //it is bright enough- turn off the light
            //and check if wifi is available
            d_log("it is bright enough, turning off the light ",1);
            turnOnLight(false);
            
            bool wifiAvailable = checkWiFi();
            if(wifiAvailable){
                //photon is able to connect to WiFi
                //checking weather
                d_log("there is WiFi ",1);

                bool weatherIsBad = checkWeather();
                if(weatherIsBad){
                    //weather requires bike light
                    //turn on the light
                    d_log("eather is bad ",1);

                    turnOnLight(true);
                }
            }
        }else{
            //it is dark outside
            //turn on the light
            d_log("it is dark, turning on the light ",1);

            turnOnLight(true);
        }
    }else{
        //handle is released
        //turn off the light
        turnOnLight(false);
    }

    //wait CHECKS_DELAY between checks
    delay(CHECKS_DELAY);

}

void publishData(char *eventName, int val) {
	// publishes val value

	char buf[256];
	snprintf(buf, sizeof(buf), "%d", val);
	Serial.printlnf("publishing %s", buf);
	Particle.publish(eventName, buf, PRIVATE);
}