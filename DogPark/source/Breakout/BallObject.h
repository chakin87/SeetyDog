#pragma once
#include <GLAD/include/glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>

#include "ProjectileObject.h"
#include <vector>
#include <SeetyDog/Events/Event.h>

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
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite, ProjectileGenerator* projGen,
		Texture2D gunSprite, Texture2D bulletSprite, Shader paddleShader, Shader bulletShader);

	// Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	// Resets the ball to original state with given position and velocity



public://Methods

	void		OnEvent(SeetyDog::Event& event);



	void      Reset(glm::vec2 position, glm::vec2 velocity);
	void	  Init();
	void	  Update(float dt);
	void	  Draw(SpriteRenderer &renderer) override;

public://Members
	ProjectileGenerator*		m_Bullets;

private://Methods
	void						UpdateGunPosition();
private:
	Shader shader;
	Texture2D texture;
	unsigned int VAO;
	glm::mat4 trans; 


	//Gun Related Members
	glm::vec2					m_GunSize;
	float						m_GunRotation;
	glm::vec2					m_GunPosition;
	Texture2D					m_GunTex;
	//Bullet Related Members
	Texture2D					m_BulletTex;
	glm::vec2					m_BulletSize;
	const short					m_MAX_BULLETS = 30;
	Shader						m_BulletShader;
	glm::vec2					m_BulletVelocity;


};

