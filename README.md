### Der Werkzeugkasten

#### Task Umgrenzungsworte
- taskBegin() Damit wird ein Task Block eingeleitet
- taskEnd()   Das Ende eines Taskblockes

##### Task Kontroll Worte
- taskSwitch() Gibt die Rechenzeit an die aufrufende Funktion ab. Es wird im nächsten Durchlauf an dieser Stelle weiter gearbeitet.
- taskPause(interval) Diese Task pausiert, bis interval abgelaufen.
- taskWaitFor(Bedingung)  Diese Task pausiert, bis die Bedingung wahr wird.         

##### Schrittketten Kontroll Worte
- taskStepName(Bezeichner)
- taskJumpTo(Bezeichner)
         
 
### Beispiel 
'''

#include <TaskMacro.h>

Task blink()
{
   taskBegin();
   while(1)   // blockiert dank der TaskPause nicht 
   {
      digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
      taskPause(500);   // gibt Rechenzeit ab
   }
   taskEnd();   
}

void setup(){}

void loop
{
  blink();
}

'''         
         

### Einzuhaltende Bedingungen
Eine Task ist eine normale C/C++ Funktion. 
Innerhalb einer Task kann das Switch()-case Konstrukt nicht genutzt werden, da dieses intern von der Task verwendet wird.
Immer nur ein Taskkontrollwort pro Zeile, da die Zeilennummer als Sprungmarke genutzt wird. 
Trage Sorge, dass die Task häufig aufgerufen wird. Loop() ist ein guter Ort dafür.  

### Empfehlungen: 
Verwende den Type "Task", um die Task eindeutig als Task zu kennzeichnen. 
Versehe jede Task mit einer Endlosschleife. So entspricht es, in etwa, dem Bild in anderen Betriebsystemumgebungen.       
         
### Links    
- [Blink Without Delay](https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay])
- [Der Wachmann](https://forum.arduino.cc/index.php?topic=423688.0)
- [Multitasking Macros](https://forum.arduino.cc/index.php?topic=415229.msg2859554)
- [Intervall Macros](https://forum.arduino.cc/index.php?topic=413734.msg2848523)


      
     