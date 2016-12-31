#include <TaskMacro.h>


/**
 * Auf Tastendruck wird 5 mal geblinckt 
*/




const byte taster            = 4;   // Taster zwischen Pin und GND
const byte led               = 13;  // Led zwischen Pin und GND
const unsigned long interval = 500; // ms
const byte zyklen            = 5;   // Anzahl Blinker

bool blinkAnforderung        = false; // Merker für Blink Anforderung

Task blink() 
{
  static byte i = 0;  // Wiederholungszaehler
  taskBegin();
  while(1)
  {
    taskWaitFor(blinkAnforderung);
    for(i=0;i<zyklen;i++)
    {
      digitalWrite(led, HIGH); // leuchte an
      taskPause(interval);
      digitalWrite(led, LOW); // leuchte aus
      taskPause(interval);
    }
    blinkAnforderung = false ; // Anforderung konsumieren
  }
  taskEnd();
}


void setup()
{
  pinMode(led, OUTPUT);
  pinMode(taster,INPUT_PULLUP);
}

void loop()
{
  blinkAnforderung = blinkAnforderung || !digitalRead(taster); // short circuit boolean expression evaluation
  blink();
}
