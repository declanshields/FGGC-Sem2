#pragma once

#include <string>
#include "Vector3D.h"
#include <Windows.h>

class Debug
{
public:
	//void function that takes in a message and then outputs it as a debug message
	static void DebugMsg(const std::string message);
	static void DebugMsg(const Vector3D vec3);
};