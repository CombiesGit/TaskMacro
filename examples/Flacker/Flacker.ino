 #include <TaskMacro.h>

const byte LED = 13;


void setup() 
{
  pinMode(LED,OUTPUT); 
  Serial.begin(9600); 
}


Task showRuns() // zeige jede Sekunde die Anzahl Durchläufe an
{
  static unsigned long runs = 0;
  runs++;
  
  taskBegin(); 
  while(1)
  {
    taskPause(1000);
    Serial.print("Runs: ");
    Serial.println(runs);
    runs = 0;
  }
  taskEnd();
}


Task flacker() // flackern
{
  static unsigned long interval = 0;
  
  taskBegin(); 
  while(1)
  {
    digitalWrite(LED,!digitalRead(LED));
    interval =  random(500) % 43 * 9;
    taskPause(interval);
  }
  taskEnd();
}


void loop() 
{
  flacker();
  showRuns();
}