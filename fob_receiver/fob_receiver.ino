// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

// System is unarmed by default
boolean armed = false;

// Relay trigger pin
const int RELAY_PIN = 3;

// Reed switches input
const int reedInput = 8;
int switchVal = 0;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();

  // Set up relay pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  delay(500);

  // Set up reed switches
  pinMode(reedInput, INPUT_PULLUP);
    
  // Setup Serial Monitor
  Serial.begin(9600);
}


// Check if doors are closed based on reed switches
String reedSwitches() {
  switchVal = digitalRead(reedInput);
  if(switchVal == LOW) {
    Serial.println("Door open");
    return "open";
  } else {
    Serial.println("Door closed");
    return "closed";
  }
}

// Arm/disarm based on transmitted message
void checkMessage(String message) {
  message.trim();
  Serial.println(message);
  
  if(message == "01") {
    arm();
  } else if(message == "00") {
    disarm();
  } else {
    Serial.println("Error! Invalid message");
  }
}

// Trigger siren using relay
void trigRelay(String onoff) {
  if(onoff == "on") {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Alarm on!");
  } else if(onoff = "off") {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Alarm off!");
  } else {
    Serial.println("Error! Invalid on/off command");
  }
  
}

// Arm system
void arm() {
  armed = true;
  Serial.println("System armed");

}

// Disarm system
void disarm() {
  trigRelay("off");
  armed = false;
  Serial.println("System disarmed");
}

// Main
void loop()
{   
  // Set buffer to size of expected message
  uint8_t buf[2];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen))
  {
    int length = strlen(buf);
    buf[length - 1] = '\0';
    String message = (char*)buf;
    checkMessage(message);
  }

  if(armed == true && reedSwitches() == "open") {
    trigRelay("on");
  }
}
