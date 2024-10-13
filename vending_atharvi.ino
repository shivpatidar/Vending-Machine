//Controlling coin acceptor with Arduino
// include the library code:
#include  <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to


#include <Stepper.h>
// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper Stepper1 = Stepper(stepsPerRevolution, SDA, 7, 10, 9);
Stepper Stepper2 = Stepper(stepsPerRevolution, SCL, 7, 10, 9);


// variable use to measuer the intervals inbetween impulses
int  i;
// Number of impulses detected
int impulsCount=0;
// Sum of all the  coins inseted
float total_amount=0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 =6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo servo1, servo2, servo3, servo4;   // DS04-NFC motors
#define button1 13
#define button2 8
int buttonPressed;
int money;
void setup() {
  // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.print("Vending Machine");
    
    servo1.attach(9);
    servo2.attach(10);
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
  
  pinMode(2,INPUT_PULLUP);
  Serial.begin(9600);
  
 // Interrupt connected  to PIN D0 executing IncomingImpuls function when signal goes from HIGH to LOW
  attachInterrupt(0,incomingImpuls, FALLING);
  
//  lcd.setBrightness(0x0f);
  

}

void incomingImpuls()
{
  
  impulsCount=impulsCount+1;
  i=0;
  
}

void loop() {
  
      
    if (digitalRead(button1) == LOW) {
      buttonPressed = 1;money=20;
      while (true) {
        i=i+1;
        Serial.print("money=");
        Serial.print(money);
        Serial.print("i=");
        Serial.print(i);
        Serial.print(" Impulses:");
        Serial.print(impulsCount);
        Serial.print(" Total:");
        Serial.println(total_amount);
        
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("Total Cost: 20");
        lcd.setCursor(0,1);
        lcd.print("Amount Paid: ");
        lcd.print(total_amount);
       
        if (i>=30  and impulsCount==1){
          total_amount=total_amount+10;
          impulsCount=0;
          
        }
   
        if (i>=30 and impulsCount==5){
          total_amount=total_amount+5;
          impulsCount=0;
      
        }

        if(total_amount==20){ 
            Stepper1.setSpeed(10);
            Stepper1.step(stepsPerRevolution);
            delay(500);
            Serial.println("Rs 20 Item dropped");
            total_amount=0;
            lcd.clear();
            lcd.print("Rs 20 Item Drop");
            delay(1000);
            lcd.clear();
            lcd.print("Vending Machine");
            break;
          }
  
}
    }
    if (digitalRead(button2) == LOW) {
      buttonPressed = 2;money=35;
      while (true) {
        i=i+1;
        Serial.print("money=");
        Serial.print(money);
        Serial.print("i=");
        Serial.print(i);
        Serial.print(" Impulses:");
        Serial.print(impulsCount);
        Serial.print(" Total:");
        Serial.println(total_amount);

        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("Total Cost: 35");
        lcd.setCursor(0,1);
        lcd.print("Amount Paid: ");
        lcd.print(total_amount);
 
        if (i>=30  and impulsCount==1){
          total_amount=total_amount+10;
          impulsCount=0;
          
        }
         
         if (i>=30 and impulsCount==5){
          total_amount=total_amount+5;
          impulsCount=0;
      
        }

 //if(total_amount<10) lcd.print(showNumberDecEx(total_amount*10, 0b10000000,  true, 2, 2)); 
  //else
        if(total_amount==35){
            Stepper2.setSpeed(10);
            Stepper2.step(stepsPerRevolution);
            delay(500);
            Serial.println("Rs 35 Item dropped");
            lcd.clear();
            lcd.print("Rs 35 Item Drop");
            delay(1000);
            lcd.clear();
            lcd.print("vending Machine");
            total_amount=0;
            break;
          }
  
        }
      } 
//  } 
}
