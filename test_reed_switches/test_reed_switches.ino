const int inputPin = 8;
int val = 0;

void setup() {
  pinMode(inputPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(inputPin);
  if(val == LOW) {
    Serial.println("Door open");
  } else {
    Serial.println("Door closed");
  }
}
