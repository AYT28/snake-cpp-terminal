#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "draw.hpp"
#include "classes.hpp"

static const char* colorOf(char ch, const Snake& snake, const std::vector<Food>& foods, int x, int y) {
    if (ch == '=' || ch == '@') return Ansi::BLUE;
    if (ch == 'O') return snake.get_color();
    if (ch == 'x') {
        // Find the food at the 'x' coordinate being drawn at that moment and return its color.
        for (const Food& f : foods) {
            if (f.get_x() == x && f.get_y() == y) {
                return f.get_color();
            }
        }
        return Ansi::RED; // If it can't find, it uses default color which is red
    }
    return Ansi::EMPTY;
}

void draw(Terminal& terminal, const Snake& snake, const std::vector<Food>& foods, int width, int height, int score) {
    std::vector<std::string> frame(height, std::string(width, ' '));

    for (int x = 0; x < width; x++) {
        frame[0][x] = '=';
        frame[height - 1][x] = '=';
    }
    for (int y = 1; y < height; y++) {
        frame[y][0] = '@';
        frame[y][width - 1] = '@';
    }
    for (const Point& p : snake.get_body()) {
        frame[p.get_y()][p.get_x()] = 'O';
    }
    for (const Food& f : foods) {
        frame[f.get_y()][f.get_x()] = 'x';
    }

    int termW, termH;
    terminal.getSize(termW, termH);
    int marginX = std::max(0, (termW - width) / 2);
    int marginY = std::max(0, (termH - height) / 2);

    std::string out;
    out.append(marginY, '\n');

    // Drawing loop
    for (int y = 0; y < height; y++) {
        out.append(marginX, ' ');
        for (int x = 0; x < width; x++) {
            char ch = frame[y][x];
            out += colorOf(ch, snake, foods, x, y);
            out += ch;
        }
        out = out + Ansi::EMPTY + "\n";
    }

    // Writing score
    std::string scoreText = "Score: " + std::to_string(score);
    out += '\n';
    out.append(marginX + (width - (int)scoreText.size()) / 2, ' ');
    out += scoreText;
    out += '\n';

    terminal.resetCursor();
    std::cout << out << std::flush;
}