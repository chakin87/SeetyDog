#include "ProjectileObject.h"


ProjectileGenerator::ProjectileGenerator(Texture2D texture, unsigned int amountB4Recycle) :
	m_LastUsedProjectile(0), m_Texture(texture), m_Amount(amountB4Recycle), m_TotalAmmunition(45)
{
	
	//this->Init();
}

void ProjectileGenerator::ShootProjectile(glm::vec2 firingPosition, float rotation)
{
	if (m_TotalAmmunition > 0) {
		m_LastUsedProjectile = GetUnusedProjectile();
		SD_TRACE(m_LastUsedProjectile);
		SpawnProjectile(this->m_Projectiles[m_LastUsedProjectile], firingPosition, rotation);
	}
}

bool ProjectileGenerator::Collision(GameObject & object)
{
	for(auto& projy : this->m_Projectiles) {
	
		if (projy.m_LifeSpan > 0.0f) {
	
			if ((object.Destroyed == false) &&
				(projy.Position.y + 5.f  < object.Position.y + object.Size.y)&&
				((projy.Position.x >= object.Position.x)&&
				(projy.Position.x <= object.Position.x + object.Size.x ))) {

				SD_TRACE("Hit with the bullet!");
				object.Destroyed = true;
				projy.m_LifeSpan = 0.0f;
			}
		}
	}
	return false;
}

void ProjectileGenerator::Update(float dt)
{

	for (unsigned int  i = 0; i < m_Amount; ++i) {
		Projectile& pewpew = this->m_Projectiles[i];
		pewpew.m_LifeSpan -= dt;
		SD_TRACE(pewpew.m_LifeSpan);
		if (pewpew.m_LifeSpan > 0.0f) {
			//If the projectile is still alive, 
			//then we move and add red to it to show it heating up.
			pewpew.Position += pewpew.Velocity * dt;
			pewpew.Color.r += dt * 1.5;
		}
	}
}



void ProjectileGenerator::Draw(SpriteRenderer &renderer)
{
	
	for (auto& projectile : this->m_Projectiles) {
		if (projectile.m_LifeSpan > 0.0f) {
			renderer.DrawSprite(projectile.Sprite, projectile.Position, projectile.Size, projectile.Rotation, projectile.Color);
		}
	}
}

void ProjectileGenerator::Init(glm::vec2& projVel, glm::vec2& projSize)
{
	for (unsigned int i = 0; i < m_Amount; ++i) {
		this->m_Projectiles.push_back(Projectile());
		this->m_Projectiles.back().Sprite = m_Texture;
		this->m_Projectiles.back().Size = projSize;
		this->m_Projectiles.back().Velocity = projVel;
	}
}
unsigned int testLUP = 0;
unsigned int ProjectileGenerator::GetUnusedProjectile()
{
	unsigned int i;
	//Search for the last used Projectile if any.
	for (i = m_LastUsedProjectile; i < this->m_Amount; ++i) {
		if (this->m_Projectiles[i].m_LifeSpan <= 0.0f) {
			m_LastUsedProjectile = i;
			return i;
		}
	}
	for (i = 0; i < m_LastUsedProjectile; ++i) {
		if (this->m_Projectiles[i].m_LifeSpan <= 0.0f) {
			m_LastUsedProjectile = i;
			return i;
		}
	}
	m_LastUsedProjectile = 0;
	return 0;
}

void ProjectileGenerator::SpawnProjectile(Projectile & projectile, GameObject & object, float rotation, glm::vec2 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 12.0f;
	GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
	projectile.Position = (object.Position) + random + offset;
	projectile.Rotation = rotation;
	//projectile.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
	projectile.m_LifeSpan = 2.0f;
//	projectile.Velocity = object.Velocity * 0.1f;
}

void ProjectileGenerator::SpawnProjectile(Projectile & projectile, glm::vec2 position, float rotation, glm::vec2 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 12.0f;
	GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
	projectile.Position = (position) + random + offset;
	projectile.Rotation = rotation;
	//projectile.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
	projectile.m_LifeSpan = 2.0f;
//	projectile.Velocity = glm::vec2(0.0f, -5.0f);
}
