#include "PlayerObject.h"

#include <SeetyDog/Input.h>
#include <SeetyDog/Logger.h>
#include <SeetyDog/KeyCodes.h>
#include <SeetyDog/MouseButtonCodes.h>

#include "ResourceManager.h"

#include <algorithm>


PlayerObject::PlayerObject()
{
}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 paddleSize, Texture2D paddleSprite, ProjectileGenerator* projGen,
	Texture2D gunSprite, Texture2D bulletSprite, Shader paddleShader, Shader bulletShader)
	: m_PaddleTex(paddleSprite), m_GunTex(gunSprite), m_BulletTex(bulletSprite),
	m_PlayerShader(paddleShader), m_BulletShader(bulletShader), m_PaddleInitSize(paddleSize), m_PaddleInitPosition(pos)//,
	//m_BulletVelocity(-100.0f)
{
	Position = pos;
	m_Bullets = projGen;
	Size = paddleSize;
	this->Init();
}

void PlayerObject::Move(float velocity, unsigned int winWidth)
{
	Position.x += velocity;
	this->UpdateGunPosition();


}

void PlayerObject::OnEvent(SeetyDog::Event& event)
{
	if (SeetyDog::Input::IsMouseButtonPressed(SD_MOUSE_BUTTON_LEFT)) {
		this->m_Bullets->ShootProjectile(glm::vec2(m_GunPosition.x + (m_GunSize.x * .5F), m_GunPosition.y - m_GunSize.y * 0.2f));
	
	}
	this->UpdateGunPosition();
}

void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
}

void PlayerObject::Init()
{
	Size = m_PaddleInitSize;
	Position = m_PaddleInitPosition;
	m_BulletVelocity = glm::vec2(0.0f, -450.0f);
	m_BulletSize = glm::vec2(7, 18);//m_GunSize * 5.f;
	this->m_Bullets->Init(m_BulletVelocity, m_BulletSize);
	this->UpdateGunPosition();
}

void PlayerObject::Reset()
{
	this->Init();
}

void PlayerObject::Update(float dt)
{
	this-> m_Bullets->Update(dt);
}

void PlayerObject::Draw(SpriteRenderer & renderer)
{
	renderer.DrawSprite(this->m_PaddleTex, this->Position, this->Size, this->Rotation, this->Color);
	renderer.DrawSprite(this->m_GunTex, this->m_GunPosition, this->m_GunSize, this->m_GunRotation, this->Color);
	m_Bullets->Draw(renderer);

}


void PlayerObject::UpdateGunPosition()
{
	m_GunSize.x = Size.x * .2f;
	m_GunSize.y = Size.y * 2.6f;
	m_GunPosition.x = Position.x - 5.0f;
	m_GunPosition.y = (Position.y - m_GunSize.y + 8.0f);
	m_GunRotation = 0.0f;
}


