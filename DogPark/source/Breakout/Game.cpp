#include "Game.h"

#include <algorithm>
#include <irrKlang/include/irrKlang.h>
using namespace irrklang;
//#include "SeetyDog/Input.h"
#include "SeetyDog/MouseButtonCodes.h"
#include "SeetyDog/KeyCodes.h"
#include "SeetyDog/Events/ApplicationEvent.h"
#include "SeetyDog/Events/KeyEvent.h"
#include "SeetyDog/Events/MouseEvent.h"
#include "Platform/Windows/WindowsInput.h"
//./#include "Platform/Windows/WindowsWindow.h"

#include "SeetyDog/Application.h"
#include "glm/glm/glm.hpp"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"
#include "TextRenderer.h"
#include <GLFW/include/GLFW/glfw3.h>




// Game-related State data
SpriteRenderer   *Renderer;
PlayerObject     *Player;


BallObject				*Ball;
ParticleGenerator		*Particles;
ParticleGenerator		*BulletParticles;
PostProcessor			*Effects;
ISoundEngine			*SoundEngine = createIrrKlangDevice();
TextRenderer			*Text;
ProjectileGenerator		*PG;

Game::Game(unsigned int width, unsigned int height)
	:m_State(GAME_ACTIVE), m_Keys(), m_Width(width), m_Height(height), ShakeTime(0.0f),
	Level(0), Lives(100)
{
}

Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Ball;
	delete Particles;
	delete Effects;
	delete Text;
	//SoundEngine->drop();
}

void Game::Init()
{
	// Load shaders

	ResourceManager::LoadShader((std::string)"source/Breakout/Resources/Shaders/basic.shader", (std::string)"sprite");
	ResourceManager::LoadShader((std::string)"source/Breakout/Resources/Shaders/particle.shader", (std::string)"particle");
	ResourceManager::LoadShader((std::string)"source/Breakout/Resources/Shaders/bullet_particle.shader", (std::string)"bulletParticle");
	ResourceManager::LoadShader((std::string)"source/Breakout/Resources/Shaders/postprocessing.shader", (std::string)"postprocessing");
	// Configure shaders
	//glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->m_Width), static_cast<GLfloat>(this->m_Height), 0.0f, -1.0f, 1.0f);


	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	ResourceManager::GetShader("bulletParticle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("bulletParticle").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/background.jpg", GL_FALSE, "background");
	
	
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/machine_gun.png", GL_TRUE, "gun");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/bullet.png", GL_TRUE, "bullet");
	
	
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/awesomefaceo.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/particle.png", GL_TRUE, "particle");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/bulletParticle.png", GL_TRUE, "bulletParticle");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/powerup_speed.png", GL_TRUE, "powerup_speed");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/powerup_sticky.png", GL_TRUE, "powerup_sticky");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/powerup_increase.png", GL_TRUE, "powerup_increase");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/powerup_confuse.png", GL_TRUE, "powerup_confuse");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/powerup_chaos.png", GL_TRUE, "powerup_chaos");
	ResourceManager::LoadTexture("source/Breakout/Resources/Textures/powerup_passthrough.png", GL_TRUE, "powerup_passthrough");
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);
	BulletParticles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("bulletParticle"), 200);
	Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->m_Width, this->m_Height);
	Text = new TextRenderer(this->m_Width, this->m_Height);
	Text->Load("source/Breakout/Resources/Fonts/OCRAEXT.TTF", 24);
	// Load levels
	GameLevel one; one.Load    ("source/Breakout/Resources/Levels/one.lvl", this->m_Width, this->m_Height * 0.5);
	GameLevel two; two.Load    ("source/Breakout/Resources/Levels/two.lvl", this->m_Width, this->m_Height * 0.5);
	GameLevel three; three.Load("source/Breakout/Resources/Levels/three.lvl", this->m_Width, this->m_Height * 0.5);
	GameLevel four; four.Load  ("source/Breakout/Resources/Levels/four.lvl", this->m_Width, this->m_Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;
	// Configure game objects

	//Set up Projectile Generator
	PG = new ProjectileGenerator(ResourceManager::GetTexture("bullet"));

	// Set up player
	glm::vec2 playerPos = glm::vec2(this->m_Width / 2 - PLAYER_SIZE.x / 2, this->m_Height - PLAYER_SIZE.y);
	Player = new PlayerObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"), PG,
		ResourceManager::GetTexture("gun"), ResourceManager::GetTexture("bullet"), ResourceManager::GetShader("sprite"), ResourceManager::GetShader("sprite"));



	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
	// Audio
	SoundEngine->play2D("source/Breakout/Resources/Sounds/breakout.mp3", GL_TRUE);



}

void Game::EventInput(SeetyDog::Event& event)
{

	if (event.GetEventType() == SeetyDog::EventType::KeyPressed) {
		if (SeetyDog::Input::IsKeyPressed(SD_KEY_ESCAPE)) {
			SD_INFO("Escape key hit");
			auto* window = static_cast<GLFWwindow*>(SeetyDog::Application::Get().GetWindow().GetNativeWindow());
			///SeetyDog::EventDispatcher d(event);
			//d.Dispatch(SeetyDog::WindowCloseEvent());
			//glfwSetWindowShouldClose(window, true);
			SeetyDog::WindowCloseEvent();
		}
		if (SeetyDog::Input::IsKeyPressed(SD_KEY_SPACE)) {

			if (Ball->Stuck) {
				Ball->Stuck = false;
			}
			else {
				Ball->Stuck = true;
			}
		}
	
		if (this->m_State == GAME_MENU)
		{
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_ENTER))
			{
				this->m_State = GAME_ACTIVE;
				//this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
			}
			if (SeetyDog::Input::IsKeyPressed(GLFW_KEY_W))
			{
				this->Level = (this->Level + 1) % 4;
				//this->KeysProcessed[GLFW_KEY_W] = GL_TRUE;
			}
			if (SeetyDog::Input::IsKeyPressed(GLFW_KEY_S))
			{
				if (this->Level > 0)
					--this->Level;
				else
					this->Level = 3;
				//this->KeysProcessed[GLFW_KEY_S] = GL_TRUE;
			}
		}
		if (this->m_State == GAME_WIN)
		{
			if (SeetyDog::Input::IsKeyPressed(GLFW_KEY_ENTER))
			{
				//this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
				Effects->Chaos = GL_FALSE;
				this->m_State = GAME_MENU;
			}
		}
	}
	Player->OnEvent(event);
}

void Game::ProcesInput(float dt)
{

	if (this->m_State == GAME_ACTIVE) {
		float velocity = PLAYER_VELOCITY * dt;

		if (SeetyDog::Input::IsKeyPressed(SD_KEY_A)) {
			if (Player->Position.x >= 0) {
				Player->Move(-velocity, this->m_Width);
			}
				if (Ball->Stuck)
					Ball->Position.x -= velocity;
			
		}
		if (SeetyDog::Input::IsKeyPressed(SD_KEY_D)) {
			if (Player->Position.x <= m_Width - Player->Size.x) {
				Player->Move(velocity, this->m_Width);
			}
				if (Ball->Stuck)
					Ball->Position.x += velocity;
			
		}
		// For Debugging Use Only! :P
		if (SeetyDog::Input::IsKeyPressed(SD_KEY_LEFT_SHIFT)) {
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_C)) {
				Player->Position.x = (Ball->Position.x + (Ball->Size.x / 2)) - (Player->Size.x / 2);
				SoundEngine->play2D("source/Breakout/Resources/Sounds/lesser_vibes_HTIS_Beeps_Synth_01_004.mp3");
			}
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_V)) {
				Ball->PassThrough = true;
				Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
				SoundEngine->play2D("source/Breakout/Resources/Sounds/lesser_vibes_HTIS_Beeps_Synth_01_004.mp3");
			}
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_F)) {
				Player->Size.x += 5;
				SoundEngine->play2D("source/Breakout/Resources/Sounds/lesser_vibes_HTIS_Beeps_Synth_01_004.mp3");
			}
		}
		if (SeetyDog::Input::IsKeyPressed(SD_KEY_LEFT_CONTROL)) {
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_C)) {
				Player->Position.x = (Ball->Position.x + (Ball->Size.x / 2)) - (Player->Size.x / 2);
				SoundEngine->play2D("source/Breakout/Resources/Sounds/lesser_vibes_HTIS_Beeps_Synth_01_004.mp3");
			}
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_V)) {
				Ball->PassThrough = false;
				Ball->Color = glm::vec3(1.0f);
				SoundEngine->play2D("source/Breakout/Resources/Sounds/lesser_vibes_HTIS_Beeps_Synth_01_004.mp3");
			}
			if (SeetyDog::Input::IsKeyPressed(SD_KEY_F)) {
				Player->Size.x -= 5;
				SoundEngine->play2D("source/Breakout/Resources/Sounds/lesser_vibes_HTIS_Beeps_Synth_01_004.mp3");
			}
		}
	}

}

void Game::Update(float dt)
{
	// Update objects
	Ball->Move(dt, this->m_Width);

//.//.//Testing "A simple 2D transformation by rotation."//.//.//		v
	Ball->Update(dt);
//.//.//Testing "A simple 2D transformation by rotation."//.//.//		^


	Player->Update(dt);



	// Check for collisions
	this->DoCollisions();
	// Update particles
	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2));


	// Update PowerUps
	this->UpdatePowerUps(dt);
	// Check loss condition
	if (Ball->Position.y >= this->m_Height) // Did ball reach bottom edge?
	{
		--this->Lives;
		// Did the player lose all his lives? : Game over
		if (this->Lives == 0)
		{
			this->ResetLevel();
			this->m_State = GAME_MENU;
		}
		this->ResetPlayer();
		// Check win condition
		if (this->m_State == GAME_ACTIVE && this->Levels[this->Level].IsCompleted())
		{
			this->ResetLevel();
			this->ResetPlayer();
			Effects->Chaos = GL_TRUE;
			this->m_State = GAME_WIN;
		}
	}
	// Reduce shake time
	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
			Effects->Shake = false;
	}
}

void Game::Render()
{
	if (this->m_State == GAME_ACTIVE || this->m_State == GAME_MENU || this->m_State == GAME_WIN)
	{   //Start effects renderer
		Effects->BeginRender();
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->m_Width, this->m_Height), 0.0f);
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		// Draw player
		Player->Draw(*Renderer);
		//Renderer->DrawSprite(ResourceManager::GetTexture("bullet"), glm::vec2(300.0f, 600.0f), glm::vec2(100, 105), 0.0f);

		// Draw PowerUps
		for (PowerUp &powerUp : this->PowerUps)
			if (!powerUp.Destroyed)
				powerUp.Draw(*Renderer);
		// Draw particles	
		Particles->Draw();
	//	for (auto bullet : Player->m_Bullets) {
	//		if (bullet.m_IsHit) {
	//			BulletParticles->Draw();
	//		}
	//	}

		// Draw ball
		Ball->Draw(*Renderer);
		//Finish effects renderer
		Effects->EndRender();
		Effects->Render(glfwGetTime());
		// Render text (don't include in postprocessing)
		std::stringstream ss; ss << this->Lives;
		Text->RenderText("Lives:" + ss.str(), 5.0f, 5.0f, 1.0f);
	}
	if (this->m_State == GAME_MENU)
	{
		Text->RenderText("Press ENTER to start", 250.0f, this->m_Height / 2, 1.0f);
		Text->RenderText("Press W or S to select level", 245.0f, this->m_Height / 2 + 20.0f, 0.75f);
	}
	if (this->m_State == GAME_WIN)
	{
		Text->RenderText("You WON!!!", 320.0f, this->m_Height / 2 - 20.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, this->m_Height / 2, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	}
}

void Game::ResetLevel()
{
	if (this->Level == 0)this->Levels[0].Load("source/Breakout/Resources/Levels/one.lvl", this->m_Width, this->m_Height * 0.5f);
	else if (this->Level == 1)
		this->Levels[1].Load("source/Breakout/Resources/Levels/two.lvl", this->m_Width, this->m_Height * 0.5f);
	else if (this->Level == 2)
		this->Levels[2].Load("source/Breakout/Resources/Levels/three.lvl", this->m_Width, this->m_Height * 0.5f);
	else if (this->Level == 3)
		this->Levels[3].Load("source/Breakout/Resources/Levels/four.lvl", this->m_Width, this->m_Height * 0.5f);
	this->Lives = 3;
}

void Game::ResetPlayer()
{
	// Reset player/ball stats
	Player->Reset();
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
	// Also disable all active powerups
	Effects->Chaos = Effects->Confuse = GL_FALSE;
	Ball->PassThrough = Ball->Sticky = GL_FALSE;
	Player->Color = glm::vec3(1.0f);
	Ball->Color = glm::vec3(1.0f);
}


void Game::UpdatePowerUps(GLfloat dt)
{
	for (PowerUp &powerUp : this->PowerUps)
	{
		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated)
		{
			powerUp.Duration -= dt;

			if (powerUp.Duration <= 0.0f)
			{
				// Remove powerup from list (will later be removed)
				powerUp.Activated = GL_FALSE;
				// Deactivate effects
				if (powerUp.Type == "sticky")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
					{	// Only reset if no other PowerUp of type sticky is active
						Ball->Sticky = GL_FALSE;
						Player->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "pass-through")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
					{	// Only reset if no other PowerUp of type pass-through is active
						Ball->PassThrough = GL_FALSE;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "confuse")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
					{	// Only reset if no other PowerUp of type confuse is active
						Effects->Confuse = GL_FALSE;
					}
				}
				else if (powerUp.Type == "chaos")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
					{	// Only reset if no other PowerUp of type chaos is active
						Effects->Chaos = GL_FALSE;
					}
				}
			}
		}
	}
	// Remove all PowerUps from vector that are destroyed AND !activated (thus either off the map or finished)
	// Note we use a lambda expression to remove each PowerUp which is destroyed and not activated
	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
		[](const PowerUp &powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
	), this->PowerUps.end());
}

GLboolean ShouldSpawn(GLuint chance)
{
	GLuint random = rand() % chance;
	return random == 0;
}
void Game::SpawnPowerUps(GameObject &block)
{
	if (ShouldSpawn(75)) // 1 in 75 chance
		this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
	if (ShouldSpawn(15)) // Negative powerups should spawn more often
		this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
	if (ShouldSpawn(15))
		this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
}

void ActivatePowerUp(PowerUp &powerUp)
{
	// Initiate a powerup based type of powerup
	if (powerUp.Type == "speed")
	{
		Ball->Velocity *= 1.2;
	}
	else if (powerUp.Type == "sticky")
	{
		Ball->Sticky = GL_TRUE;
		Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
	}
	else if (powerUp.Type == "pass-through")
	{
		Ball->PassThrough = GL_TRUE;
		Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
	}
	else if (powerUp.Type == "pad-size-increase")
	{
		Player->Size.x += 50;
	}
	else if (powerUp.Type == "confuse")
	{
		if (!Effects->Chaos)
			Effects->Confuse = GL_TRUE; // Only activate if chaos wasn't already active
	}
	else if (powerUp.Type == "chaos")
	{
		if (!Effects->Confuse)
			Effects->Chaos = GL_TRUE;
	}
}

GLboolean IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type)
{
	// Check if another PowerUp of the same type is still active
	// in which case we don't disable its effect (yet)
	for (const PowerUp &powerUp : powerUps)
	{
		if (powerUp.Activated)
			if (powerUp.Type == type)
				return GL_TRUE;
	}
	return GL_FALSE;
}


// Collision detection
GLboolean CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

//GLfloat ShakeTime = 0.0f;
void Game::DoCollisions()
{
	for (GameObject &box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Player->m_Bullets->Collision(box);
			
			//./Collision collisionBullet = CheckCollision(Player->m_Bullets[0], box);
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision)) // If collision is true
			{
				// Destroy block if not solid
				if (!box.IsSolid) {
					box.Destroyed = GL_TRUE;
					//Sound Effects
					SoundEngine->play2D("source/Breakout/Resources/Sounds/bleep.mp3");
					this->SpawnPowerUps(box);
				}
				else
				{   // if block is solid, enable shake effect
					ShakeTime = 0.05f;
					//Sound Effects
					SoundEngine->play2D("source/Breakout/Resources/Sounds/solid.wav");
					Effects->Shake = true;
				}
				// Collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (!(Ball->PassThrough && !box.IsSolid)) // don't do collision resolution on non-solid bricks if pass-through activated
				{
					if (dir == LEFT || dir == RIGHT) // Horizontal collision
					{
						Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
						// Relocate
						GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						Ball->Position.x += penetration; // Move ball to right
					else
						Ball->Position.x -= penetration; // Move ball to left;
					}
					else // Vertical collision
					{
						Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
						// Relocate
						GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
						if (dir == UP)
							Ball->Position.y -= penetration; // Move ball bback up
						else
							Ball->Position.y += penetration; // Move ball back down
					}
				}
			}
		}
	}
	for (PowerUp &powerUp : this->PowerUps)
	{
		if (!powerUp.Destroyed)
		{
			if (powerUp.Position.y >= this->m_Height)
				powerUp.Destroyed = GL_TRUE;
			if (CheckCollision(*Player, powerUp))
			{	// Collided with player, now activate powerup
				ActivatePowerUp(powerUp);
				//Sound Effects
				SoundEngine->play2D("source/Breakout/Resources/Sounds/powerup.wav");
				powerUp.Destroyed = GL_TRUE;
				powerUp.Activated = GL_TRUE;
			}
		}
	}
	// Also check collisions for player pad (unless stuck)
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		// Check where it hit the board, and change velocity based on where it hit the board
		GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
		GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		GLfloat percentage = distance / (Player->Size.x / 2);
		//Sound Effects
		SoundEngine->play2D("source/Breakout/Resources/Sounds/bleep.wav");
		// Then move accordingly
		GLfloat strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		//Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
		// Fix sticky paddle
		Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
		// If Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
		Ball->Stuck = Ball->Sticky;
	}
}

GLboolean CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
{
	// Get center point circle first 
	glm::vec2 center(one.Position + one.Radius);
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// Now retrieve vector between center circle and closest point AABB and check if length < radius
	difference = closest - center;

	if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
		return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
	else
		return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

// Calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}