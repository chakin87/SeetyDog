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
	: m_PaddleTex(paddleSprite), m_GunTex(gunSprite),
	m_PlayerShader(paddleShader), m_BulletShader(bulletShader), m_PaddleInitSize(paddleSize), m_PaddleInitPosition(pos)
{
	Position = pos;
	Size = paddleSize;
	this->Init();
}

void PlayerObject::Move(float velocity, unsigned int winWidth)
{
	if (this->Position.x >= 0 && (this->Position.x <= winWidth - this->Size.x))
	Position.x += velocity;
	this->UpdateGunPosition();


}

void PlayerObject::OnEvent(SeetyDog::Event& event)
{
	if (SeetyDog::Input::IsMouseButtonPressed(SD_MOUSE_BUTTON_LEFT)) {
		//./glm::vec2 bulletPos = Gun->Position;
		//./bulletPos.x += GUN_SIZE.x * .5f;
		//./bulletPos.y -= Gun->Size.y;
		//./Bullets[0] = new GameObject(bulletPos, glm::vec2(6.0f, 8.0f), ResourceManager::GetTexture("bullet"));
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
}

void PlayerObject::Draw(SpriteRenderer & renderer)
{
	renderer.DrawSprite(this->m_PaddleTex, this->Position, this->Size, this->Rotation, this->Color);
	renderer.DrawSprite(this->m_GunTex, this->m_GunPosition, this->m_GunSize, this->m_GunRotation, this->Color);
}

void PlayerObject::ShootGun()
{
}

void PlayerObject::UpdateGunPosition()
{
	m_GunSize.x = Size.x * .2f;
	m_GunSize.y = Size.y * 2.6;
	m_GunPosition.x = Position.x;
	m_GunPosition.y = (Position.y - m_GunPosition.y + 3.0f);
	m_GunRotation = 0.0f;
}
