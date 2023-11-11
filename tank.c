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
#include <time.h>


#define MOVEMENT_SPEED 500
#define ACCELERATION 200
#define DECELERATION (ACCELERATION * 3)
#define TURN_SPEED 100
#define REPAIR_TIME 1  // seconds
#define POWERUP_DURATION 10

Queue history;

enum { PLAYER_1, PLAYER_2 };
Tank tanks[NUM_PLAYERS] = { 0 };
Size tankSize = { 75.f, 100.f };

//meant to use for implementing the powerups
enum {
	NORMAL, BIG_BULLET, SHOTGUN, RAPID_FIRE
};

extern Keybinds keybindings[];

//// HARD CODING CERTAIN STUFF FOR NOW!!!!
//void drawHealthBar(Tank* tank, int playerIndex) {
//	CP_Color fillCol = CP_Color_Create(0, 255, 0, 255); // Green colour for health
//	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255); // Black colour for border
//
//	// Calculate percentage of health remaining
//	double healthPercentage = (tank->health / MAX_HEALTH) * 100.0;
//
//	// Calculate width of the health bar based on the tank's health
//	double barWidth = 2*(tank->size.width * (healthPercentage / 100.0));
//	double barHeight = 30;
//	//Size size = { barWidth, barHeight };
//	double xPos, yPos;
//	// Calculate position based on player index
//	if (playerIndex == 0)
//	{
//		xPos = 10; // Adjust x-position for player 1
//	}
//	else
//	{
//		xPos = WINDOW_SIZE.width - barWidth - 10; // Adjust x position for player 2
//	}
//
//	yPos = 50;
//
//	//Position barPos = { xPos, yPos };
//	//drawRect(&barPos, &size, &fillCol, &strokeCol);
//	CP_Settings_Fill(fillCol);
//	CP_Settings_Stroke(strokeCol);
//	CP_Graphics_DrawRect(xPos, yPos, barWidth, barHeight);
//
//	// Display HP value
//	CP_Settings_TextSize(25);
//	CP_Settings_Fill(fillCol);
//
//	char hpText[50];
//	snprintf(hpText, 50, "HP: %.0f", tank->health); // Convert HP value to string
//	CP_Font_DrawText(hpText, xPos + barWidth / 2, yPos - 20); // Draw HP text above health bar
//}

void _drawTank(Tank* tank) {
	CP_Color fillCol = CP_Color_Create(tank->color.r, tank->color.g, tank->color.b, tank->color.a);
	CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
	drawTankAdvanced(tank, &fillCol, &strokeCol);

	if (tank->repairTimer > 0) {
		//printf("%lf\n", tank->repairTimer);
		// make tank flash
		if ((int)(tank->repairTimer * 10) % 2 == 0) {
			CP_Color fillCol = CP_Color_Create(255, 255, 255, 255);
			CP_Color strokeCol = CP_Color_Create(0, 0, 0, 255);
			drawTankAdvanced(tank, &fillCol, &strokeCol);
		}
	}
}

void _setTankColor(Tank* tank, BYTE r, BYTE g, BYTE b, BYTE a) {
	tank->color.r = r;
	tank->color.g = g;
	tank->color.b = b;
	tank->color.a = a;
}


void _moveTanks(void) {
	const double dt = CP_System_GetDt();
	double dDegrees = dt * TURN_SPEED;  // dDegrees as in change in degrees like dx, dy (differentiate)

	for (int i = 0; i < NUM_PLAYERS; i++) {
		Tank* t = &tanks[i];

		double old = t->pos.direction;

		/*tu79*/
		if (t->speed == 0) {
			t->currentDir = FRONT;
		}


		/*movement*/
		if (CP_Input_KeyDown(keybindings[i].up) || CP_Input_KeyDown(keybindings[i].down)) {
			t->speed += ACCELERATION * dt;  // add speed
			if (t->currentDir == BACK) {  // limit speed to half of max speed if reversing
				t->speed = t->speed > MOVEMENT_SPEED / 2 ? MOVEMENT_SPEED / 2 : t->speed;
			}
			else {  // limit movement speed to max speed if going forwards
				t->speed = t->speed > MOVEMENT_SPEED ? MOVEMENT_SPEED : t->speed;  // limit speed to MOVEMENT_SPEED
			}

			// if collided, set speed to 0
			bool isNewCollision = t->hasCollided != history.data[history.rear][i].hasCollided;
			if (isNewCollision) {
				t->speed = 0;
			}

		if (t->repairTimer > 0) {
			t->speed = 0;
			// dDegrees = 0;	
		}

			const double distance = dt * abs((int)t->speed);  // i have absolutely no idea why i cannot use other methods to ensure this isnt negative

			if (CP_Input_KeyDown(keybindings[i].up)) {
				if (t->currentDir == BACK && t->speed > 0) {  // braking
					t->speed -= 2 * DECELERATION * dt;
					t->pos.x -= t->pos.d.x * distance;
					t->pos.y -= t->pos.d.y * distance;
				}
				else {
					t->pos.x += t->pos.d.x * distance;
					t->pos.y += t->pos.d.y * distance;
					t->currentDir = FRONT;
				}
			}
			else if (CP_Input_KeyDown(keybindings[i].down)) {
				if (t->currentDir == FRONT && t->speed > 0) {  // braking
					t->speed -= 2 * DECELERATION * dt;
					t->pos.x += t->pos.d.x * distance;
					t->pos.y += t->pos.d.y * distance;
				}
				else {
					t->pos.x -= t->pos.d.x * distance;
					t->pos.y -= t->pos.d.y * distance;
					t->currentDir = BACK;
				}
			}
		}
		else {
			t->speed -= DECELERATION * dt;
			t->speed = t->speed < 0 ? 0 : t->speed;  // limit speed to MOVEMENT_SPEED
			const double distance = dt * t->speed;

			if (t->currentDir == FRONT) {
				t->pos.x += t->pos.d.x * distance;
				t->pos.y += t->pos.d.y * distance;
			}
			else {
				t->pos.x -= t->pos.d.x * distance;
				t->pos.y -= t->pos.d.y * distance;
			}
		}

		/*directional input*/
		if (CP_Input_KeyDown(keybindings[i].left)) {
			if (t->currentDir == BACK) {  // if reversing, invert directions
				t->pos.direction += dDegrees;
				t->pos.dDir = dDegrees;
			}
			else {
				if (t->pos.direction == 0) {
					t->pos.direction = (double)(360 - ceil(dDegrees));
				}
				else {
					t->pos.direction -= dDegrees / 2;
					t->pos.dDir = -(dDegrees / 2);
				}
			}
		}
		else if (CP_Input_KeyDown(keybindings[i].right)) {
			if (t->currentDir == BACK) {  // if reversing, invert directions
				if (t->pos.direction == 0) {
					t->pos.direction = (double)(360 - ceil(dDegrees));
				}
				else {
					t->pos.direction -= dDegrees / 2;
					t->pos.dDir = -(dDegrees / 2);
				}
			}
			else {
				t->pos.direction += dDegrees;
				t->pos.dDir = dDegrees;
			}
		}
		t->pos.direction = t->pos.direction >= 0 ? t->pos.direction : -t->pos.direction;
		t->pos.direction = (double)((int)(t->pos.direction) % 360);
		t->pos.d = getDVector(t);
	}
}


Tank _tankConstructor(Position pos, Color color) {
	Tank tank = { 0 };
	tank.pos = pos;
	tank.color = color;
	tank.health = MAX_HEALTH;
	tank.size = tankSize;

	/* add tank to tanks array */
	bool valid = false;
	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (tanks[i].pos.x == 0.f) {
			tanks[i] = tank;
			valid = true;
			break;
		}
	}
	if (!valid) {
		fprintf(stderr, "error: maximum number of tanks created (based on NUM_PLAYERS)\n");
		exit(1);
	}

	return tank;
}

Tank _createTank(double posX, double posY, double direction, BYTE r, BYTE g, BYTE b, BYTE a) {
	Vector d = { direction == 90 ? 1 : -1, 0 };
	Position pos = { posX, posY, direction, 0, d };
	Color col = { r,g,b,a };
	return _tankConstructor(pos, col);
}

void _renderTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		_drawTank(&tanks[i]);
	}
}

//void _renderHealthBar(void) {
//	for (int i = 0; i < NUM_PLAYERS; i++) {
//		drawHealthBar(&tanks[i], i);
//	}
//}


void _damageTank(Tank* tank, double damage) {
	tank->health -= damage;
}

void _tankCollectPowerUp(int i) { //int i is which tank it is in the array tanks[i] 
	//logic for collecting powerups draft will change once the actual code for the area of rect is there
	//for (int i = 0; i < NUM_PLAYERS; i++) {
	//	if (checkRectangleCollision(tanks[i].pos.x,tanks[i].pos.y, powerUps.pos.x,powerUps.pos.y)) {
	//		for (int j = 0; j < POWERUPS_COUNT; j++) 
	//		{
	//			if (tanks[i].activePermPowers[i] == 0) 
	//			{
	//				tanks[i].activePermPowers[i] += powerUps.num;// for the tank to take in which powerup is 
	//			}

	//		}
	//	}
	//}

}


void _tankUsePowerUp(int i) { //int i is which tank it is in the array tanks[i] 
	static clock_t powerUpStartTime = 0;
		if (CP_Input_KeyDown(keybindings[i].usePower)) {
			for (int j = 0; j < POWERUPS_COUNT; j++)
			{
				//takes in the tank that have the power up
				if (tanks[i].activePermPowers[j] != 0) {
					tanks[i].activePowerUps = tanks[i].activePermPowers[j];
					powerUpStartTime = clock(); //takes in the time that the function is being called
				}
			}
		}
		if (tanks[i].activePowerUps != 0) {
			clock_t currentTime = clock();
			double elapsedTime = (double)(currentTime - powerUpStartTime) / CLOCKS_PER_SEC;

			if (elapsedTime >= POWERUP_DURATION) {
				// Power-up duration has elapsed, reset activePowerUps to 0
				tanks[i].activePowerUps = NORMAL;
			}
		}

}

Position _getTurretCenter(Tank* t, Size turretSize) {
	double scalar = sqrt(pow(t->size.width / 2.0, 2.0) + pow(t->size.height / 2.0, 2.0)); //the distance between the point

	Position O = { 0 };
	O.x = t->pos.x + scalar * t->pos.d.x;
	O.y = t->pos.y + scalar * t->pos.d.y;

	return O;
}




void _tankShoot(int i, int activePowerUp) { //int i is which tank it is in the array tanks[i] 
	if (CP_Input_KeyDown(keybindings[i].shoot))
	{
		//using the exact address to find the directional vector 
		Vector unitVector = getDVector(&tanks[i]);

		Size size = { 0 };
		size.height = (tanks[i].size.height * 0.6f) * 0.6f;
		size.width = (tanks[i].size.width * 0.6f) * 0.3f;

		Position turretTip = _getTurretCenter(&tanks[i], size);

		switch (activePowerUp) {
		case NORMAL:
			onFireCannonball(turretTip, unitVector, i);
			break;
		//case BIG_BULLET:
		//	onFireBigBullet(turretTip, unitVector, i);
		//	break;
		//case SHOTGUN:
		//	onFireShotGunBullets(turretTip, unitVector, i);
		//	break;
		//case RAPID_FIRE:
		//	onRapidFireCannonballs(turretTip, unitVector, i);
		//	break;
		default:
			onFireCannonball(turretTip, unitVector, i); // switched default to normal cannonball shooting just incase
			break;
		}

	}

}


void _tankRefillHealth(void) {
	if (CP_Input_KeyDown(KEY_F5)) {
		for (int i = 0; i < NUM_PLAYERS; i++) {
			tanks[i].health = MAX_HEALTH;
		}
	}
}

/*!
* @brief logic to handle shooting, collecting, using powerups
*/
void _actionTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		_tankCollectPowerUp(i);
		_tankShoot(i,tanks[i].activePowerUps);
		_tankUsePowerUp(i);

	}
}


/*debugging use only (collision dev)*/
void _debugTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		CP_Graphics_DrawCircle((float)tanks[i].pos.x, (float)tanks[i].pos.y, 5);
		Position corners[4] = { 0 };
		Rect r = { tanks[i].size, tanks[i].pos };
		_getRectCorners(&r, &tanks[i].pos.d, corners, true);
		for (int j = 0; j < 4; j++) {
			CP_Graphics_DrawCircle((float)corners[j].x, (float)corners[j].y, 5);
		}
	}
}

Tank _findNoColTank(int player) {
	int i = history.rear;
	do {
		i = (i - 1 + MAX_HISTORY) % MAX_HISTORY; // move backwards in the queue
		// printf("%d\n", history.data[i][player].hasCollided);
		if (!history.data[i][player].hasCollided) {
			// puts("found");
			return history.data[i][player];
		}
	} while (i != history.front);
	return history.data[history.front][player];
}

void _collisionsTank(void) {
	const double dt = CP_System_GetDt();

	bool hasCollidedTank = areTanksColliding(&tanks[0], &tanks[1]);
	if (hasCollidedTank) {
		puts("col tank");
	}

	for (int i = 0; i < NUM_PLAYERS; i++) {
		tanks[i].repairTimer = tanks[i].repairTimer <= 0 ? 0 : tanks[i].repairTimer - dt;

		bool hasCollidedWall = colTankWall(&tanks[i]);
		if (hasCollidedWall) {
			puts("col wall");
		}

		bool hasCollidedCb = colTankCb(&tanks[i]);
		if (hasCollidedCb) {
			puts("BOOM");
		}

		if (hasCollidedWall || hasCollidedTank) {
			// puts("have ok\n");
			tanks[i].hasCollided = true;
		}
		else {
			tanks[i].hasCollided = false;
		}
	}
}

void initTank(void) {
	_createTank(WINDOW_SIZE.width / 6, WINDOW_SIZE.height / 2, 90.f, 0, 255, 0, 255);
	_createTank(WINDOW_SIZE.width / 6 * 5, WINDOW_SIZE.height / 2, 270.f, 255, 0, 0, 255);
	initQueue(&history);
}

void updateTank(void) {

	_moveTanks();
	_actionTank();
	_collisionsTank();
	_renderTank();
	//_renderHealthBar();

	// capture history
	enqueue(&history, tanks[0], tanks[1]);

	_debugTank();


	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (tanks[i].hasCollided) {
			tanks[i] = _findNoColTank(i);
			// tanks[i].speed = 0;
			tanks[i].repairTimer = REPAIR_TIME;
		}
	}
}

void destroyTank(void) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		Tank tank = { 0 };
		tanks[i] = tank;
	}
}
