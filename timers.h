#pragma once

void Timer0Init();
void Timer1Init();
void Timer2Init();
inline void TimersInit();

inline void TimersInit()
{
	Timer0Init();
	Timer1Init();
	Timer2Init();
}
