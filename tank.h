#pragma once

void Tank_draw(Tank* Tank);

void Tank_move(Tank* Tank);

Tank tankConstructor(Position position, Color color, float health, int activePowerUps[3],float elapsedPowerTime,int activePermPowers[3]);
