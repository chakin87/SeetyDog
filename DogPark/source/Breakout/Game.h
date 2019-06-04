#pragma once

#include <vector>
#include <tuple>

#include <GLAD/include/glad/glad.h>
#include <SeetyDog/Events/Event.h>

#include "BallObject.h"
#include "GameLevel.h"
#include "PowerUp.h"
#include "PlayerObject.h"
#include "ProjectileObject.h"

enum GameState;
enum Direction;


const glm::vec2 GUN_SIZE(18.0f, 53.0f);


// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100, 20);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(500.0f);
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;

// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>



	GLboolean IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type);

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
	void DoCollisions();
	// Reset
	void ResetLevel();
	void ResetPlayer();
	// Powerups
	void SpawnPowerUps(GameObject &block);
	void UpdatePowerUps(GLfloat dt);

public://Members 
	GameState m_State;
	bool m_Keys[1024];
	unsigned int m_Width, m_Height;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
	GLuint                 Lives;
	std::vector<PowerUp>   PowerUps;
	GLfloat ShakeTime;
};


// Represents the current state of the game
enum GameState {
	GAME_ACTIVE, GAME_MENU, GAME_WIN
};
// Represents the four possible (collision) directions
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};