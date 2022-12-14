#ifndef	INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager
{
private:

public:
	InputManager();
	~InputManager();

	bool upIsPressed();
	bool downIsPressed();
	bool leftIsPressed();
	bool rightIsPressed();
	bool spaceIsPressed();
	bool enterIsPressed();
	bool escIsPressed();
	bool pIsPressed();
};

#endif // End of '#ifndef INPUTMANAGER_H'