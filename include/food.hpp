#pragma once
#include "classes.hpp"
#include <vector>

void checkFoodEaten(std::vector<Food>& foods, Snake& snake, int& score, bool& isEaten);
void generateFood(std::vector<Food>& foods, int height, int width, const Snake& snake);