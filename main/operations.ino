void operations() {

  // Print the current status of the reed switch
  if (reed != oldreed) {
    //Serial.print("Now ");
    //Serial.println(reed);
  }
  oldreed = reed;


  // Check if all variables have been received and the test is ready to start
  // Turns on subsystems and runs test
  if (test_start == true && reed == true) {
    test_start = false;
    // Turn on systems
    ConnectorIO4.State(true);
    if (pistonActive == false) {
      //set Piston to pull up at ~500analog
      output_pist = false; //Direction up  ****************** Check if correct bool
      
      setForce = 500;                    //***************** Check if this force can keep piston up during vibration
    }
    else if (pistonActive == true) {
      output_pist = true;                //****************** Check if correct bool
    }

    if (setRotation == 999) {
      // Turn rotation motor off
      output_motor = false; //Motor off ******************** Check if correct bool
      rotOscil = false;
    }
    else if (setRotation != 999) {
      //Turn rotation motor on
      output_motor = true; //Motor on ********************** Check if correct bool
      forward_motor = true; //Motor direction, true=CW, false=CCW   *****************Check if correct
      if (setRotation != 0.00) {
        //Check if motor needs to oscillate
        rotOscil = true;
      }
      else if (setRotation == 0.00) {
        rotOscil = false;
      }
    }
    // Start tracking time
    startTime = micros();
    operating = true;
  }

  // Check time dependent actions
  // Rotation and run time
  if (timeStop == true && operating == true) {
    T = micros();
    runTime = T - startTime;
    if (runTime >= setRunTime){   //If run time has been exceeded, stop the test
      test_stop = true;
    }
  }

  if (rotOscil == true && operating == true) {
    T = micros();
    if ((T-lastOscil) >= oscilTime){
      forward_motor = !forward_motor;
      lastOscil = micros();
    }
  }


  // Check stop conditions (STOP command received, time limit reached or reed switch is opened
  // If either condition is met, stop ALL subsystems
  if (test_stop == true || reed == false) {
    // Turn off ALL systems
    operating = false;
    timeStop = false;
    test_stop = false;
    rotOscil = false;
    output_pist = false; //Direction up
    setForce = 300;
    output_motor = false;
    ConnectorIO4.State(false);
    //Serial.print("STOP:\nHeight:69,89,99\nTime:420,520,620\n");   //Send stop command to Python to stop VFD
    Serial.print("STOP");
  }

}
