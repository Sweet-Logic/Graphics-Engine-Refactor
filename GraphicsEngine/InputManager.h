#pragma once
#include <d3d11_1.h>

class InputManager
{
private:
	InputManager() {};

public:
	InputManager & operator=(InputManager&); // Disallowed
	InputManager(const InputManager&); // Disallowed
	~InputManager();

	InputManager* GetInstance() { return (_instance)? _instance : _instance = new InputManager(); }

	bool CheckIfKeyPressed(char key)
	{
		return GetAsyncKeyState(toupper(key));
	}

private:
	static InputManager* _instance;

};

