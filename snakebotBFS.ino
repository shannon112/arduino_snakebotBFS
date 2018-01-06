#include <Tlc5940.h>
#include <tlc_animations.h>
#include <tlc_config.h>
#include <tlc_fades.h>
#include <tlc_progmem_utils.h>
#include <tlc_servos.h>
#include <tlc_shifts.h>
#include <Servo.h>
#include "Tlc5940.h"
#include "tlc_servos.h"

#define DELAY_TIME      20

//distance
float distance;
#define TRIGPIN 4
#define ECHOPIN 5
int distanceReading;
int distanceReadingLeft;
int distanceReadingRight;
float wallDistance;
float wallDistanceLeft;
float wallDistanceRight;
float wallDistanceTolerance = 100;

int counter = 0; // Loop counter variable
float lag = .5712; // Phase lag between segments
int frequency = 1; // Oscillation frequency of segments.
int amplitude = 50; // Amplitude of the serpentine motion of the snake
int rightOffset = -10; // Right turn offset
int leftOffset = 10; // Left turn offset
int offset = 2; // Variable to correct servos that are not exactly centered
int delayTime = 3; // Delay between limb movements
int startPause = 5000;  // Delay time to position robot
int test = -3; // Test varialble takes values from -6 to +5

float Distance() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  return pulseIn(ECHOPIN, HIGH) / 10;
}

void goForward() {
  for (counter = 0; counter < 360; counter += 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));//actually pin3
    tlc_setServo(2, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag)); //actually pin4
    tlc_setServo(3, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag)); //actually pin4
    tlc_setServo(4, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag)); //actually pin5
    tlc_setServo(5, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag)); //actually pin5
    tlc_setServo(6, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag)); //actually pin5
    tlc_setServo(7, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + -1 * lag)); //actually pin5
    tlc_setServo(8, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + -2 * lag)); //actually pin6
    tlc_setServo(9, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag)); //actually pin7
    tlc_setServo(10, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag)); //actually pin8
    tlc_setServo(11, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag)); //actually pin9
    tlc_setServo(12, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag)); //actually pin10
    Tlc.update();
  }
}

void goReverse() {
  for (counter = 360; counter > 0; counter -= 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + offset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
    Tlc.update();
  }
}

void goLeft() {
  for (counter = 0; counter < 10; counter += 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + .1 * counter * leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
  }
  // Continue left turn
  for (counter = 11; counter < 350; counter += 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
  }
  // Ramp down turn offset
  for (counter = 350; counter < 360; counter += 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + .1 * (360 - counter)*leftOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
  }

}

void goRight() {
  // Reverse
  for (counter = 360; counter > 0; counter -= 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
  }
  // Turn right
  // Ramp up turn offset
  for (counter = 0; counter < 10; counter += 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + .1 * counter * rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
  }
  // Continue right turn
  for (counter = 11; counter < 350; counter += 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
  }
  // Ramp down turn offset
  for (counter = 350; counter < 360; counter += 1)  {
    delay(delayTime);
    tlc_setServo(1, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 5 * lag));
    tlc_setServo(2, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 4 * lag));
    tlc_setServo(3, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 3 * lag));
    tlc_setServo(4, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 2 * lag));
    tlc_setServo(5, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 1 * lag));
    tlc_setServo(6, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 + 0 * lag));
    tlc_setServo(7, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 1 * lag));
    tlc_setServo(8, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 2 * lag));
    tlc_setServo(9, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 3 * lag));
    tlc_setServo(10, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 4 * lag));
    tlc_setServo(11, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 5 * lag));
    tlc_setServo(12, 90 + .1 * (360 - counter)*rightOffset + amplitude * cos(frequency * counter * 3.14159 / 180 - 6 * lag));
  }
}

void check() {
  tlc_setServo(13, 120);
  delay(delayTime);
  wallDistanceLeft = Distance();

  tlc_setServo(13, 60);
  delay(delayTime);
  wallDistanceRight = Distance();

  tlc_setServo(13, 90);
  delay(delayTime);
}

void setup() {
  //distance
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Serial.begin(9600);
  tlc_initServos();  // Note: this will drop the PWM freqency down to 50Hz.
  tlc_setServo(1, 90 + offset + amplitude * cos(5 * lag));//actually pin3
  tlc_setServo(2, 90 + offset + amplitude * cos(4 * lag));//actually pin3
  tlc_setServo(3, 90 + offset + amplitude * cos(4 * lag));//actually pin3
  tlc_setServo(4, 90 + offset + amplitude * cos(2 * lag)); //actually pin3
  tlc_setServo(5, 90 + offset + amplitude * cos(1 * lag)); //actually pin3
  tlc_setServo(6, 90 + offset + amplitude * cos(0.5 * lag)); //actually pin4
  tlc_setServo(7, 90 + offset + amplitude * cos(-1 * lag)); //actually pin5
  tlc_setServo(8, 90 + offset + amplitude * cos(-2 * lag)); //actually pin6
  tlc_setServo(9, 90 + offset + amplitude * cos(-3 * lag)); //actually pin7
  tlc_setServo(10, 90 + offset + amplitude * cos(-4 * lag)); //actually pin8
  tlc_setServo(11, 90 + offset + amplitude * cos(-5 * lag)); //actually pin9
  tlc_setServo(12, 90 + offset + amplitude * cos(-6 * lag)); //actually pin10
  Tlc.update();
  Serial.println("setup ready! prepare to go~");
  delay(startPause);  // Pause to position robot
}


void loop() {
  wallDistance = Distance();
  Serial.println(wallDistance);
  if (wallDistance > wallDistanceTolerance) {  // If wallDistance > wallDistanceTolerance, move forward
    Serial.println("going fwd");
    goForward();
  } else {// wallDistance < wallDistanceTolerance
    Serial.println("check where to go");
    check();
    Serial.println("going rev");
    goReverse();
    goReverse();
    if (wallDistanceLeft > wallDistanceRight) {
      Serial.println("going left");
      goLeft();
    } else  {//wallDistanceLeft <= wallDistanceRight
      Serial.println("going right");
      goRight();
    }
  }
}
