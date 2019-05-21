#pragma once

#include <GLAD/include/glad/glad.h>
#include <SeetyDog/Events/Event.h>


enum GameState;

class Game
{
public:
	Game() {}
	Game(unsigned int width, unsigned int height);
	~Game();

public://Methods
	void Init();
	void EventInput(SeetyDog::Event& event);
	void ProcesInput(float dt);
	void Update(float dt);
	void Render();

public://Members 
	GameState m_State;
	bool m_Keys[1024];
	unsigned int m_Width, m_Height;

};

enum GameState {
	GAME_ACTIVE, GAME_MENU, GAME_WIN
};