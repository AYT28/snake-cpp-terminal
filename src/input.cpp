#include <deque>
#include "classes.hpp"
#include "terminal.hpp"

void moveDirection(Terminal& terminal, Direction& direction, bool& isGameRunning) {
    if (terminal.keyPressed()) {
        char key = terminal.getKey();

        if (key != '\0') {
            if ((key == 'w' || key == 'W') && direction != Direction::DOWN){
                direction = Direction::UP;
            }
            else if ((key == 's' || key == 'S') && direction != Direction::UP) {
                direction = Direction::DOWN;
            }
            else if ((key == 'a' || key == 'A') && direction != Direction::RIGHT) {
                direction = Direction::LEFT;
            }
            else if ((key == 'd' || key == 'D') && direction != Direction::LEFT) {
                direction = Direction::RIGHT;
            }

            if(key == 'q' || key == 'Q') {
                isGameRunning = false;
            }
        }
    }
}