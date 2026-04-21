#include "ctimer.h"

CUtlLinkedList<CTimerBase*> g_timers;

void RemoveTimers()
{
	g_timers.PurgeAndDeleteElements();
}