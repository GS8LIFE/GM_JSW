#pragma once
#include <ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{
public:
	int2 nowHead = {0,0};
	Part* Front = nullptr;
	Part* Back = nullptr;

protected:
};