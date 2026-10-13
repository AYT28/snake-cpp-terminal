#pragma once
#include <deque>
#include <vector>
#include "terminal.hpp"
#include "classes.hpp"
#include "food.hpp"

void draw(Terminal& terminal, const Snake& snake, const std::vector<Food>& foods, int width, int height, int score);