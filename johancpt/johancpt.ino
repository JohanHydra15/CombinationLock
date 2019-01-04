 /*
  Combination Lock Circuit and Code
  Author: Johan Sebastiampillai
  Date: June 20, 2017

  This program monitors two potentiometers. After the Arduino is turned on, you will have 10 seconds to enter a code 
  that you want to use after which a green led will turn on and then off to indicate that the password has been set. 
  Then disrupt you originally set code to lock the box again. When the correct code is entered, the green LED will 
  turn on followed by the servo turning 90 degrees to unlock the door. The door will remain unlocked until the door 
  is closed properly and the correct code is disturbed. While the wrong code is entered, the red LED will remain on. 
  */
 
 #include <Servo.h>          //import the servo motor library
 
 Servo myservo;              //create servo object to control a servo
 int LEDGreen = 4;           //declare and intitialize the variable for the greed LED
 int LEDRed = 2;             //declare and intitialize the variable for the red LED
 int pot1Status;             //declare and intitialize the variable for the state of the first potentiometer (for the code set in the beginning)
 int pot1State;              //declare and intitialize the variable for the state of the first potentiometer
 int pot2Status;             //declare and intitialize the variable for the state of the second potentiometer (for the code set in the beginning)
 int pot2State;              //declare and intitialize the variable for the state of the second potentiometer

void setup() {
  
  myservo.attach(9);                                 //attaches the servo on pin 9 to the servo object
  pinMode(LEDGreen, OUTPUT);                         //make the green LED pin an output
  pinMode(LEDRed, OUTPUT);                           //make the red LED pin an output
  
  delay (10000);                                     //delay for 10 seconds
  pot1Status = analogRead(A0);                       //read the state of the first potentiometer (to initialize password)   
  pot2Status = analogRead(A1);                       //read the state of the second potentiometer (to initialize password) 
  pot1Status = map(pot1Status, 0, 1023, 1, 6);       //map the state of the first potentiometer to make 5 possible positions for password
  pot2Status = map(pot2Status, 0, 1023, 1, 6);       //map the state of the second potentiometer to make 5 possible positions for password
  digitalWrite(LEDGreen, HIGH);                      //turn on green LED
  delay (1000);                                      //delay for 1 second
  digitalWrite(LEDGreen, LOW);                       //turn of green LED
  myservo.write(180);                                //turn the servo motor to 180 degrees to lock box
}

void loop() {

  pot1State = analogRead(A0);                        //read the state of the first potentiometer
  pot2State = analogRead(A1);                        //read the state of the second potentiometer  
  pot1State = map(pot1State, 0, 1023, 1, 6);         //map the state of the first potentiometer for 5 possoble positions
  pot2State = map(pot2State, 0, 1023, 1, 6);         //map the state of the second potentiometer for 5 possoble positions
  
  if (pot1State == pot1Status && pot2State == pot2Status) {    //check if the entered password it the same as the originally set password
   digitalWrite(LEDGreen, HIGH);                               //turn off green LED
   digitalWrite(LEDRed, LOW);                                  //turn off red LED
   myservo.write(100);                                         //turn the servo motor 100 degrees to unlock box
   delay(15);                                                  //delay for 15 milliseconds
   
  } else {                                                     //if the code entered does not equal the originally set password
    myservo.write(180);                                        //turn the servo motor back to 180 degrees to lock the box
    digitalWrite(LEDGreen, LOW);                               //turn off green LED
    digitalWrite(LEDRed, HIGH);                                //turn off red LED
  } 

}
