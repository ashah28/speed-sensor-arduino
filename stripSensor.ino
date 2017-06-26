
int stripIRSensor = 2;
int distPerStripe = 150/12;
unsigned long refreshInTime = 300;
float perTimeUnit = 1000.0/refreshInTime;

float cmSecToKmHrMultiplier = 3600.0/(100.0 * 1000.0);

int lastValueIR = 0;
int stripsTravelledLastSecIR = 0;
unsigned long timeElapsed = 0;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(stripIRSensor, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
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
    float speedRate = distanceTravelled * perTimeUnit;
    String data = "[" + 
//    String(stripsTravelledLastSecIR)
    String(speedRate * cmSecToKmHrMultiplier ) + "]"
//    + ", " +
//    String(speedRate)
    ;
    Serial.println(data);
    stripsTravelledLastSecIR = 0;
    timeElapsed = millis();
  }
}
