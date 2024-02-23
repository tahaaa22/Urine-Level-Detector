// include the library code: 
#include <LiquidCrystal.h>
//initialise the library with the numbers of the interface pins 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
 
int buzzer = 8;
const int trigPin = 7;
const int echoPin = 6;
  
void setup() { 
 Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2); 
  lcd.setCursor(0,0);
  // Print a message to the LCD. 
  lcd.print("WATER LEVEL: "); 
} 
  
void loop() { 
  // set the cursor to column 0, line 1 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond pulse to trigger the ultrasound measurement
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the duration of the pulse from the echoPin
  int duration = pulseIn(echoPin, HIGH);
  
    lcd.setCursor(0,1);
    // Serial.print("water level: ");
     //Serial.println(duration);



    if (duration >= 790)
  { lcd.println("empty");
  digitalWrite(buzzer, LOW); 
  Serial.println(0);
  } 
  else if (duration >590  && duration < 790)
  { lcd.println("0-25% full");
  digitalWrite(buzzer, LOW);
  Serial.println(12);
   }
  else if (duration >= 530 && duration <= 590)
  { lcd.println("25% full");
  digitalWrite(buzzer, LOW);
  Serial.println(25);
   }
    else if (duration >340  && duration < 530)
  { lcd.println("25-50% full");
  digitalWrite(buzzer, LOW);
  Serial.println(32);
   }
   else if (duration >= 320 && duration <= 340)
   { lcd.println("50% full"); 
   digitalWrite(buzzer, LOW);
   Serial.println(50);
   }
    else if (duration >140  && duration < 320)
  { lcd.println("50-75% full");
  digitalWrite(buzzer, LOW);
  Serial.println(62);
   }
    else if (duration >= 115 && duration <= 140){ 
     lcd.println("75% full"); 
     digitalWrite(buzzer, LOW);
     Serial.println(75);
   }
   else if(duration < 115)
   {
    
    lcd.println("danger:change bag!!"); 
     digitalWrite(buzzer, HIGH);
     Serial.println(90);
   }
  
   delay(1000); 
}