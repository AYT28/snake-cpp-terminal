#include <deque>
#include <ctime>
#include <vector>
#include <iostream>
#include "terminal.hpp"
#include "classes.hpp"
#include "input.hpp"
#include "draw.hpp"
#include "food.hpp"
#include "checks.hpp"
#include "screen.hpp"

int main() {
    Terminal terminal;
    terminal.setUTF8();
    terminal.setCursorVisibility(false);
    srand(time(0));

    std::string startArt = readTextFile("res/start.txt");
    
    // A restarting loop that wraps all of the program's loops
    bool playProgram = true;
    while (playProgram) {
        bool inMenu = true;
        const char* snakeColor = Ansi::GREEN;
        int termW, termH;
        terminal.getSize(termW, termH);
        int prevTermH = termH;
        int prevTermW = termW;

        // 1. Start Screen and Color Choosing
        while (inMenu) {
            terminal.getSize(termW, termH);
            if (termH != prevTermH || termW != prevTermW) {
                std::cout << Ansi::CLEAR;
                prevTermH = termH;
                prevTermW = termW;
            }

            drawScreen(terminal, startArt, Ansi::WHITE, termW, termH);

            if (terminal.keyPressed()) {
                char key = terminal.getKey();
                switch (key) {
                    case '1': 
                        snakeColor = Ansi::GREEN;
                        break;
                    case '2': 
                        snakeColor = Ansi::WHITE; 
                        break;
                    case '3': 
                        snakeColor = Ansi::PURPLE; 
                        break;
                    case '4': 
                        snakeColor = Ansi::YELLOW; 
                        break;
                }

                if (key == '1' || key == '2' || key == '3' || key == '4') {
                    inMenu = false;
                    std::cout << Ansi::CLEAR;
                    break;
                }

                if (key == 'q' || key == 'Q') {
                    playProgram = false;
                    break;
                }
            }
            Sleep(50);
        }

        if (!playProgram) {
            break;
        }

        // 2. Game Variables
        bool isGameRunning = true;
        Direction direction = Direction::UP;
        int width = 40;
        int height = 20;
        int score = 0;
        
        Snake snake({Point(8, 10), Point(9, 10), Point(10, 10)}, snakeColor, Direction::UP);
        std::vector<Food> foods = {};

        terminal.getSize(termW, termH);
        prevTermH = termH;

        // 3. Main Game Loop
        while (isGameRunning) {
            bool isEaten = false;

            moveDirection(terminal, snake, isGameRunning);
            scoreControl(score, isGameRunning);

            snake.new_head();

            checkFoodEaten(foods, snake, score, isEaten);
            selfCollision(isGameRunning, snake);
            wallCollision(isGameRunning, snake, width, height);

            if (!isGameRunning) {
                break;
            }

            if (!isEaten) {
                snake.pop();
            }

            while(foods.size() < 3) {
                generateFood(foods, width, height, snake);
            }

            for (int i = (int)foods.size() - 1; i >= 0; i--) {
                if(foods[i].get_type() == FoodType::Trap) {
                    foods[i].lifetime_tick();

                    if (foods[i].get_lifetime() >= 50) {
                        foods.erase(foods.begin() + i);
                    }
                }
            }

            terminal.getSize(termW, termH);
            if (termH != prevTermH) {
                std::cout << Ansi::CLEAR;
                prevTermH = termH;
            }

            draw(terminal, snake, foods, width, height, score);
            Sleep(100); // 10 FPS
        }

        // If game is over but user did not quit pressing Q, show game over screen
        if (!playProgram) break;

        std::cout << Ansi::CLEAR;
        bool waitingForRestart = true;
        
        while (waitingForRestart) {
            std::string gameOverText = readTextFile("res/gameover.txt");
            terminal.resetCursor();

            terminal.getSize(termW, termH);
            if (termH != prevTermH || termW != prevTermW) {
                std::cout << Ansi::CLEAR;
                prevTermH = termH;
                prevTermW = termW;
            }

            drawScreen(terminal, gameOverText, Ansi::GREEN, termW, termH);

            if (terminal.keyPressed()) {
                char k = terminal.getKey();
                if (k == 'r' || k == 'R') {
                    waitingForRestart = false;
                    std::cout << Ansi::CLEAR;
                }
                else if (k == 'q' || k == 'Q') {
                    waitingForRestart = false;
                    playProgram = false; // Break the main program loop
                }
            }
            Sleep(50);
        }
    }

    terminal.setCursorVisibility(true);
    std::cout << Ansi::CLEAR;
    return 0;
}