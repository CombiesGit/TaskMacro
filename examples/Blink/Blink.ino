#include <TaskMacro.h>

const byte LED = 13;


void setup() 
{
  pinMode(LED,OUTPUT);  
}

void loop() 
{
  taskBegin();
  while(1)
  {
    digitalWrite(LED,!digitalRead(LED));
    taskPause(500);
  }
  taskEnd();
}