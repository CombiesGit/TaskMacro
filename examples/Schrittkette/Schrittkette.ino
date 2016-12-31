#include <TaskMacro.h>


const byte    tasterPin = 11;
const byte    ledPin    = 13;
unsigned long loops     =  0;

#undef taskPriority(pri)
#define  taskPriority(pri)



class OneShot // Signal Merker
{
  private:
  bool signal = false;

  protected:
  void set(const bool value = true)
  {
    signal = value;
  }
  
  public:
  bool get() // signal wird konsumiert
  {
    bool temp = signal;
    signal = false;
    return temp;
  }
};


class Taster : public OneShot
{
  public:
  Task run(const byte pin, const bool invers = false)
  {
    static int i = 0 ; // Schleifenzähler 
    bool taster = digitalRead(pin) ^ invers;
    taskPriority(500); // wird nur beim jedem 500sten Durchlauf ausgefuehrt 
    
    taskBeginTimer(millis);
    while(1)
    {
        taskStepName(WarteAufTaster);
        taskWaitFor(taster);
        for(i=0;i<20;i++)
        {
          taskPause(5);
          if(!taster) taskJumpTo(WarteAufTaster);
        }
        set();  // setze den OneShot Merker
    
        
        taskStepName(WarteAufLosLassen);
        taskWaitFor(!taster);
        for(i=0;i<20;i++)
        {
          taskPause(5);
          if(taster) taskJumpTo(WarteAufLosLassen);
        }
        taskJumpTo(WarteAufTaster);
    }
    taskEnd();
  }
}; 



Task schrittKette(const byte pin, OneShot * taster)
{
  taskPriority(100); // wird nur beim jedem 100sten Durchlauf ausgefuehrt 
  taskBeginTimer(millis);
  while(1)
  {
      taskStepName(schnellesBlinken);
      while(1)
      {
          digitalWrite(pin,!digitalRead(pin));
          taskPause(100);
          if(taster->get()) taskJumpTo(langsamesBlinken);
      }
  
      taskStepName(langsamesBlinken);
      while(1)
      {
         digitalWrite(pin,!digitalRead(pin));
         taskPause(500);
         if(taster->get()) taskJumpTo(schnellesBlinken);
      }
  }    
  taskEnd();
}


Task showLoops()
{
  taskPriority(10000);
  taskBeginTimer(millis);
  for(;;)
  {
    taskPause(1000);
    Serial.print("Loops pro Sekunde: ");
    Serial.println(loops);
    loops = 0;
  }
  taskEnd();
}



void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(tasterPin,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  static Taster taster;
  
  loops++;
  taster.run(tasterPin,true);
  schrittKette(ledPin,&taster);
  showLoops();
}