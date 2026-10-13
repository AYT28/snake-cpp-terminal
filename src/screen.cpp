#include "screen.hpp"
#include "classes.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

std::string readTextFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return "Dosya bulunamadı: " + filepath;
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str(); 
}

void drawScreen(Terminal& terminal, const std::string& content, const char* color, int termW, int termH) {
    std::vector<std::string> lines;
    std::stringstream ss(content);
    std::string line;
    int maxLineWidth = 0;

    while (std::getline(ss, line)) {
        lines.push_back(line);
        if ((int)line.size() > maxLineWidth) {
            maxLineWidth = (int)line.size();
        }
    }

    int marginX = std::max(0, (termW - maxLineWidth) / 2);
    int marginY = std::max(0, (termH - (int)lines.size()) / 2);

    std::string out;
    out.append(marginY, '\n');

    for (const auto& l : lines) {
        out.append(marginX, ' ');
        out += color;
        out += l;
        out = out + Ansi::EMPTY + "\n";
    }

    terminal.resetCursor();
    std::cout << out << std::flush;
}