# Terminal Snake
A snake game written in C++ that runs in terminal.

This project was created as a learning project to practice C++.

# Features
- Multiple color choices for snake
- Two food types
- Score system
- Start and Game Over menu
- Terminal rendering using terminal APIs and ANSI escape sequences

# Requirements
- C++17 compiler
- CMake 3.20 or higher
- Windows x64

# Installation
Download snake-cpp-terminal-windows-x64.zip from the Releases section. Extract the zip file and run snake.exe.

# Manual Installation
Clone the repository: 
```
git clone https://github.com/AYT28/snake-cpp-terminal.git
cd <repositry_directory>
```
Build the project:
```
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```
Run the executable from the build directory

# Platform Support
Right now it only works in Windows. I am planning to make it work in Linux as well.
