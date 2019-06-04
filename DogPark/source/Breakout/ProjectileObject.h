#pragma once
#include <vector>
#include <GLAD/include/glad/glad.h>
#include <SeetyDog/Events/Event.h>

#include "Shader.h"
#include "Texture2D.h"
#include "GameObject.h"


/*class GameObject
{
public:
	// Object state
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	// Render state
	Texture2D   Sprite;
	// Constructor(s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
};*/

class Projectile : public GameObject
{
public://Constructors/Destructor
	Projectile(): m_LifeSpan(0.0f) { }
	~Projectile() {}
public://Members
	float m_LifeSpan;


};

// The PRojectileGenerator acts as a container  for projectiles. It handles the drawing,
// updating, texture, shaders, etc...
class ProjectileGenerator 
{
public://Constructors/Destructor
	ProjectileGenerator(Texture2D texture, unsigned int amountB4Recycle = 20);
public://Methods
	void ShootProjectile(glm::vec2 firingPosition, float rotation = 0.0f);
	bool Collision(GameObject& object);
	void Update(float dt);
//	void Update(float dt);
	void Draw(SpriteRenderer &renderer);
	void Init(glm::vec2& projVel, glm::vec2& projSize);
private://Methods
	unsigned int GetUnusedProjectile();
	void SpawnProjectile(Projectile &projectile, GameObject &object, float rotation = 0.0f, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void SpawnProjectile(Projectile &projectile, glm::vec2 position, float rotation = 0.0f, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
public://Members
	std::vector<Projectile> m_Projectiles;
	unsigned int m_Amount;
	unsigned int m_TotalAmmunition;
	//Shader m_Shader;
	Texture2D m_Texture;
	unsigned int m_LastUsedProjectile;


private://Members



};