void receive_comm() {
  
  incomingString = Serial.read;
  Serial.print("I just received this: ");
  Serial.println(incomingString);
  incomingString = Serial.readStringUntil(":")

  if (incomingString == "Force") {
    switcher_var = 1;
  }
  else if (incomingString == "Rotation") {
    switcher_var = 2;
  }
  else if (incomingString == "Time"){
    switcher_var == 3;
  }
  else if(incomingString == "Go"){
    switcher_var = 4;
  }
  else if(incomingString == "STOP"){
    switcher_var = 5;
  }

  switch (switcher_var){

    case 1:
    setForce = round(Serial.readStringUntil(',').toFloat());
    setForce = setForce * 3.41; //Convert from Newtons to Analog
    // Confirm equation, involves max N produced by piston
    break;

    case 2:
    setRotation = round(Serial.readStringUntil(',').toFloat());
    if (setRotation != 0 && setRotation != 999){
      RotFreq = 1/ setRotation;
    }
    break;

    case 3:
    setRunTime = round(Serial.readStringUntil(',').toFloat());
    if (setRunTime == 999){
      // Run until STOP button pressed
    }
    break;

    case 4:
    test_start = true;
    break;

    case 5:
    test_stop = true;
  }

}
