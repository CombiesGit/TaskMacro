#pragma once // include guard

#include <util/atomic.h>

typedef  void Task; //  Task Type


// grundlegene Worte um einen Task Bereich einzugrenzen
#define taskBegin()                                               \
static int Task_mark = 0;                                         \
static unsigned long __attribute__((unused)) Task_timeStamp = 0;  \
switch(Task_mark)                                                 \
{                                                                 \
  case 0:  
  
  
#define taskEnd()               \
  for(;;)                       \
  {                             \
          taskSwitch();         \
  }                             \
}


// Task Kontrol Worte, diese werden Taskwechsel einleiten
#define taskSwitch() do { Task_mark = __LINE__; return ; case __LINE__: ; } while (0)
#define taskPause(Task_interval) Task_timeStamp = millis(); while((millis() - Task_timeStamp) < (Task_interval)) taskSwitch()
#define taskWaitFor(Task_condition) while(!(Task_condition)) taskSwitch();



// Benennen und anspringen von Schrittketten Verzweigungen
#define taskStepName(Task_stepname) Task_step_##Task_stepname  :
#define taskJumpTo(Task_stepname)  goto  Task_step_##Task_stepname 


// Task Prioritaet festlegen
// 0 == hoch(wird bei jedem Durchlauf ausgeführt) bis 65535 (AnzahlAusfuehrungen == Durchlaeufe/pri )
#define taskPriority(pri)                                   \
do                                                          \
{                                                           \
  static uint16_t taskPri;                                  \
  taskPri++;                                                \
  if(taskPri < (pri) ) return;taskPri=0;                    \
} while(0)


// kleine helferlein
#define CriticalSection  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)




// Mutex , Semaphor, Monitor, Lock
 /* TODO
// Mutex Abhandlung
struct Mutex {int8_t flag = 0;};

static inline bool mutexFree(Mutex * mutex)
{
  return (!(mutex)->flag);
}

static inline void mutexClaim(Mutex * mutex)
{
  ++(mutex)->flag;
}


      

#define taskWaitForMutex(mutex)       \
do{                                   \
   taskWaitFor(mutexFree(mutex));     \
   mutexClaim(mutex);                 \
}while(0)

 */           