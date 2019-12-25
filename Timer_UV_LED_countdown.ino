// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int potPin1 = A1;
const int PushButton1 = A2;
const int PushButton2 = A3;
const int ledPin = 13;  

int sensorMin = 1000;  // minimum potentiometre value
int sensorMax = 0;     // maximum potentiometre value
int sensorValue = 0;     // the initial potentiometre value
int value = 0;
int var = 0;

int PB1State = HIGH; //this variable tracks the state of the push button 1
int PB2State = HIGH; //this variable tracks the state of the push button 2

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();

  // assign Inputs and Outputs
  pinMode(potPin1, INPUT);        
  pinMode(PushButton1, INPUT);
  pinMode(PushButton2, INPUT);
  pinMode(13, OUTPUT);

  //Initiate Serial communication.
  Serial.begin(9600);
  Serial.print("Debugging mode");
}

void loop()
{
 
  // read the potentiometre and push button values:
  sensorValue = analogRead(potPin1);
  PB1State = analogRead(PushButton1);
  PB2State = analogRead(PushButton2);  
   
  // apply the calibration to the potentiotometre reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 120);

  // in case the potentiotometre value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 120);

  lcd.setCursor(0, 0); // Sets the cursor to col 0 and row 0
  lcd.print("Time [s] "); // Prints Sensor Val: to LCD

  // "if loop" to ensure correct reading on LCD (i.e. no left over digits)
  if(sensorValue < 10)
   { lcd.setCursor(0, 1); // Sets the cursor to col 1 and row 0
     lcd.print(sensorValue); // Prints value on Potpin1 to LCD lcd.setCursor(1,1);
     lcd.setCursor(1, 1); 
     lcd.print(" "); //removes extra character at position (1,1)
   }
   else if(sensorValue < 100)
   { lcd.setCursor(0, 1); // Sets the cursor to col 1 and row 0
     lcd.print(sensorValue); // Prints value on Potpin1 to LCD lcd.setCursor(0,1);
     lcd.setCursor(2, 1); 
     lcd.print(" "); //removes extra character at position (2,1)
   }
   else
   {lcd.setCursor(0, 1); // Sets the cursor to col 1 and row 0
   lcd.print(sensorValue); // Prints value on Potpin1 to LCD lcd.setCursor(0,1);
   }
 
   //need to press the 2 push buttons to start the loop.
   if (PB1State == LOW and PB2State == LOW) {
     delay(500);            // waits for a second
     var = 1;               // assign "1" to increment variable "var" 
     value = sensorValue;      // assign "sensor value" to variable "value"

     // count down loop 
     while (var < value+1){
        lcd.setCursor(0, 0); // Sets the cursor to col 1 and row 0
        lcd.print("Exposing:       "); // Prints Sensor Val: to LCD
        lcd.setCursor(0, 1); // Sets the cursor to col 1 and row 0
        digitalWrite(ledPin, HIGH); // sets the digital pin 13 on
        delay(1000);            // waits for a second

         // "if loop" to ensure correct reading on LCD (i.e. no left over digits)
        if(value-var < 10)
         { lcd.setCursor(0, 1); // Sets the cursor to col 1 and row 0
           lcd.print(value-var); // Prints value on Potpin1 to LCD lcd.setCursor(1,1);
           lcd.setCursor(1, 1); 
           lcd.print(" "); //removes extra character at position (1,1)
         }
         else if(value-var < 100)
         { lcd.setCursor(0, 1); // Sets the cursor to col 1 and row 0
           lcd.print(value-var); // Prints value on Potpin1 to LCD lcd.setCursor(1,1);
           lcd.setCursor(2, 1); 
           lcd.print(" "); //removes extra character at position (2,1)
         }
        else
         {lcd.setCursor(0, 1); // Sets the cursor to col 1 and row 0
         lcd.print(value-var); // Prints value on Potpin1 to LCD lcd.setCursor(1,1);
          }
        var++;
        }
      digitalWrite(ledPin, LOW);  // sets the digital pin 13 off
      lcd.clear();
      delay(1000);  // delay 1 sec
   }
}
