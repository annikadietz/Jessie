// Engine constants
const int left_wheel = 3;
const int left_wheel_backwards = 2;
const int right_wheel = 9;
const int right_wheel_backwards = 4;
#define E1 11
#define E2 6


/*
 * Controls a given wheel
 * @param wheel The wheel to control
 * @param backwards Make the wheel drive backwards
 * @param state The wheel is spinning
 */
void control_wheel(char wheel[], boolean backwards, boolean state){
  if(wheel == "left"){
    digitalWrite((backwards == true) ? left_wheel_backwards : left_wheel, state);
  } else {
    digitalWrite((backwards == true) ? right_wheel_backwards : right_wheel, state);
  }
}

/*
 * Make all wheels stop
 */
void halt(){
  control_wheel("left", true, LOW);
  control_wheel("left", false, LOW);
  control_wheel("right", true, LOW);
  control_wheel("right", false, LOW);
}

/*
 * Make the car go straight ahead
 * (so not in reverse)
 */
void straight(){
  // Disable backwards
  control_wheel("left", true, LOW);
  control_wheel("right", true, LOW);

  // Enable going forward on both wheels
  control_wheel("left", false, HIGH);
  control_wheel("right", false, HIGH);    
}

 /*
 * Make the car go reversed
 * (so not going forward)
 */
void backwards(){
  // Disable going forward
  control_wheel("left", false, LOW);
  control_wheel("right", false, LOW);

  // Enable going backwards on both wheels
  control_wheel("left", true, HIGH);
  control_wheel("right", true, HIGH);    
}

void turnRight(){
  // Enable going backwards on right wheel
  control_wheel("left", false, HIGH);
  control_wheel("right", true, HIGH);  
  
}

void turnLeft(){
  // Enable going backwards on right wheel
  control_wheel("right", false, HIGH);
  control_wheel("left", true, HIGH);  
  
}

void moveRight(int speed)
{

  analogWrite(left_wheel, speed);
  analogWrite(right_wheel_backwards, speed);
}

void moveLeft(int speed)
{
  analogWrite(right_wheel, speed);
  analogWrite(left_wheel_backwards, speed);  
}

void forwardSpeed(int speed)
{
  analogWrite(left_wheel, speed);
  digitalWrite(left_wheel_backwards, LOW);
  analogWrite(right_wheel, speed);
  digitalWrite(right_wheel_backwards, LOW);

}

void testMotors(int speed)
{
  analogWrite(left_wheel, 100);
  analogWrite(right_wheel, 200);
  //digitalWrite(left_wheel, HIGH);
  //digitalWrite(right_wheel, HIGH);
}


void turnAround()
{
  halt();
  digitalWrite(left_wheel_backwards, HIGH);
  delay(1000);
  halt();
  digitalWrite(right_wheel, HIGH);
  delay(1000);
  halt();
}



