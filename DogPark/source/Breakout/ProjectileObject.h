#pragma once
#include <vector>
#include <GLAD/include/glad/glad.h>
#include <SeetyDog/Events/Event.h>

#include "Shader.h"
#include "Texture2D.h"
#include "GameObject.h"

class Projectile : public GameObject
{
public://Constructors/Destructor
	Projectile();
public://Methods
	//Base Class Methods
	//		virtual void Draw(SpriteRenderer &renderer);
private://Methods

public://Members
	//Base Class Members
			glm::vec2   Position, Size, Velocity;
			glm::vec3   Color;
			GLfloat     Rotation;
			GLboolean   IsSolid;
			GLboolean   Destroyed;
			Texture2D   Sprite;

private://Members

};

class ProjectileGenerator 
{
public://Constructors/Destructor

public://Methods

private://Methods

public://Members

private://Members



};