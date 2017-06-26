#include <Filter.h>

Moving_average ma2(5, 0); // change the value divider appropriately to avoid int overflow

//Need a divide the speedRate to keep it as an int and avoid overflow
int valueDivider = 2;

int stripIRSensor = 2;
int distPerStripe = 150/12;
//refresh time in miliseconds
unsigned long refreshInTime = 100;
float perTimeUnit = 1000.0/refreshInTime;

float cmSecToMHrMultiplier = 3600.0/(100.0);

int lastValueIR = 0;
int stripsTravelledLastSecIR = 0;
unsigned long timeElapsed = 0;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(stripIRSensor, INPUT);
//  pinMode(3, INPUT);
//  pinMode(4, INPUT);
  timeElapsed = millis();
}

// the loop routine runs over and over again forever:
void loop() {
  int stripIRSensorResult = digitalRead(stripIRSensor);
  
  if(lastValueIR != stripIRSensorResult)
  {
    stripsTravelledLastSecIR++;
    lastValueIR = stripIRSensorResult;
  }

  if(millis() - timeElapsed >= refreshInTime)
  { 
    int distanceTravelled = stripsTravelledLastSecIR * distPerStripe;
    //speed is a keyword
    //speedrate is cm travelled per sec
    float speedRate = distanceTravelled * perTimeUnit * cmSecToMHrMultiplier;
    //Data is current speed in m/hr /(10*valueDivider)
    int filter2 = ma2.filter(int(speedRate/(10 * valueDivider))) * valueDivider;
    String data = "[" + String(filter2) + "]";
    Serial.println(data);
    stripsTravelledLastSecIR = 0;
    timeElapsed = millis();
  }
}
