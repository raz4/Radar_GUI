#include "Arduino.h"
#include <Servo.h>

Servo myServo;

class Ultrasonic
{
	public:
		Ultrasonic(int pin);
    void DistanceMeasure(void);
		long microsecondsToCentimeters(void);
		long microsecondsToInches(void);
	private:
		int _pin;//pin number of Arduino that is connected with SIG pin of Ultrasonic Ranger.
        long duration;// the Pulse time received;
};

Ultrasonic::Ultrasonic(int pin)
{
	_pin = pin;
}

/*Begin the detection and get the pulse back signal*/
void Ultrasonic::DistanceMeasure(void)
{
  pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);
	duration = pulseIn(_pin,HIGH);
}

/*The measured distance from the range 0 to 400 Centimeters*/
long Ultrasonic::microsecondsToCentimeters(void)
{
	return duration/29/2;	
}

/*The measured distance from the range 0 to 157 Inches*/
long Ultrasonic::microsecondsToInches(void)
{
	return duration/74/2;	
}

Ultrasonic ultrasonic(7);

//import processing.serial.*;

//PrintWriter output;

void setup()
{
	Serial.begin(9600);
    
    //output = createWriter ( " data.txt " );
    
    myServo.attach(9);
 
}

int i = 15;
         
void loop()
{
	//long RangeInInches;
	long RangeInCentimeters;
    
    //RangeInInches = ultrasonic.microsecondsToInches(); //convert the time to inches;
    RangeInCentimeters = ultrasonic.microsecondsToCentimeters();//convert the time to centimeters
    
    for (i = 15; i < 165 ; i++){
        myServo.write(i);
        ultrasonic.DistanceMeasure();// get the current signal time;
        RangeInCentimeters = ultrasonic.microsecondsToCentimeters();
        Serial.println(i);
        Serial.println(RangeInCentimeters);//0~400cm
        delay(30);
    }
    
    for (i = 165; i > 15; i++){
        myServo.write(i);
        ultrasonic.DistanceMeasure();// get the current signal time;
        RangeInCentimeters = ultrasonic.microsecondsToCentimeters();
        //Serial.print("distance: ");
        Serial.println(i);
        Serial.println(RangeInCentimeters);//0~400cm
        delay(30);
    }
    
    i = 15;
    //delay(100);
}
