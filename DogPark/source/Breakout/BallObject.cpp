#include "BallObject.h"

#include <SeetyDog/Input.h>
#include <SeetyDog/Logger.h>
#include <SeetyDog/KeyCodes.h>
#include <SeetyDog/MouseButtonCodes.h>

//TODO: Fix this using engine implementation
#include <GLAD/include/glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>
#include <SeetyDog/Application.h>


BallObject::BallObject()
	: GameObject(), Radius(12.5f), Stuck(true), Sticky(GL_FALSE), PassThrough(GL_FALSE) { }


BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite,
	ProjectileGenerator* projGen, Texture2D gunSprite, Texture2D bulletSprite, Shader paddleShader, Shader bulletShader)
	: GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity),
	Radius(radius), Stuck(true), Sticky(GL_FALSE), PassThrough(GL_FALSE), m_GunTex(gunSprite), m_BulletTex(bulletSprite),
	m_BulletShader(bulletShader)
{
	Position = pos;
	m_Bullets = projGen;
	//Size = paddleSize;
	this->Init();
}


glm::vec2 BallObject::Move(GLfloat dt, GLuint window_width)
{
	// If not stuck to player board
	if (!this->Stuck)
	{
		// Move the ball
		this->Position += this->Velocity * dt;
		// Then check if outside window bounds and if so, reverse velocity and restore at correct position
		if (this->Position.x <= 0.0f)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0.0f;
		}
		else if (this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}
		if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
	}
	return this->Position;
}

void BallObject::OnEvent(SeetyDog::Event & event)
{
	if (SeetyDog::Input::IsMouseButtonPressed(SD_MOUSE_BUTTON_LEFT)) {
		this->m_Bullets->ShootProjectile(glm::vec2(m_GunPosition.x + (m_GunSize.x * .5F), m_GunPosition.y - m_GunSize.y * 0.2f));
		//TODO: Fix this using a future engine implementation
	//	glm::vec2 MousePos;
		double mx, my;
		auto* window = static_cast<GLFWwindow*>(SeetyDog::Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &mx, &my);
		SD_TRACE(mx);
		SD_TRACE(my);
	}
	this->UpdateGunPosition();
}

void BallObject::UpdateGunPosition()
{
	m_GunSize.x = Size.x * .2f;
	m_GunSize.y = Size.y * 2.6f;
	m_GunPosition.x = Position.x - 5.0f;
	m_GunPosition.y = (Position.y - m_GunSize.y + 8.0f);
	m_GunRotation = 0.0f;
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
	this->Sticky = GL_FALSE;
	this->PassThrough = GL_FALSE;
	this->UpdateGunPosition();
}


void BallObject::Init()
{
	m_BulletVelocity = glm::vec2(0.0f, -450.0f);
	m_BulletSize = glm::vec2(7, 18);//m_GunSize * 5.f;
	this->m_Bullets->Init(m_BulletVelocity, m_BulletSize);
	this->UpdateGunPosition();
}

void BallObject::Update(float dt)
{

	this->UpdateGunPosition();
	//this->Rotation += (dt * 0.5f);
	this->m_Bullets->Update(dt);

}

void BallObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
	renderer.DrawSprite(this->m_GunTex, this->m_GunPosition, this->m_GunSize, this->m_GunRotation, this->Color);
	m_Bullets->Draw(renderer);
}
