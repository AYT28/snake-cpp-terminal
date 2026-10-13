#include <deque>
#include "classes.hpp"
#include "terminal.hpp"

void moveDirection(Terminal& terminal, Snake& snake, bool& isGameRunning) {
    if (terminal.keyPressed()) {
        char key = terminal.getKey();
        Direction direction = snake.get_direction();

        if (key != '\0') {
            if ((key == 'w' || key == 'W') && direction != Direction::DOWN){
                snake.set_direction(Direction::UP);
            }
            else if ((key == 's' || key == 'S') && direction != Direction::UP) {
                snake.set_direction(Direction::DOWN);
            }
            else if ((key == 'a' || key == 'A') && direction != Direction::RIGHT) {
                snake.set_direction(Direction::LEFT);
            }
            else if ((key == 'd' || key == 'D') && direction != Direction::LEFT) {
                snake.set_direction(Direction::RIGHT);
            }

            if(key == 'q' || key == 'Q') {
                isGameRunning = false;
            }
        }
    }
}