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

void setup()
{
  // Initialize ASK Object
  rf_driver.init();

  // Set up relay pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  delay(500);
    
  // Setup Serial Monitor
  Serial.begin(9600);
}

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

void trigRelay(String onoff) {
  if(onoff == "on") {
    digitalWrite(RELAY_PIN, HIGH);
  } else if(onoff = "off") {
    digitalWrite(RELAY_PIN, LOW);
  } else {
    Serial.println("Error! Invalid on/off command");
  }
  
}

void arm() {
  armed = true;
  trigRelay("on");
  Serial.println("System armed");

}

void disarm() {
  armed = false;
  trigRelay("off");
  Serial.println("System disarmed");
}

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
}
