#include "BallObject.h"


BallObject::BallObject()
	: GameObject(), Radius(12.5f), Stuck(true), Sticky(GL_FALSE), PassThrough(GL_FALSE) { }

BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
	: GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity),
	Radius(radius), Stuck(true), Sticky(GL_FALSE), PassThrough(GL_FALSE) { }
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		v
BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite, Shader shader)
	: GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity),
	Radius(radius), Stuck(true), Sticky(GL_FALSE), PassThrough(GL_FALSE), shader(shader), texture(texture)
{
	this->Init();
}
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		^

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

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
	this->Sticky = GL_FALSE;
	this->PassThrough = GL_FALSE;
}

//.//.//Testing "A simple 2D transformation by rotation."//.//.//		v
void BallObject::Init()
{
	trans = glm::mat4(1.0f);
}
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		^
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		v
void BallObject::Update(float dt)
{

	//this->Rotation += (dt * 0.5f);

}
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		^
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		v
void BallObject::Draw(SpriteRenderer &renderer)
{
	//this->shader.Use();
	//this->shader.SetMatrix4("trans", trans, true);
	//this->texture.Bind();
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);

}
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		^