#include "IBT.h"

//Wheels

IBT lw(2,3);
IBT rw(4,5);
IBT rf(6,7);
IBT rb(8,9);

String receivedData = "";

double b = 15;
double r = 16.5;
double max_speed = 7.2;

double pwm_l = 0;
double pwm_r = 0;


void process_vel(double linear, double angular){
  double r_wheel_vel = constrain(((linear+(angular*(b/2)))/r),-max_speed,max_speed);
  double l_wheel_vel = constrain(((linear-(angular*(b/2)))/r),-max_speed,max_speed);

  pwm_l = map(r_wheel_vel,-max_speed,max_speed,-200,200);
  pwm_r = map(l_wheel_vel,-max_speed,max_speed,-200,200);

  lf.setRawSpeed(pwm_l);
  lb.setRawSpeed(pwm_l);
  rf.setRawSpeed(-pwm_r);
  rb.setRawSpeed(-pwm_r);
}



void setup() {
  Serial.begin(115200);
  Serial.println("Ready to receive data");
}

void loop() {
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();  

    // Check for end of line character
    if (incomingChar == '\n') {
      processCommand(receivedData);  // Process the complete string
      receivedData = "";            // Clear the string for the next command
    } else {
      receivedData += incomingChar;  // Append the character to the string
    }
  }
}

void processCommand(String command) {
  // Print the received command for debugging
  Serial.print("Received command: ");
  Serial.println(command);

  // Example: Parse linear and angular velocity from the command
  if (command.startsWith("L") && command.indexOf("A") && command.indexOf("B") && command.indexOf("R") && command.indexOf("M") > 0) {
    String linear = command.substring(1, command.indexOf("A"));
    String angular = command.substring(command.indexOf("A") + 1,command.indexOf("B")-1);
    String b_str = command.substring(command.indexOf("B")+1,command.indexOf("R")-1);
    String radius_str = command.substring(command.indexOf("R")+1,command.indexOf("M")-1);
    String max_str = command.substring(command.indexOf("M")+1);

    float linearVelocity = linear.toFloat();
    float angularVelocity = angular.toFloat();
    //made this variable too
    r = radius_str.toFloat();
    b = b_str.toFloat();
    max_speed = max_str.toFloat();
    process_vel(linearVelocity,angularVelocity);
    delay(150);
    
  } else {
    Serial.println("Invalid command format!");
  }
}