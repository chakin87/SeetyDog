#pragma once
#include "GameObject.h"
#include "ProjectileObject.h"
#include <vector>
#include <SeetyDog/Events/Event.h>

struct BulletObject;

class PlayerObject : public GameObject
{
public://Constructors/Destructors
	PlayerObject();

	PlayerObject(glm::vec2 pos, glm::vec2 paddleSize, Texture2D paddleSprite, ProjectileGenerator* projGen,
		Texture2D gunSprite, Texture2D bulletSprite, Shader paddleShader, Shader bulletShader);

public://Methods
	void		Move(float velocity, unsigned int winWidth);
	void		OnEvent(SeetyDog::Event& event);
	void		Reset(glm::vec2 position, glm::vec2 velocity);
	void		Init();
	void		Reset();
	void		Update(float dt);
	void		Draw(SpriteRenderer &renderer) override;

public://Members 
	ProjectileGenerator*		m_Bullets;
private://Methods
	void						UpdateGunPosition();
private://Members
	unsigned int				VAO;
	//Paddle Related Members
	glm::vec2					m_PaddleInitSize;
	glm::vec2					m_PaddleInitPosition;
	float						m_PlayerSpeed;
	Texture2D					m_PaddleTex;
	Shader						m_PlayerShader;
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