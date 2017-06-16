
int stripSensor = 2;
unsigned long lastUpdate = 0;
int lastValue = 0;
bool plot = false;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(250000);
  pinMode(stripSensor, INPUT);
  //lastUpdate = millis();
  lastUpdate = micros();
}

int last_delta;

// the loop routine runs over and over again forever:
void loop() {
  int stripSensorResult = digitalRead(stripSensor);
  int delta;
  if(lastValue != stripSensorResult)
  {
    lastValue = stripSensorResult;
    delta = micros()/100 - lastUpdate;
    lastUpdate = micros()/100;

    //Added code to minimise false reportings if this delta is drastically different than the last
    if(plot && abs(delta - last_delta) > last_delta * .25 )
    {
      last_delta = delta;
      return;
     }
    last_delta = delta;


    if(plot)
    {
      Serial.print(stripSensorResult);
      Serial.print(",");
      Serial.print(delta);
      Serial.print(",");
      Serial.println((float)delta/1000);
    }
    else
    {
      Serial.println(1);
    }
  }
}
