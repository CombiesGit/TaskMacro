#pragma once // include guard

#include <util/atomic.h>

typedef  void Task; //  Task Type


// grundlegene Worte um einen Task Bereich ein zu grenzen
#define taskBegin() static int mark = 0; static unsigned long __attribute__((unused)) timeStamp = 0; switch(mark){ case 0:  
#define taskEnd() }


// Task Kontrol Worte, diese werden Taskwechsel einleiten
#define taskSwitch() do { mark = __LINE__; return ; case __LINE__: ; } while (0)
#define taskPause(interval) timeStamp = millis(); while((millis() - timeStamp) < (interval)) taskSwitch()
#define taskWaitFor(condition) while(!(condition)) taskSwitch();


// Benennen und anspringen von Schrittketten Verzweigungen
#define taskStepName(STEPNAME) TASKSTEP_##STEPNAME  :
#define taskJumpTo(STEPNAME)  goto  TASKSTEP_##STEPNAME 


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

// Mutex Abhandlung
struct Mutex {int8_t flag= 0;};

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

            