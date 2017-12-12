//based on https://docs.particle.io/guide/getting-started/examples/core/#read-your-photoresistor-function-and-variable

int led = D0; // This is where LED is plugged in. The other side goes to a resistor connected to GND.

int photoresistor = A0; // This is where photoresistor is plugged in. The other side goes to the "power" pin (below).

int touchSensor = A1; // analog output from the touch sensor

int power = A5; // This is the other end of the photoresistor. The other side is plugged into the "photoresistor" pin (above).

const int LIGHT_THRESHOLD = 100; // if there is that little light, we want to turn bike light on
const int CHECKS_DELAY = 5000; // number of miliseconds to wait between consecutive state checks
const int TOUCH_THRESHOLD = 800; // if value returned by the touch sensor is greater than this threshold, bike handle is being touched

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

}


void myHandler(const char *event, const char *data) {
  // Handle the response from weather api with humidity
    Serial.printf("humidity received = %s ",data);
    Serial.println();

    parseHumidity(data);
    
}

void parseHumidity(const char *hString){
    int humidity = atoi(hString);
    Serial.printf("our int = %d ",humidity);
    Serial.println();

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

    
    Serial.printf("checkBikeHandle(): touch sensor digital value = %d",digitalTouchValue);
    Serial.println();

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

int switcher = 0;
void loop() {
    //Particle.publish("aaHumidity", PRIVATE);
    //Serial.printf("sent humidity req ");
    //Serial.println();

    turnOnLight(true);
    
    bool handleTouched = checkBikeHandle();
    checkLight();
 
    //wait CHECKS_DELAY between checks
    delay(CHECKS_DELAY);

}
