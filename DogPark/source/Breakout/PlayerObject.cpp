#include "PlayerObject.h"

#include <SeetyDog/Input.h>
#include <SeetyDog/Logger.h>
#include <SeetyDog/KeyCodes.h>
#include <SeetyDog/MouseButtonCodes.h>

#include "ResourceManager.h"


PlayerObject::PlayerObject()
{
}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 paddleSize, Texture2D paddleSprite, Texture2D gunSprite, Texture2D bulletSprite, Shader paddleShader, Shader bulletShader)
	: m_PaddleTex(paddleSprite), m_GunTex(gunSprite), m_BulletTex(bulletSprite),// m_NumActiveBullets(0),
	m_PlayerShader(paddleShader), m_BulletShader(bulletShader), m_PaddleInitSize(paddleSize), m_PaddleInitPosition(pos)//,
	//m_BulletVelocity(-100.0f)
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
	m_BulletVelocity = glm::vec2(0.0f, -250.0f);
	m_BulletSize = glm::vec2(70, 85);//m_GunSize * 5.f;
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
			
			bullet.m_Position += m_BulletVelocity * dt;
		}
	}
}

void PlayerObject::Draw(SpriteRenderer & renderer)
{
	renderer.DrawSprite(this->m_PaddleTex, this->Position, this->Size, this->Rotation, this->Color);
	renderer.DrawSprite(this->m_GunTex, this->m_GunPosition, this->m_GunSize, this->m_GunRotation, this->Color);
	for (auto& bullet : m_Bullets) {
		if (bullet.m_IsFlying == true) {
			renderer.DrawSprite(this->m_BulletTex, bullet.m_Position, this->m_BulletSize, bullet.Rotation);
		}
	}

}

void PlayerObject::ShootGun()
{
	if (m_Bullets.size() <= m_MAX_BULLETS) {
		SD_TRACE("Mouse Button Pressed!");
		m_Bullets.emplace_back(BulletObject());
		m_Bullets.back().m_IsFlying = true;
		m_Bullets.back().m_Position.x = this->m_GunPosition.x - 19.0f;
		m_Bullets.back().m_Position.y = this->m_GunPosition.y - 50.f;// (m_GunSize.y);
	}
	else {
		return;
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
