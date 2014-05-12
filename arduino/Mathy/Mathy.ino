/*
=== STILL UNDER DEVELOPMENT ===

A Robot developed with my daughter Julia in 2013.
Its body has a numeric keypad and a LCD display.
It asks math questions at random that has to be
answered via the keypad.

The communication between the Robot and us is 
in German, for this is Julia's main language.

 */

// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 40, 41, 32, 33 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 48, 46, 45 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Random number
int ran1, ran2;
boolean done, again;
int pos;
String result;

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};


void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hallo, Julia!");
  lcd.setCursor(0, 1);
  lcd.print("Ich bin Mathy!");
  delay(3000);
  lcd.clear();
  
  Serial.begin(9600);
  
  randomSeed(analogRead(0)+1024*analogRead(1));  
  
  done = true;
  again = false;
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
//  lcd.print(millis()/1000);

  if ( done )
  {
    String resultAux;
    result = resultAux;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wie viel?");

    if ( ! again ) {
       ran1 = int(random(1,9));
       ran2 = int(random(1,9));
    }
    String equation = String(ran1) + "." + String(ran2) + " = ";
    lcd.setCursor(0, 1);
    lcd.print(equation);
    done = false;
    pos = 6;
  }
  
  
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    // fix bug in library, meanwhile...
        char keyAux = key;
        if ( key == '*' ) keyAux = '#';
        if ( key == '#' ) keyAux = '*';
        key = keyAux;
        if ( key != '*' && key != '#' )
        {
           result += key;
           lcd.setCursor(pos++, 1);
           lcd.print(key);
           Serial.println(atoi(result.c_str()));
        }
        if ( key == '#' )
        {
          done = true;
          if ( ran1 * ran2 == atoi(result.c_str()) )
          {
            lcd.setCursor(0, 0);
            lcd.print("Gut gemacht! ");
            again  = false;
            delay(5000);
          }
          else
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Schade!");
            lcd.setCursor(0, 1);
            lcd.print("Versuch nochmal!");
            again = true;
            delay(5000);
          }
        }
        
        
  }


}

