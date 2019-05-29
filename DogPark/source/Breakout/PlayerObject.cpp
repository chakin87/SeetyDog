#include "PlayerObject.h"

#include <SeetyDog/Input.h>
#include <SeetyDog/Logger.h>
#include <SeetyDog/KeyCodes.h>
#include <SeetyDog/MouseButtonCodes.h>

#include "ResourceManager.h"


PlayerObject::PlayerObject()
{
}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 paddleSize, Texture2D paddleSprite, Texture2D gunSprite, Shader paddleShader, Shader bulletShader)
	: m_PaddleTex(paddleSprite), m_GunTex(gunSprite), m_NumActiveBullets(0),
	m_PlayerShader(paddleShader), m_BulletShader(bulletShader), m_PaddleInitSize(paddleSize), m_PaddleInitPosition(pos)
{
	Position = pos;
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
		this->ShootGun();
		SD_TRACE("Mouse Button Pressed!");
	}
}

void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
}

void PlayerObject::Init()
{
	Size = m_PaddleInitSize;
	Position = m_PaddleInitPosition;
	this->UpdateGunPosition();
}

void PlayerObject::Reset()
{
	this->Init();
}

void PlayerObject::Update(float dt)
{
	for (auto& bullet : m_Bullets) {
		if (bullet.m_IsFlying) {

		}
	}
}

void PlayerObject::Draw(SpriteRenderer & renderer)
{
	renderer.DrawSprite(this->m_PaddleTex, this->Position, this->Size, this->Rotation, this->Color);
	renderer.DrawSprite(this->m_GunTex, this->m_GunPosition, this->m_GunSize, this->m_GunRotation, this->Color);
}

void PlayerObject::ShootGun()
{
	if (m_Bullets.size() < m_MAX_BULLETS) {
		m_Bullets.emplace_back(BulletObject());
		m_Bullets.back().m_IsFlying = true;
	}
}

void PlayerObject::UpdateGunPosition()
{
	m_GunSize.x = Size.x * .2f;
	m_GunSize.y = Size.y * 2.6f;
	m_GunPosition.x = Position.x - 5.0f;
	m_GunPosition.y = (Position.y - m_GunSize.y + 8.0f);
	m_GunRotation = 0.0f;
}
