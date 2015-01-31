#include <QTRSensors.h>

#define ROBORIO_PORT 11
#define SENSOR_PORT  12
#define LED_PORT     13

#define ON HIGH
#define OFF LOW

#define DEBUG 0

// The sensor threshold should be between the raw value returned
// when above red/blue carpet  and white ramps.
#define SENSOR_THRESHOLD 1000

QTRSensorsRC qtrrc;

void setLed(int state) {
  digitalWrite(LED_PORT, state);
}

void setRoborio(int state) {
  digitalWrite(ROBORIO_PORT, state); 
}

// Reads a QTR-1RC sensor and returns a value between 0 and the sensor timeout as set
// during init().  Default is 0 (~light) to 2000 (~dark).
unsigned int readSensor() {
  unsigned int values[] = { 0 };
  
  qtrrc.read(values);
#if DEBUG
  Serial.print("Sensor => ");
  Serial.println(values[0], DEC);
#endif
  
  return values[0];
}

// Returns true if the sensor is triggered *count* times in a row.
bool sensorTrigger(unsigned int count = 3) {
  while (count-- > 0) {
    if (readSensor() >= SENSOR_THRESHOLD) { return false; }
  }
  
  return true;
}

void setup(){
  pinMode(ROBORIO_PORT, OUTPUT);
  pinMode(SENSOR_PORT, INPUT_PULLUP);
  pinMode(LED_PORT, OUTPUT);

#if DEBUG
  Serial.begin(9600);
#endif

  qtrrc.init((unsigned char[]) {SENSOR_PORT}, 1);
  setLed(OFF);
}

void loop(){
  if (sensorTrigger()) {
    setRoborio(LOW);
    setLed(ON);
  } else {
    setRoborio(HIGH);
    setLed(OFF);
  }    
}



