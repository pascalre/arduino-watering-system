#define SENSOR 7
#define PUMP   8

bool isWaterInBarrel(int pin);
void pumpWater(unsigned long seconds);

unsigned long timeToWater =   120000;               // 2 minutes in ms
unsigned long interval_1  = 57600000 - timeToWater; // 16 hours in ms (time between 18:00 and 10:00)
unsigned long interval_2  = 28800000 - timeToWater; // 8 hours in ms (time between 10:00 and 18:00)

void setup() {
  pinMode(SENSOR, INPUT);
  digitalWrite(SENSOR, HIGH);
  pinMode(PUMP, OUTPUT);
}

void loop() {
  pumpWater(timeToWater);
  delay(interval_1);
  pumpWater(timeToWater);
  delay(interval_2);
}

void pumpWater(unsigned long seconds) {
  bool doPumpWater = true;
  unsigned long startTime = millis();
  while (doPumpWater && isWaterInBarrel(SENSOR)) {
    digitalWrite(PUMP, HIGH);
    if((millis() - startTime) > seconds) {
      doPumpWater = false;
    }
  }
  digitalWrite(PUMP, LOW);  
}

bool isWaterInBarrel(int pin) {
  if(digitalRead(pin) == HIGH) {
    delay(10);
    if(digitalRead(pin) == HIGH) {
      return false;
    }
  } else return true;
}
