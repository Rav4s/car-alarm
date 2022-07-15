/ Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop()
{
  // Set buffer to size of expected message
  uint8_t buf[4];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen))
  {
    int length = strlen(buf);
    buf[length - 1] = '\0';
    Serial.println((char*)buf);
  }
}
