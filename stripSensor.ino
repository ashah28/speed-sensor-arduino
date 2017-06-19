
int stripSensor = 2;
unsigned long lastUpdate = 0;
int lastValue = 0;
unsigned long int timeElapsed = 0;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(stripSensor, INPUT);
  timeElapsed = micros();
}

int last_delta;
int stripsTravelledLastSec = 0;

// the loop routine runs over and over again forever:
void loop() {
  int stripSensorResult = digitalRead(stripSensor);
  int delta;
  if(lastValue != stripSensorResult)
  {
    stripsTravelledLastSec++;
    lastValue = stripSensorResult;
    delta = micros()/100 - lastUpdate;
    lastUpdate = micros()/100;

    //Added code to minimise false reportings if this delta is drastically different than the last
//    if(abs(delta - last_delta) > last_delta * .75 )
//    {   
//      Serial.print("===>");
//      Serial.print(',');   
//      Serial.print(delta);
//      Serial.print(',');
//      Serial.print(last_delta);
//      Serial.print(',');
//      Serial.println(delta - last_delta
//      );
//      last_delta = delta;
//      //return;
//     }
    last_delta = delta;
  }
  
  if(micros() - timeElapsed >= 200000)
  {      
    Serial.println(stripsTravelledLastSec);
//    Serial.print(',');
//    Serial.println(micros() - timeElapsed);
      stripsTravelledLastSec = 0;
      timeElapsed = micros();
  }
//  else
//    Serial.println("0");
}
