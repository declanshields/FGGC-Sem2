#include "Debug.h"

void Debug::DebugMsg(const std::string message) 
{
	//creates a buffer to store the message, sets the size of buffer to a string, and stores the message in the buffer
	//this message is then output using OutputDebugString
	CHAR sz[2048] = { 0 };
	int success = sprintf(sz, "Debug Log: %s\n", message.c_str());

	OutputDebugStringA(sz);
}

void Debug::DebugMsg(const Vector3D vec3)
{
	CHAR sz[2048] = { 0 };
	std::string message;
	message = "X: " + std::to_string(vec3.x) + " Y: " + std::to_string(vec3.y) + " Z: " + std::to_string(vec3.z);
	int success = sprintf(sz, "Position: %s\n", message.c_str());

	OutputDebugStringA(sz);
}