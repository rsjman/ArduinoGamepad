/*
 * Example of working 2 Thumbsticks (PS2 Thumbstick for Arduino) with Calibration
 * Connect first thumbstick X to A1, Y to A0
 *         second thumbstick X to A3,Y to A2
 */
//including a library
#include <Gamepad.h>

//initialize a centers of axises for calibration
int leftXcenter = 1;  // left X axis original center value
int leftYcenter = 7;  // left Y axis original center value
int rightXcenter = 1;  // right X axis original center value
int rightYcenter = 1;  // right Y axis original center value

int CalVal(int val, int centerVal){
  if(val < centerVal){
    val = map(val, -127, centerVal, -127, 0);
  }else if(val > centerVal){
    val = map(val, centerVal, 127, 0, 127);
    
  }else if(val == centerVal){
    val = 0;
  }
  return val;
}


//Initializing a Gamepad
Gamepad gp;
void setup() {
  //initializing inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(3,  INPUT_PULLUP);
  pinMode(4,  INPUT_PULLUP);
}

void loop() {
  int lx, ly, rx, ry;
  lx = analogRead(A1);
  ly = analogRead(A0);
  rx = analogRead(A3);
  ry = analogRead(A2);
  // define Axis Value
  lx = map(lx, 0, 1023, -127, 127);
  ly = map(ly, 0, 1023, -127, 127);

  rx = map(rx, 0, 1023, -127, 127);
  ry = map(ry, 0, 1023, -127, 127);
  lx = changeVal(lx, leftXcenter);
  ly = changeVal(ly, leftYcenter);
  rx = changeVal(rx, rightXcenter);
  ry = changeVal(ry, rightYcenter);

  gp.setLeftXaxis(lx);
  gp.setRightXaxis(rx);
  //because i have placed a thumbstick in breadboard, i must invert a Y axis and swap X and Y axises
  gp.setLeftYaxis(ly);
  gp.setRightYaxis(ry);

  int rightStickButton, leftStickButton;
  rightStickButton = digitalRead(3);
  leftStickButton = digitalRead(4);

  if(rightStickButton == LOW)
	  gp.setButtonState(11, true);
  else
	  gp.setButtonState(11, false);

  if(leftStickButton == LOW)
	  gp.setButtonState(10, true);
  else
	  gp.setButtonState(10, false);
  delay(20);
}
