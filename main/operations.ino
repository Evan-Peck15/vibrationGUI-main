void operations(){

  // Print the current status of the reed switch
  if (reed != oldreed){
    Serial.print("Now ");
    Serial.println(reed);
  }
  oldreed = reed;


// Check if all variables have been received and the test is ready to start
// Turns on subsystems and runs test
  if (test_start == true && reed == true){
    test_start = false;
    // Turn on systems
    // Start tracking time
  }

// Check stop conditions (STOP command received, time limit reached or reed switch is opened
// If either condition is met, stop ALL subsystems
  if (test_stop == true || reed == false){
    // Turn off ALL systems
  }
  
  // change fequency up to 2047 and then put it back down
//  if  ((current_time - start_time) >= allowed_time) {
//    if (output_i < 1847){
//      output_i+=10;
//    }
//    else if (output_i >= 1847){
//      output_i = 410;
//    }
//    start_time = millis();
//  }

  // used for calibrating outout to input
//  if  ((current_time - start_time) >= allowed_time) {
//    if (output_i <= 2015){
//      output_i += 32;
//    }
//    else if ((output_i > 2015) && (output_i != 2047)) {
//      output_i = 2047;
//    }
//    else if (output_i == 2047){
//      output_i = 410;
//    }
//    start_time = millis();
//  }
  
}
