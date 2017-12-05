#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();
// --------------------------------------------------------------------------- Motors
#define ML0 13
#define ML1 12

#define MR0 8
#define MR1 7

#define MLS 11
#define MRS 6


// --------------------------------------------------------------------------- Setup
void setup() {

nunchuk.init();	

// Setup motors
pinMode(ML0, OUTPUT);
pinMode(ML1, OUTPUT);

pinMode(MR0, OUTPUT);
pinMode(MR1, OUTPUT);

}

// --------------------------------------------------------------------------- Loop
void loop() {
	nunchuk.update();

int xValue = constrain(nunchuk.analogX, 27, 232);
int xVal = 133 - xValue;

int yValue = constrain(nunchuk.analogY, 33, 229);
int yVal = 132 - yValue;

int spd1 = map(abs(yVal), 0, 99, 0, 254);
int spd2 = map((abs(yVal) + (xVal/2)), 0, 114, 0, 254);
int fullTurnSpd = map(abs(xVal), 0, 108, 0, 254);

int zVal = nunchuk.zButton;
int cVal = nunchuk.cButton;

if(nunchuk.zButton == 1){
	motor_stop();
} else {
	if(yVal < -20){
		drive_forward(spd1, spd2);
	} else if (yVal > 20) {
		drive_backward(spd1, spd2);
	} else if (xVal > 20) {
		turn_left(fullTurnSpd);
	} else if (xVal < -20) {
		turn_right(fullTurnSpd);
	} else {
		motor_stop();
	}
}

}

// --------------------------------------------------------------------------- Drive

void motor_stop(){
analogWrite(MLS, 0);
analogWrite(MRS, 0);

digitalWrite(ML0, LOW);
digitalWrite(ML1, LOW);

digitalWrite(MR0, LOW);
digitalWrite(MR1, LOW);
delay(25);
}

void drive_forward(int leftVal, int rightVal){
digitalWrite(ML0, HIGH);
digitalWrite(ML1, LOW);
analogWrite(MLS, leftVal);

digitalWrite(MR0, HIGH);
digitalWrite(MR1, LOW);
analogWrite(MRS, rightVal);
}

void drive_backward(int leftVal, int rightVal){
digitalWrite(ML0, LOW);
digitalWrite(ML1, HIGH);
analogWrite(MLS, leftVal);

digitalWrite(MR0, LOW);
digitalWrite(MR1, HIGH);
analogWrite(MRS, rightVal);
}
//use for hard left only
void turn_left(int speed){
digitalWrite(ML0, LOW);
digitalWrite(ML1, HIGH);
analogWrite(MLS, speed);

digitalWrite(MR0, HIGH);
digitalWrite(MR1, LOW);
analogWrite(MRS, speed);
}
//use for hard right only
void turn_right(int speed){
digitalWrite(ML0, HIGH);
digitalWrite(ML1, LOW);
analogWrite(MLS, speed);

digitalWrite(MR0, LOW);
digitalWrite(MR1, HIGH);
analogWrite(MRS, speed);
}
