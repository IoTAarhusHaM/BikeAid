// This #include statement was automatically added by the Particle IDE.

int led = D7;  // The on-board LED

void setup() {
    pinMode(led, OUTPUT);
    Particle.subscribe("hook-response/gdaWeather", myHandler, MY_DEVICES);
    
    
    //managing serial connection for debugging purposes   
    Serial.begin(9600);   // open serial over USB
    // wait up to 10 seconds for USB host to connect
    // requires firmware >= 0.5.3
    waitFor(Serial.isConnected, 10000);

}

void d_log(const char *msg){
    //TODO for debugging only
    //printing message to serial usb output

   // publishData(eventName, val);
    Serial.printf("%s ",msg);
    Serial.println();
    
}


void myHandler(const char *event, const char *data) {
  // Handle the integration response
    d_log("my handler called! ");
    d_log(data);
    
    
   // char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    /*StaticJsonBuffer<400> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(data);

    const char* visibilityVal = root["visibility"];
    
    d_log("visibilityVal = ");

    d_log(visibilityVal);*/
}
          


void loop() {
  digitalWrite(led, HIGH);   // Turn ON the LED

  Particle.publish("gdaWeather", PRIVATE);
  d_log("published get req ");

  delay(10000);               // Wait for 30 seconds

  digitalWrite(led, LOW);    // Turn OFF the LED
  delay(10000);               // Wait for 30 seconds
}