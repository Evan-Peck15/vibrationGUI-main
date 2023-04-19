void output_map(){

  // Set the piston to up or down
  ConnectorIO1.State(output_pist);

  // Turn the rotation motor on or off
  ConnectorIO3.State(output_motor);

  // Change the direction of rotation of the rotation motor
  ConnectorIO2.State(forward_motor);
  
  // If it is told to, change the speed of the vibration motor
  if (change_speed){
    analogWrite(piston_analog, setForce, CURRENT);
    change_speed = !change_speed;
  }
}
