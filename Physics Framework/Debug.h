#pragma once

#include <string>
#include <Windows.h>

class Debug
{
public:
	//constructor
	Debug();

	//void function that takes in a message and then outputs it as a debug message
	void DebugMsg(const std::string message);
};