## TaskMacro
Eine Arduino Lib, um Kooperatives Multitasking übersichtlich zu gestalten. 
Diese Library verbirgt große Teile der Komplexität vor dem Programmierer.

### Abgrenzung von anderen Systemen
Natürlich gibt es viele weitere Multitaskingsysteme für Arduino. 
Einige implementieren sogar preemptives Multitasking.  z.B. verschiedene [FreeRTOS](http://www.freertos.org/) Implementierungen.
Das bedingt leider einen recht großen RAM Verbrauch, da zu einem TaskKontrollBlock, für jede Task, auch noch jeweils ein eigener Stack Bereich dazu kommt.
Somit ist das RAM eines UNOs mit ca 5 Tasks vollständig geflutet. Mehr geht kaum. 
Auch sind nicht alle Funktionen der Arduino Laufzeitumgebung reentrant/Wiedereintrittsfähig.  
Eine Echtzeitfähigkeit ist nur mit einem preemptiven Multitasking System durchsetzbar.

Des weiteren gibt es natürlich viele alternative Systeme/Libs, welche kooperatives Multitasking abbilden. 
Auch diese verwenden meist TaskKontrollblocks um Features, wie Task.start() Task.stop() Task.suspend() Task.resume() zu erlauben.



### Ziele
- Schaffen eines "Drop in" Ersatzes, für die delay() Funktion
- Lang laufende Schleifen aufbrechen 
- Möglichst wenig RAM Verbrauch (2 Byte für interne Markierungen, + 4 Byte wenn eine Zeitsteuerung verwendet wird)
- Übersichtliches Programm
- Grundlage für Schrittketten, einfache endliche Automaten



### Der Werkzeugkasten

#### Task Umgrenzungsworte
- **taskBegin()** Damit wird ein Task Block eingeleitet
- **taskEnd()** Das Ende eines Taskblockes

##### Task Kontroll Worte
- **taskSwitch()** Gibt die Rechenzeit an die aufrufende Funktion ab. Es wird im nächsten Durchlauf an dieser Stelle weiter gearbeitet.
- **taskPause(unsigned long interval)** Gibt Rechenzeit ab, bis interval abgelaufen.
- **taskWaitFor(bool Bedingung)**  Gibt Rechenzeit ab, bis die Bedingung wahr wird.         

##### Schrittketten Kontroll Worte
- **taskStepName(Bezeichner)** Setzt eine benannte Sprungmarke
- **taskJumpTo(Bezeichner)** Springt zu der gesetzten Sprungmarke
         
 
### Beispiel 

```
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

void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop
{
  blink();
}
```         
         

### Einzuhaltende Bedingungen
Eine Task ist eine normale C/C++ Funktion.
 
Innerhalb einer Task kann das Switch()-case Konstrukt nicht genutzt werden, da dieses intern von der Task verwendet wird.

Immer nur ein Taskkontrollwort pro Zeile setzen, da die Zeilennummer als Sprungmarke genutzt wird. 

Trage Sorge, dass die Task häufig aufgerufen wird. Loop() ist ein guter Ort dafür. 

Man sollte bedenken, dass lokale Variablen immer nur einen Durchlauf überleben. Darum wird man in solchen Tasks also eher statische, oder globale, Variablen verwenden. 

Dinge, welche bei jedem Aufruf erledigt werden wollen, haben sich vor  taskBegin(); einzufinden.



### Empfehlungen 
Verwende den Type "Task", um die Task eindeutig als solche zu kennzeichnen. 

Versehe jede Task mit einer Endlosschleife. So entspricht es, in etwa, dem Bild in anderen Betriebsystemumgebungen.  

     
         
### Links    
- [Blink Without Delay](https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay])
- [Der Wachmann](https://forum.arduino.cc/index.php?topic=423688.0)
- [Multitasking Macros](https://forum.arduino.cc/index.php?topic=415229.msg2859554)
- [Intervall Macros](https://forum.arduino.cc/index.php?topic=413734.msg2848523)


### Danke
An dieser Stelle möchte ich mich insbesondere bei  "Donald E. Knuth" bedanken.
Seine unkonventionelle Sicht auf die Dinge, ist eine steter Quell für Inspirationen.      
     