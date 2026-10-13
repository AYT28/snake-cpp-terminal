#pragma once
#include <string>
#include "terminal.hpp"

std::string readTextFile(const std::string& filepath);
void drawScreen(Terminal& terminal, const std::string& content, const char* color, int termW, int termH);