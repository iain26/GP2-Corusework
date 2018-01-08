#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "DisplayWindow.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Tex.h"
#include "transform.h"
#include "Sound.h"
#include "Cam.h"

enum class GameState{MENU, PLAY, EXIT};

class TheGame
{
public:
	TheGame();
	~TheGame();

	void run();

private:

	void Initialise();
	void Keyboard();
	void GameLoop();
	void Render(); 

	void CheckBird1Collision();
	void CheckBird2Collision();
	void CheckBird3Collision();

	void CheckBirdsOutRange();

	bool Collided(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void SetInitialPositions();
	float Distance(glm::vec3 a, glm::vec3 b);
	void PlaySoundFiles(unsigned int file, glm::vec3 pos);

	DisplayWindow displayWindow;
	GameState gameState;

	Mesh plane;
	Transform planeMovements;

	Mesh skySphere;
	Cam cam;

	glm::vec3 planePos;
	glm::vec3 leftEngine;
	glm::vec3 rightEngine;

	Mesh bird1;
	Mesh bird2;
	Mesh bird3;
	Transform bird1Movements;
	Transform bird2Movements;
	Transform bird3Movements;
	glm::vec3 bird1OrigPos = glm::vec3(6, 5, 50);
	glm::vec3 bird1target;
	glm::vec3 bird2OrigPos = glm::vec3(-6, 5, 100);
	glm::vec3 bird2target;
	glm::vec3 bird3OrigPos = glm::vec3(6, -5, 150);
	glm::vec3 bird3target;

	float bird1Incre = 0;
	float bird2Incre = 0;
	float bird3Incre = 0;

	float planeRotX = 0;
	float PlaneRotY = 0;
	float PlaneRotZ = 0;

	float engineOffsetx = 2.75;
	float engineOffsety = 0.2;
	float engineOffsetz = 2;

	int HitsTaken = 0;
	int HitLimit = 6;

	Sound audio;
	unsigned int jetSound;
	unsigned int hitSound;
	unsigned int chirpSound;
};

