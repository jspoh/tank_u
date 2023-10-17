#pragma once

void tank_draw(Tank* Tank);

void tank_move(Tank* Tank, int direction);

Tank tankConstructor(Position position, Color color, float health, int activePowerUps[3],float elapsedPowerTime,int activePermPowers[3]);
