//based on https://docs.particle.io/guide/getting-started/examples/core/#read-your-photoresistor-function-and-variable

int led = D0; // This is where LED is plugged in. The other side goes to a resistor connected to GND.

int photoresistor = A0; // This is where photoresistor is plugged in. The other side goes to the "power" pin (below).

int touchSensor = A1; // analog output from the touch sensor

int power = A5; // This is the other end of the photoresistor. The other side is plugged into the "photoresistor" pin (above).

const int LIGHT_THRESHOLD = 70; // if there is that little light, we want to turn bike light on
const int TOUCH_THRESHOLD = 800; // if value returned by the touch sensor is greater than this threshold, bike handle is being touched
const int HUMIDITY_THRESHOLD = 95; // if humidity is greater than this threshold, lights should be turned on 

const int CHECKS_DELAY = 5000; // number of miliseconds to wait between consecutive state checks
const int PUBLISH_DELAY = 3; //every PUBLISH_DELAY the main loop runs, we run publishHumidityReq() function

int lastCheckedHumidity;
 
int publishCounter;

void setup() {
    //setup webhook to get current humidity in selected location
    Particle.subscribe("hook-response/aaHumidity", myHandler, MY_DEVICES);
    

    // declaration of all pins
    pinMode(led,OUTPUT); // LED pin is output (lighting up the LED)

    pinMode(touchSensor,INPUT);  //  touch sensor pin is input (reading the sensor data)
    pinMode(photoresistor,INPUT);  //  photoresistor pin is input (reading the photoresistor)


    pinMode(power,OUTPUT); // The pin powering the photoresistor and touch sensor is output (sending out consistent power)

    //write one pin of the photoresistor and touch sensor to be the maximum possible, so that it can be used for power.
    digitalWrite(power,HIGH);



    //managing serial connection for debugging purposes
    Serial.begin(9600);   // open serial over USB
    // wait up to 10 seconds for USB host to connect
    // requires firmware >= 0.5.3
    waitFor(Serial.isConnected, 10000);
    
    lastCheckedHumidity = 0;
    publishCounter = 0;
}


void myHandler(const char *event, const char *data) {
  // Handle the response from weather api with humidity
    Serial.printf("humidity received = %s ",data);
    Serial.println();

    lastCheckedHumidity = parseHumidity(data);
    
    
}

int parseHumidity(const char *hString){
    int humidity = atoi(hString);
    return humidity;

}


void turnOnLight(bool turnOn){
    //turning on the actuator
    if(turnOn){
        digitalWrite(led,HIGH);
    }else{
        digitalWrite(led,LOW);
    }
}


bool checkBikeHandle(){
    //returns true if bike handle is touched
    //false otherwise

    bool handleTouched = false;
    int digitalTouchValue = digitalRead(touchSensor);
    if(digitalTouchValue == 1){
        handleTouched = true;
    }

    return handleTouched;
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

    Serial.printf("checkLight(): read photoresistor value = %d", analogValue);
    Serial.println();

    return isMuchLight;
}

void publishHumidityReq(){
    Serial.printf("PUBLISH COUNTER = %d", publishCounter);
    Serial.println();
    
    //publishing humidity request every PUBLISH_DELAY times the main loop runs
    if(publishCounter == 0){
        Serial.println("there is WiFi, publishing get humidity request");

        Particle.publish("aaHumidity", PRIVATE);

    }else{
        Serial.println("there is WiFi, BUT NOT publishing req");

    }
    publishCounter++;
    if(publishCounter == PUBLISH_DELAY){
        publishCounter = 0;
    }
}

bool isWeatherBad(){
    //returns true if humidity value indicates poor visibility
    //false otherwise
    return (lastCheckedHumidity > HUMIDITY_THRESHOLD);
}

bool checkWiFi(){
    return Particle.connected();
}

void checkLoop(){
    //check if the client is touching the bike handle
    bool handleTouched = checkBikeHandle();
    if(handleTouched){
        //client is using the bike
        //check light conditions
        Serial.println("handle is touched");

        bool isLightOutside = checkLight();
        if(isLightOutside){
            //it is bright enough- turn off the light
            //and check if wifi is available
            Serial.println("it is bright enough, turning off the light");
            turnOnLight(false);
            
            bool wifiAvailable = checkWiFi();
            if(wifiAvailable){
                //photon is able to connect to WiFi
                //checking weather
                Serial.println("there is WiFi");
                
                publishHumidityReq();
                

                bool weatherIsBad = isWeatherBad();
                if(weatherIsBad){
                    //weather requires bike light
                    //turn on the light
                    Serial.println("weather is bad");

                    turnOnLight(true);
                }
            }
        }else{
            //it is dark outside
            //turn on the light
            Serial.println("it is dark, turning on the light");
            turnOnLight(true);
        }
    }else{
        //handle is released
        //turn off the light
        Serial.println("handle is released, turning off the light");

        turnOnLight(false);
        //set default humidity value, so that we don't work with outdated data
        lastCheckedHumidity = 0;
    }
    Serial.println();
}

void loop() {
    checkLoop();
    
    //wait CHECKS_DELAY between checks
    delay(CHECKS_DELAY);
   

}