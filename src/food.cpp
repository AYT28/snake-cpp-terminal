#include "food.hpp"
#include "classes.hpp"
#include "checks.hpp"
#include <vector>
#include <deque>
#include <random>

void checkFoodEaten(std::vector<Food>& foods, Snake& snake, int& score, bool& isEaten) {
    for (int i = 0; i < foods.size(); i++) {
        if (snake.get_head().get_x() == foods[i].get_x() && snake.get_head().get_y() == foods[i].get_y()) {
            score += foods[i].get_value();
            isEaten = true;
            foods.erase(foods.begin() + i);
            break;
        }
    } 
}

void generateFood(std::vector<Food>& foods, int width, int height, const Snake& snake) {
    int foodX, foodY;

    do {
        foodX = rand() % (width - 2) + 1;
        foodY = rand() % (height - 2) + 1;
    } while(isPositionOccupied(foodX, foodY, snake));

    int typeRandom = rand() % 4 + 1;
    FoodType type;
    int value;

    if (typeRandom != 4) {
        type = FoodType::Normal ;
        value = 10;
    } else {
        type = FoodType::Trap;
        value = -5;
    }

    foods.push_back(Food(foodX, foodY, value, type));
}