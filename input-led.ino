// Enter a number using the serial monitor,
// and blink a led that many times.
// As soon as a number is entered, the led turns on.

const int LED = 8;

int ledState;                   // ledState used to toggle the LED
unsigned long previousMillis;   // will store last time LED was updated
bool enable;                    // turn on (true) and off (false) the millis-timer
unsigned long interval = 500;   // interval between toggles in milliseconds
int count1;                     // keep track of how many times the led has blinked
int maxBlink;                   // number to blink

void setup () {

Serial.begin (9600);
Serial.setTimeout( 50);
pinMode (LED, OUTPUT);
Serial.println ("----------HELLO!  WELCOME----------");
delay (1000);
Serial.println ("THIS IS TEAM SPYDAR PROJECT DISPLAY");
delay (500);
Serial.println ("GROUP 4");
Serial.println ("------------------------------------------------------------");
delay (1000);
Serial.println ("Just a moment, Display interface will be up shortly");
delay (500);
Serial.println ("Type any number and the LED will blink the number of times you typed");
Serial.println ("   ");
}

void loop()
{

  if( Serial.available() > 0)    // something received
  {
    delay( 50);                  // wait to hopefully receive the full line
    int n = Serial.parseInt();
    if( n > 0)                   // was it a valid number
    {
      blinkLed( n);              // Start the blinking of the led.
     Serial.println ("****************************************");
     Serial.print ("LED will blink for ");
     Serial.print (n);
     Serial.print (" times");
     Serial.println ();
    }

    while( Serial.available() > 0)
    {
      Serial.read();              // read it and throw it away
    }
  }

   updateLed();
}


void blinkLed( int n)
{
  // The led is immediately turned on,
  // and after the first interval the led is turned off.
  // That will be the first blink.
  ledState = HIGH;
  digitalWrite(LED, ledState);

  // Start the blinking
  previousMillis = millis();   // update the stored millis time to this moment.
  count1 = 0;                  // start from zero
  maxBlink = n;                // blink up to this number
  enable = true;               // enable the millis-timer in the "update" function.
}


void updateLed()
{
  // A 'currentMillis' variable is not needed, but is often handy
  unsigned long currentMillis = millis();

  if( enable)                  // should we blink ?
  {
    if( currentMillis - previousMillis > interval)  // millis-timer
    {
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
      ledState = ledState == HIGH ? LOW : HIGH;

      // set the LED with the ledState of the variable:
      digitalWrite(LED, ledState);

      // When the led has just turned low, increase the number that is blinked
      if( ledState == LOW)
      {
        count1++;
        if( count1 >= maxBlink)
        {
          enable = false;      // enough with this blinking, stop it.
        }
      }
    }
  }
}