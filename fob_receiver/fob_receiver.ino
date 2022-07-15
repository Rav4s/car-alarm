// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

//Initialize pins
const int trigPin = 3;
const int echoPin = 2;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();

  // setup hcsr04 sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // System is unarmed by default
  boolean armed = false;
  
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  double duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  double distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
    
  // Set buffer to size of expected message
  uint8_t buf[3];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen))
  {
    int length = strlen(buf);
    buf[length - 1] = '\0';
    Serial.println((char*)buf);
  }

  delay(1000);
}
