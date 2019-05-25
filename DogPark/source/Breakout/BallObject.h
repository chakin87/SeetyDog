#pragma once
#include <GLAD/include/glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>

#include "GameObject.h"
#include "Texture2D.h"
#include "SpriteRenderer.h"



class BallObject : public GameObject
{
public:
	// Ball state	
	GLfloat   Radius;
	GLboolean Stuck;
	GLboolean Sticky, PassThrough;
	// Constructor(s)
	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite, Shader shader);
	// Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	// Resets the ball to original state with given position and velocity
	void      Reset(glm::vec2 position, glm::vec2 velocity);
	void	  Init();
	void	  Update(float dt);
	void	  Draw(SpriteRenderer &renderer) override;
private:
	Shader shader;
	Texture2D texture;
	unsigned int VAO;
	glm::mat4 trans; 
};

