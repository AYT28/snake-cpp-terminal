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
        // O an çizilen 'x' koordinatındaki yemeği bul ve rengini döndür
        for (const Food& f : foods) {
            if (f.get_x() == x && f.get_y() == y) {
                return f.get_color(); // Yemek sınıfına eklediğin get_color() fonksiyonu
            }
        }
        return Ansi::RED; // Eğer bulunamazsa varsayılan renk
    }
    return Ansi::EMPTY;
}

void draw(Terminal& terminal, const Snake& snake, const std::vector<Food>& foods, int width, int height, int score) {
    std::vector<std::string> frame(height, std::string(width, ' '));

    // Çerçeve ve öğeleri yerleştirme kısımları aynı kalabilir...
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

    // Harf harf (x, y koordinatlarıyla) yazdırma döngüsü
    for (int y = 0; y < height; y++) {
        out.append(marginX, ' ');
        for (int x = 0; x < width; x++) {
            char ch = frame[y][x];
            out += colorOf(ch, snake, foods, x, y); // x ve y koordinatını gönderiyoruz
            out += ch;
        }
        out = out + Ansi::EMPTY + "\n";
    }

    // Skor yazdırma kısmı aynı kalabilir...
    std::string scoreText = "Score: " + std::to_string(score);
    out += '\n';
    out.append(marginX + (width - (int)scoreText.size()) / 2, ' ');
    out += scoreText;
    out += '\n';

    terminal.resetCursor();
    std::cout << out << std::flush;
}