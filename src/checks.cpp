#include "classes.hpp"

void selfCollision(bool& isGameRunning, Snake& snake) {
    const Point head = snake.get_head();
    const auto body = snake.get_body();

    for (int i = 1; i < body.size(); ++i) {
        if (head.get_x() == body[i].get_x() && head.get_y() == body[i].get_y()) {
            isGameRunning = false;
            break;
        }
    }
}

void wallCollision(bool& isGameRunning, const Snake& snake, int width, int height) {
    const Point head = snake.get_head();

    if (head.get_x() <= 0 || head.get_y() <= 0 || head.get_x() >= width - 1 || head.get_y() >= height - 1) {
        isGameRunning = false;
    }
}

bool isPositionOccupied(int x, int y, const Snake& snake) {
    for (const Point& p : snake.get_body()) {
        if (x == p.get_x() && y == p.get_y()) {
            return true;
        }
    }
    return false;
}

void scoreControl(int& score, bool& isGameRunning) {
    if (score < 0) {
        isGameRunning = false;
    }
}