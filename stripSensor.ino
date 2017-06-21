
int stripIRSensor = 2;
int hallSensor = 3;
int hall2Sensor = 4;

int lastValueIR = 0;
int lastValueHall = 0;
int lastValueHall2 = 0;

int stripsTravelledLastSecIR = 0;
int stripsTravelledLastSecHall = 0;
int stripsTravelledLastSecHall2 = 0;

unsigned long int timeElapsed = 0;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(stripIRSensor, INPUT);
  pinMode(hallSensor, INPUT);
  pinMode(hall2Sensor, INPUT);
  timeElapsed = micros();
}

//int last_delta;


// the loop routine runs over and over again forever:
void loop() {
  int stripIRSensorResult = digitalRead(stripIRSensor);
  int stripHallSensorResult = digitalRead(hallSensor);
  int stripHall2SensorResult = digitalRead(hall2Sensor);
  
  if(lastValueIR != stripIRSensorResult)
  {
    stripsTravelledLastSecIR++;
    lastValueIR = stripIRSensorResult;
  }

  if(lastValueHall != stripHallSensorResult)
  {
    stripsTravelledLastSecHall++;
    lastValueHall = stripHallSensorResult;
  }

  if(lastValueHall2 != stripHall2SensorResult)
  {
    stripsTravelledLastSecHall2++;
    lastValueHall2 = stripHall2SensorResult;
  }  
  
  if(micros() - timeElapsed >= 10000)
  { 
    String data = String(stripsTravelledLastSecIR) + ","+ String(stripsTravelledLastSecHall + 5) 
    + "," + String(stripsTravelledLastSecHall2 + 10) 
    +  "," + String(stripsTravelledLastSecHall - stripsTravelledLastSecHall2)
    ;
    Serial.println(data);
    stripsTravelledLastSecIR = 0;
    stripsTravelledLastSecHall = 0;
    stripsTravelledLastSecHall2 = 0;
    timeElapsed = micros();
  }
  
//  unsigned long int b = micros();
//  String data = String(b-a) ;//+ "   " +String(a)+ "   " +String(b);
//  Serial.println(data);
}
