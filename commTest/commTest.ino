String incomingString;
float setFreq;
float setForce;
float setRotation;
float setRunTime;
bool input_switcher = false;
int switcher_var;
void setup() {
  Serial.begin(9600);

}

void loop() {
  if (Serial.available() > 0) {
//    incomingString = Serial.readString();
    incomingString = Serial.readStringUntil(':');
    Serial.print("I just recieved this: ");
    Serial.println(incomingString);
  if (incomingString == "Freq"){
    switcher_var = 1;
  }
  else if (incomingString == "Force"){
    switcher_var = 2;
  }
  else if (incomingString == "Rotation"){
    switcher_var == 3;
  }
  else if (incomingString == "Time"){
    switcher_var == 4;
  }
    switch (switcher_var) {
      case 1:
        setFreq = round(Serial.readStringUntil(',').toFloat());
        //Serial.print("Freq: ");
        //Serial.println(setFreq, 2);
        break;

      case 2:
        setForce = round(Serial.readStringUntil(',').toFloat());
        //Serial.print("Force: ");
        //Serial.println(setForce, 2);
        break;

      case 3:
        setRotation = round(Serial.readStringUntil(',').toFloat());
        //Serial.print("Rotation: ");
        //Serial.println(setRotation, 2);
        break;

      case 4:
        setRunTime = round(Serial.readStringUntil(',').toFloat());
        //Serial.print("Run Time: ");
        //Serial.println(setRunTime, 2);
        break;
    }
  }

  float freqResults[] = {setFreq};
  float forceResults[] = {setForce};
  float rotationResults[] = {setRotation};
  float timeResults[] = {setRunTime};
  
  int startTime = micros();
  int T = micros();
  int endTime = startTime + (setRunTime*1000000);
  float interval = (setRunTime*1000000) / 50;
  int i = 1;
  float runTime =0;
  float del_t = 0;
  float oldT = 0;
  while(runTime <= endTime){
    if (del_t >= interval){
      freqResults[i] = T + 50;
      forceResults[i] = -T +300;
      rotationResults[i] = sin(T);
      timeResults[i] = T-startTime;
    }
    oldT = T;
    T = micros();
    del_t = T - oldT;
    runTime = T-startTime;
  }

  String Freq = "Freq:";
  String Force = "Force:";
  String Rotation = "Rotation:";
  String Time = "Time:";
  
  for (int i=0; i<=50; i++){
    Freq.concat(freqResults[i]);
    Force.concat(forceResults[i]);
    Rotation.concat(rotationResults[i]);
    Time.concat(timeResults[i]);
  }
  String resultsString = Freq + Force + Rotation + Time;
  Serial.print(resultsString);
}
