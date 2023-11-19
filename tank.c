/**
 * @file tank.c
 * @author Lim Jia Yin,Merylene ( jiayinmerylene.lim) - tank collects the power up, uses the power up and centering of the cannonball coming out from the tank
 * @author POH JING SENG (jingseng.poh) - rendering of tank on screen, rotation and movement
 * @brief this file is used to render, assign attributes to the tank and trigger actions that are related to the tank eg. movement etc
 * functions starting with _ at the front (eg._drawTank) is a in file function
 * 
 * _drawTank: used to draw the tank
 * _setTankColor: used to initalise the inital color for the tanks
 * _moveTanks: used to move tanks
 * _tankConstructor: used to assign attributes to the tank to initalise it
 * _createTank: used to call _tankConstructor to create a tank
 * _rendertank: used to render the tank on the screen when called 
 * _damageTank: used when the tank takes in damage
 * _tankUsePowerUp : checks for the specific keybinding to activate the powerup
 * _getTurretCenter: used to check where is the center of the turret
 * _tankShoot : used to call onFireCannonball when the keybinding for it is clicked 
 * _playMemeFire: used to play the meme sounds when the meme sounds settings are on 
 * _tankRefillHealth: was used for testing in game
 * _actiontank: used to iterate _tankShoot and _tankUsePowerUp to use it when needed 
 * _debugTank: this was used for debugging purposes
 * _findNoColTank: refer to the file level documentation for further details 
 * _colliionTank: handles all the collisions related to the tank 
 * initTank : Used to initalise values and load assets for the tank 
 * updateTank: runs in the loop for the users to make changes to
 * destoryTank: used to free all assests for the tank
 * 
 * @copyright Copyright Digipen 2023
 * 
 */

#include "config.h"
#include "cprocessing.h"
#include "tank.h"
#include "tank_utils.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "cannonball.h"
#include "collision.h"
#include "queue.h"
#include "winner.h"
#include "dropbox.h"
#include "powerup.h"

#define MOVEMENT_SPEED 300
#define ACCELERATION 300
#define DECELERATION (ACCELERATION * 3)
#define TURN_SPEED 100
#define REPAIR_TIME 0.1 // seconds
#define POWERUP_DURATION 10
#define NUM_MEME_FIRE_SOUNDS 6

CP_Sound tankFire;
CP_Sound collectPower;
CP_Sound usePower;
CP_Sound powerEnd;
CP_Sound memeTankFire[NUM_MEME_FIRE_SOUNDS] = { 0 };
extern CP_Sound tankHit;

extern double sfxVolume;
extern int SFX_GROUP;
extern int MEME_SFX_GROUP;

Queue history;

enum
{
	PLAYER_1,
	PLAYER_2
};
Tank tanks[NUM_PLAYERS] = {0};
Size tankSize = {75.f / 3 * 2, 100.f / 3 * 2};

extern Keybinds keybindings[];
extern Rect dropbox;

extern bool powerupPickedUp;


void _drawTank(Tank* tank) {
	CP_Color fillCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	drawTankAdvanced(tank, &fillCol, &strokeCol);

	if (tank->repairTimer > 0 || tank->hasCollided)
	{
		// debug_log("%lf\n", tank->repairTimer);
		//  make tank flash
		if ((int)(tank->repairTimer * 10) % 2 == 0)
		{
			CP_Color fillCol = CP_Color_Create(255, 255, 255, 255);
			CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
			drawTankAdvanced(tank, &fillCol, &strokeCol);
		}
	}
}

void _setTankColor(Tank *tank, BYTE r, BYTE g, BYTE b, BYTE a)
{
	tank->color.r = r;
	tank->color.g = g;
	tank->color.b = b;
	tank->color.a = a;
}

void _moveTanks(void)
{
	const double dt = CP_System_GetDt();
	double dDegrees = dt * TURN_SPEED; // dDegrees as in change in degrees like dx, dy (differentiate)

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		Tank *t = &tanks[i];

		double old = t->pos.direction;

		/*tu79*/
		if (t->speed == 0)
		{
			t->currentDir = FRONT;
		}

		/*movement*/
		if (CP_Input_KeyDown(keybindings[i].up) || CP_Input_KeyDown(keybindings[i].down))
		{
			t->speed += ACCELERATION * dt; // add speed
			if (t->currentDir == BACK)
			{ // limit speed to half of max speed if reversing
				t->speed = t->speed > MOVEMENT_SPEED / 2 ? MOVEMENT_SPEED / 2 : t->speed;
			}
			else
			{																	  // limit movement speed to max speed if going forwards
				t->speed = t->speed > MOVEMENT_SPEED ? MOVEMENT_SPEED : t->speed; // limit speed to MOVEMENT_SPEED
			}

			// if collided, set speed to 0
			bool isNewCollision = t->hasCollided != history.data[history.rear][i].hasCollided;
			if (isNewCollision)
			{
				t->speed = 0;
			}

			if (t->repairTimer > 0)
			{
				t->speed = 0;
				// dDegrees = 0;
			}

			const double distance = dt * abs((int)t->speed); // i have absolutely no idea why i cannot use other methods to ensure this isnt negative

			if (CP_Input_KeyDown(keybindings[i].up))
			{
				if (t->currentDir == BACK && t->speed > 0)
				{ // braking
					t->speed -= 2 * DECELERATION * dt;
					t->pos.x -= t->pos.d.x * distance;
					t->pos.y -= t->pos.d.y * distance;
				}
				else
				{
					t->pos.x += t->pos.d.x * distance;
					t->pos.y += t->pos.d.y * distance;
					t->currentDir = FRONT;
				}
			}
			else if (CP_Input_KeyDown(keybindings[i].down))
			{
				if (t->currentDir == FRONT && t->speed > 0)
				{ // braking
					t->speed -= 2 * DECELERATION * dt;
					t->pos.x += t->pos.d.x * distance;
					t->pos.y += t->pos.d.y * distance;
				}
				else
				{
					t->pos.x -= t->pos.d.x * distance;
					t->pos.y -= t->pos.d.y * distance;
					t->currentDir = BACK;
				}
			}
		}
		else
		{
			t->speed -= DECELERATION * dt;
			t->speed = t->speed < 0 ? 0 : t->speed; // limit speed to MOVEMENT_SPEED
			const double distance = dt * t->speed;

			if (t->currentDir == FRONT)
			{
				t->pos.x += t->pos.d.x * distance;
				t->pos.y += t->pos.d.y * distance;
			}
			else
			{
				t->pos.x -= t->pos.d.x * distance;
				t->pos.y -= t->pos.d.y * distance;
			}
		}

		/*directional input*/
		if (CP_Input_KeyDown(keybindings[i].left))
		{
			if (t->currentDir == BACK)
			{ // if reversing, invert directions
				t->pos.direction += dDegrees;
				t->pos.dDir = dDegrees;
			}
			else
			{
				if (t->pos.direction == 0)
				{
					t->pos.direction = (double)(360 - ceil(dDegrees));
				}
				else
				{
					t->pos.direction -= dDegrees / 2;
					t->pos.dDir = -(dDegrees / 2);
				}
			}
		}
		else if (CP_Input_KeyDown(keybindings[i].right))
		{
			if (t->currentDir == BACK)
			{ // if reversing, invert directions
				if (t->pos.direction == 0)
				{
					t->pos.direction = (double)(360 - ceil(dDegrees));
				}
				else
				{
					t->pos.direction -= dDegrees / 2;
					t->pos.dDir = -(dDegrees / 2);
				}
			}
			else
			{
				t->pos.direction += dDegrees;
				t->pos.dDir = dDegrees;
			}
		}
		t->pos.direction = t->pos.direction >= 0 ? t->pos.direction : -t->pos.direction;
		t->pos.direction = (double)((int)(t->pos.direction) % 360);
		t->pos.d = getDVector(t);
	}
}

Tank _tankConstructor(Position pos, Color color)
{
	Tank tank = {0};
	tank.pos = pos;
	tank.color = color;
	tank.health = MAX_HEALTH;
	tank.size = tankSize;
	// change to different kinds of ammo for debugging
	// enum { NORMAL, BIG_BULLET, SHOTGUN, RAPID_FIRE };
	tank.activeAmmo = NORMAL;

	/* add tank to tanks array */
	bool valid = false;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (tanks[i].pos.x == 0.f)
		{
			tanks[i] = tank;
			valid = true;
			break;
		}
	}
	if (!valid)
	{
		fprintf(stderr, "error: maximum number of tanks created (based on NUM_PLAYERS)\n");
		exit(1);
	}

	return tank;
}

Tank _createTank(double posX, double posY, double direction, BYTE r, BYTE g, BYTE b, BYTE a)
{
	Vector d = {direction == 90 ? 1 : -1, 0};
	Position pos = {posX, posY, direction, 0, d};
	Color col = {r, g, b, a};
	return _tankConstructor(pos, col);
}

void _renderTank(void)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		_drawTank(&tanks[i]);
	}
}


void _damageTank(Tank *tank, double damage)
{
	tank->health -= damage;
}

void _tankUsePowerUp(int i)
{ // int i is which tank it is in the array tanks[i]
	if (CP_Input_KeyDown(keybindings[i].usePower))
	{
		// takes in the tank that have the power up
		if (tanks[i].availPowerup != NORMAL)
		{
			tanks[i].activeAmmo = tanks[i].availPowerup;
			tanks[i].availPowerup = NORMAL; // no powerups available. reset state.
			tanks[i].powerElapsedTime = 0;
			CP_Sound_PlayAdvanced(usePower, (float)sfxVolume, 1.f, false, SFX_GROUP);

			debug_log("tank %d used powerups %d\n", i+1, tanks[i].activeAmmo);
		}
	}

	/*cancel powerup after time is up*/
	if (tanks[i].activeAmmo != NORMAL)  
	{
		const double dt = CP_System_GetDt();
		tanks[i].powerElapsedTime += dt;

		if (tanks[i].powerElapsedTime >= POWERUP_DURATION)
		{
			// Power-up duration has elapsed, reset activeAmmo to 0
			tanks[i].activeAmmo = NORMAL;
			CP_Sound_PlayAdvanced(powerEnd, (float)sfxVolume, 1.f, false, SFX_GROUP);
			debug_log("tank %d powerup finished\n", i+1);
		}
	}
}

Position _getTurretCenter(Tank *t, Size turretSize)
{
	double scalar = sqrt(pow(t->size.width / 2.0, 2.0) + pow(t->size.height / 2.0, 2.0)) * 1.1; // the distance between the point

	Position O = {0};
	O.x = t->pos.x + scalar * t->pos.d.x;
	O.y = t->pos.y + scalar * t->pos.d.y;

	return O;
}

void _playMemeFire(void) {
	int fire = getRand(0, 5);
	CP_Sound_PlayAdvanced(memeTankFire[fire], (float)sfxVolume, 1.f, false, MEME_SFX_GROUP);
	debug_log("played fire %d/%d", fire + 1, NUM_MEME_FIRE_SOUNDS);
}

void _tankShoot(int i, enum AMMO_TYPES activeAmmo) { //int i is which tank it is in the array tanks[i] 
	if (CP_Input_KeyDown(keybindings[i].shoot) && tanks[i].repairTimer == 0)
	{
		// using the exact address to find the directional vector
		Vector unitVector = getDVector(&tanks[i]);

		Size size = {0};
		size.height = (tanks[i].size.height * 0.6f) * 0.6f;
		size.width = (tanks[i].size.width * 0.6f) * 0.3f;

		Position turretTip = _getTurretCenter(&tanks[i], size);

		bool firingSuccess = onFireCannonball(turretTip, unitVector, i, activeAmmo);
		if (firingSuccess)
		{
			CP_Sound_PlayAdvanced(tankFire, (float)sfxVolume, 1.f, false, SFX_GROUP);
			debug_log("fired");
			_playMemeFire();
		}
	}
}

void _tankRefillHealth(void)
{
	if (CP_Input_KeyDown(KEY_F5))
	{
		for (int i = 0; i < NUM_PLAYERS; i++)
		{
			tanks[i].health = MAX_HEALTH;
		}
	}
}

/*!
 * @brief logic to handle shooting, collecting, using powerups
 */
void _actionTank(void)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		_tankShoot(i, tanks[i].activeAmmo);
		_tankUsePowerUp(i);
	}
}

/*debugging use only (collision dev)*/
void _debugTank(void)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		CP_Graphics_DrawCircle((float)tanks[i].pos.x, (float)tanks[i].pos.y, 5);
		Position corners[4] = {0};
		Rect r = {tanks[i].size, tanks[i].pos};
		_getRectCorners(&r, &tanks[i].pos.d, corners, true);
		for (int j = 0; j < 4; j++)
		{
			CP_Graphics_DrawCircle((float)corners[j].x, (float)corners[j].y, 5);
		}
	}
}

/**
 * @brief looks through the past `MAX`(256) frames and finds an instance of tank that did not collide
 * 
 * 		  basically, if the user collides with a wall, to prevent tunneling, teleport user to last nocollision position
 *		  so smart right
 *  
 * @param player 
 * @return Tank 
 */
Tank _findNoColTank(int player)
{
	int i = history.rear;
	do
	{
		i = (i - 1 + MAX_HISTORY) % MAX_HISTORY; // move backwards in the queue
		// debug_log("%d\n", history.data[i][player].hasCollided);
		if (!history.data[i][player].hasCollided)
		{
			Tank validTank = history.data[i][player];  // no collision
			Tank tank = tanks[player];
			tank.pos = validTank.pos;
			tank.speed = validTank.speed;
			return tank;
		}
	} while (i != history.front);
	return history.data[history.front][player];
}

// put all tank collision handling log here
void _collisionsTank(void)
{
	const double dt = CP_System_GetDt();

	bool hasCollidedTank = areTanksColliding(&tanks[0], &tanks[1]);
	if (hasCollidedTank)
	{
		debug_log("col tank");
	}

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		tanks[i].repairTimer = tanks[i].repairTimer <= 0 ? 0 : tanks[i].repairTimer - dt;

		bool hasCollidedWall = colTankWall(&tanks[i]);
		if (hasCollidedWall)
		{
			debug_log("tank %d has collided with wall\n", i + 1);
		}

		double damageTaken = 0;
		bool hasCollidedCb = colTankCb(&tanks[i], &damageTaken);
		if (hasCollidedCb)
		{
			debug_log("cannonball collided with tank %d\n", i + 1);
			_damageTank(&tanks[i], damageTaken);
			CP_Sound_PlayAdvanced(tankHit, (float)sfxVolume, 1.f, false, SFX_GROUP);
		}

		bool hasCollidedTree = collisionTree(&tanks[i]);
		if (hasCollidedTree)
		{
			debug_log("tank %d has collided with tree\n", i + 1);
		}

		if (hasCollidedWall || hasCollidedTank || hasCollidedTree)
		{
			tanks[i].hasCollided = true;
		}
		else
		{
			tanks[i].hasCollided = false;
		}

		/*dropbox logic*/
		Rect dbHitbox = (Rect){dropbox.size, (Position){dropbox.pos.x - dropbox.size.width / 2, dropbox.pos.y - dropbox.size.height / 2}};
		if (colTankRect(&tanks[i], &dbHitbox, false) && !powerupPickedUp)
		{
			tanks[i].availPowerup = getPowerup();
			CP_Sound_PlayAdvanced(collectPower, (float)sfxVolume, 1.f, false, SFX_GROUP);
			debug_log("tank %d picked up powerup %d\n", i + 1, tanks[i].availPowerup);
		}
	}
}

void initTank(void)
{
	_createTank(WINDOW_SIZE.width / 6, WINDOW_SIZE.height / 2, 90.f, 0, 255, 0, 255);
	_createTank(WINDOW_SIZE.width / 6 * 5, WINDOW_SIZE.height / 2, 270.f, 255, 0, 0, 255);
	initQueue(&history);
	tankFire = CP_Sound_Load("Assets/audio/sfx/tank_fire.mp3");
	debug_log("loaded tank firing sfx\n");
	collectPower = CP_Sound_Load("Assets/audio/sfx/collect_power_up.mp3");
	debug_log("loaded collect power up sfx\n");
	usePower = CP_Sound_Load("Assets/audio/sfx/using_power_up.mp3");
	debug_log("loaded using power up sfx\n");
	powerEnd = CP_Sound_Load("Assets/audio/sfx/powerup_end.mp3");
	debug_log("loaded end power up sfx\n");
	for (int i = 0; i < NUM_MEME_FIRE_SOUNDS; i++) {
		char path[MAX] = "";
		snprintf(path, MAX, "Assets/audio/meme/sfx/tank_shoot/bang_%d.mp3", i + 1);
		debug_log("Loaded meme fire Sound %d/%d from path %s\n", i + 1, NUM_MEME_FIRE_SOUNDS, path);
		memeTankFire[i] = CP_Sound_Load(path);
	}
}

void updateTank(bool isPaused)
{
	_renderTank();

	if (isPaused)
	{
		return;
	}

	_moveTanks();
	_actionTank();
	_collisionsTank();
	//_renderHealthBar();

	// capture history
	enqueue(&history, tanks[0], tanks[1]);

	if (DEBUG_MODE)
	{
		// _debugTank();
	}

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (tanks[i].hasCollided)
		{
			debug_log("tank %d collided\n", i + 1);
			tanks[i] = _findNoColTank(i);
			// tanks[i].speed = 0;
			tanks[i].repairTimer = REPAIR_TIME;
		}
	}

	// debug_log("%f\n", tanks[1].health);
	//_tankRefillHealth();
}

void destroyTank(void)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		Tank tank = {0};
		tanks[i] = tank;
	}
	if (tankFire != NULL)
	{
		CP_Sound_Free(&tankFire);
	}
	debug_log("freed tank fire sfx\n");
	for (int i = 0; i < NUM_MEME_FIRE_SOUNDS; i++) {
		if (memeTankFire[i] != NULL)
		{
			CP_Sound_Free(&memeTankFire[i]);
			debug_log("freed meme tank fire %d/%d sfx\n", i + 1, NUM_MEME_FIRE_SOUNDS);
		}

	}
	if (collectPower != NULL)
	{
		CP_Sound_Free(&collectPower);
	}
	if (usePower != NULL)
	{
		CP_Sound_Free(&usePower);
	}
	if (powerEnd != NULL)
	{
		CP_Sound_Free(&powerEnd);
	}

}
