#include <TaskMacro.h>

const unsigned long leuchtDauer = 2000; // Ampeltakt
bool piepflag = false;                  // Merker

Task piepser() // 5 mal piepsen, wenn Flag gesetzt
{
  static int i = 0;  
  taskBegin();
  while(1) // diese Schleife blockiert nicht
  {
    taskWaitFor(piepflag);
    for(i = 0; i < 5; i++) // diese Schleife blockiert nicht
    {
       Serial.println(F("Piep"));
       taskSwitch();
    }
    piepflag = false; // fertig mit piepsen
  }
  taskEnd();
}


Task ampel() // Ampelschaltung
{
  static unsigned long i = 0; // zählt die Ampelaufrufe
  i++;
  taskBegin();
  while(1) // diese Schleife blockiert nicht
  { 
      // rotPhase
      Serial.print(i);
      Serial.println(F(" Rot an - Gelb aus - Gruen aus"));
      taskPause(leuchtDauer);
      
      
      // gelbPhase Type: Mit Rot
      Serial.print(i);
      Serial.println(F(" Rot an - Gelb an - Gruen aus"));
      taskPause(leuchtDauer);
    
      
      // grünPhase
      Serial.print(i);
      Serial.println(F(" Rot aus - Gelb aus - Gruen an"));
      piepflag = true; // 5 mal piepsen
      taskPause(leuchtDauer);
     
      
      // gelbPhase Type: ohne Rot
      Serial.print(i);
      Serial.println(F(" Rot aus - Gelb an - Gruen aus"));
      taskPause(leuchtDauer);
  }
  taskEnd();
}



void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  piepser();
  ampel();  
}