// sterowanie dioda przez serial

//ustawianie wszystkich stalych i zmiennych
//set all variables

// Define these at the top of your sketch.

#include <stdio.h>
#define TYPE        "3xON/OFF"  //rodzaj urzadzenia
#define SW          "1.0"       //wersja programu
#define HW          "Nano3"     //wersja sprzetowa
#define ADDRESS     "11"        //adres sieciowy urzadzenia

#define LEDBLINK_PIN    13    // I/O pin connected to the LED.
#define LEDBLINK_MS     1000  // Blink rate (in milliseconds).

//ustawienia sieciowe
const int net_adr = 11;       //zakres 10-99 !

//tworzymy tablicę pinów, pod które podłączone mamy diody LED
int leds[] = {2, 3, 4};
//określamy wielkość tablicy jako stałą
#define SIZE 3
int i;

//int hb_led = 13;
int wyjscie2 = 2;
int wyjscie3 = 3;
int wyjscie4 = 4;

void setup(){
  Serial.begin(9600);
  Serial.println("TYP: "+ String(TYPE) + " Adres: " + String(ADDRESS));
  Serial.println("HW: "+ String(HW) + " SW: "+ String(SW));
  
  // For ledBlink(), set LEDBLINK_PIN to output.
    pinMode(LEDBLINK_PIN, OUTPUT);
  
  //Set all the pins we need to output pins
  //Ustawiamy wszystkie piny jakie potrzebujemy na OUT
    //pinMode(hb_led, OUTPUT);
    pinMode(wyjscie2,OUTPUT);
    pinMode(wyjscie3,OUTPUT);
    pinMode(wyjscie4,OUTPUT);
}

void loop (){
  
   // Blink the LED to let the user know we are still alive.
  ledBlink();
  
  if (Serial.available()) {

    //read serial as a character
    char ser = Serial.read();

    //NOTE because the serial is read as "char" and not "int", the read value must be compared to character numbers
    //hence the quotes around the numbers in the case statement
    switch (ser) {
        case 'a':
        //pinON(13);
        Serial.println("pin13:ON");
        break;
        //case 'b':
        pinOFF(13);
        Serial.println("pin13:OFF");
        break;
        case '2':
        pinON(wyjscie2);
        Serial.println("wyjscie2:ON");
        break;
        case '3':
        pinON(wyjscie3);
        Serial.println("wyjscie3:ON");
        break;
        case '4':
        pinON(wyjscie4);
        Serial.println("wyjscie4:ON");
        break;
        case '0':
        pinOFF(wyjscie2);
        pinOFF(wyjscie3);
        pinOFF(wyjscie4);
        Serial.println("wyjscia:OFF");
        break;
        case '1':
        pinON(wyjscie2);
        pinON(wyjscie3);
        pinON(wyjscie4);
        Serial.println("wyjscia:ON");
        break;
        //case 'p':
        //--biegnący punkt świetlny
        //for (i = 0; i < SIZE; i++) {
        //digitalWrite(leds[i], HIGH);
        //delay(300);
        //digitalWrite(leds[i], LOW);
        //}
        //break;
        //case 'b':
        //--Bar graph
        //for (i = 0; i < SIZE; i++) {
        //digitalWrite(leds[i], HIGH);
        //delay(300);
        //}
        //for (i = 0; i < SIZE; i++) {
        //digitalWrite(leds[i], LOW);
        //delay(300);
        //}
        //break;
    }
  }
}

void pinON(int pin){
  digitalWrite(pin, HIGH);
}

void pinOFF(int pin){
  digitalWrite(pin, LOW);
}

void ledBlink()
{
  static unsigned int  ledStatus = LOW;  // Last set LED mode.
  static unsigned long ledBlinkTime = 0; // LED blink time.

  // LED blinking heartbeat. Yes, we are alive.
  // For explanation, see:
  // http://playground.arduino.cc/Code/TimingRollover
  if ( (long)(millis()-ledBlinkTime) >= 0 )
  {
    // Toggle LED.
    ledStatus = (ledStatus==HIGH ? LOW : HIGH);

    // Set LED pin status.
    digitalWrite(LEDBLINK_PIN, ledStatus);

    // Reset "next time to toggle" time.
    ledBlinkTime = millis()+LEDBLINK_MS;
  }
} // End of ledBlink()
