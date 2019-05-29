#pragma once
#include "GameObject.h"

#include <SeetyDog/Events/Event.h>


class PlayerObject : public GameObject
{
public://Constructors/Destructors
	PlayerObject();
	
	PlayerObject(glm::vec2 pos, glm::vec2 paddleSize, Texture2D paddleSprite,
		Texture2D gunSprite, Shader paddleShader, Shader bulletShader);

public://Methods
	void		Move(float velocity, unsigned int winWidth);
	void		OnEvent(SeetyDog::Event& event);
	void		Reset(glm::vec2 position, glm::vec2 velocity);
	void		Init();
	void		Reset();
	void		Update(float dt);
	void		Draw(SpriteRenderer &renderer) override;

public://Members
	//glm::vec2		Position;
	//glm::vec2		Size;
	
private://Members
	void ShootGun();
	void UpdateGunPosition();
private://Members
	glm::vec2		m_PaddleInitSize;
	glm::vec2		m_PaddleInitPosition;
	glm::vec2		m_GunSize;
	float			m_PlayerSpeed;
	float			m_BulletSpeed;
	float			m_GunRotation;
	glm::vec2		m_GunPosition;
	glm::vec2		m_BulletVelocity;
	Texture2D		m_PaddleTex;
	Texture2D		m_GunTex;
	Shader			m_PlayerShader;
	Shader			m_BulletShader;
	unsigned int	VAO;
	glm::mat4		trans;
};