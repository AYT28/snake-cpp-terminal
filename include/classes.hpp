#pragma once
#include <string>
#include <deque>

enum class Direction {
    UP,
    DOWN ,
    LEFT ,
    RIGHT
};

enum class FoodType {
    Normal,
    Trap
};

namespace Ansi {
    constexpr const char* BLACK = "\x1b[90m";
    constexpr const char* RED = "\x1b[91m";
    constexpr const char* GREEN = "\x1b[92m";
    constexpr const char* YELLOW = "\x1b[93m";
    constexpr const char* BLUE = "\x1b[94m";
    constexpr const char* PURPLE = "\x1b[95m";
    constexpr const char* CYAN = "\x1b[96m";
    constexpr const char* WHITE = "\x1b[97m";
    constexpr const char* EMPTY = "\x1b[0m";
    constexpr const char* CLEAR = "\x1b[2J\x1b[3J\x1b[H";
}

class Point {
    private:
    int x;
    int y;

    public:
    Point(int x, int y);

    int get_x() const;
    int get_y() const;
    void set_x(int x);
    void set_y(int y);
};

class Food : public Point {
    private:
    int value;
    FoodType type;
    int lifetime;

    public:
    Food(int x, int y, int value, FoodType type);

    int get_value() const;
    FoodType get_type() const;
    const char* get_color() const;
    void lifetime_tick();
    int get_lifetime() const;
};

class Snake {
    private:
    std::deque<Point> body;
    const char* color;
    Direction direction;

    public:
    Snake(std::initializer_list<Point> points, const char* color, Direction direction);

    const std::deque<Point>& get_body() const;
    const char* get_color() const;
    Direction get_direction() const;
    void set_direction(Direction direction);
    void new_head();
    void pop();
    Point get_head() const;
};