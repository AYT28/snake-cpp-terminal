#pragma once
#include "classes.hpp"

void selfCollision(bool& isGameRunning, Snake& snake);
void wallCollision(bool& isGameRunning, const Snake& snake, int width, int height);
bool isPositionOccupied(int x, int y, const Snake& snake);
void scoreControl(int& score, bool& isGameRunning);