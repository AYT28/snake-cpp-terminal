#include "classes.hpp"
#include <vector>

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::get_x() const {
    return this->x;
}

int Point::get_y() const {
    return this->y;
}

void Point::set_x(int x) {
    this->x = x;
}

void Point::set_y(int y) {
    this->y = y;
}

Food::Food(int x, int y, int value, FoodType type) : Point(x, y) {
    this->value = value;
    this->type = type;
    this->lifetime = 0;
}

int Food::get_value() const {
    return this->value;
}

FoodType Food::get_type() const {
    return this->type;
}

const char* Food::get_color() const {
    if (this->get_type() == FoodType::Normal) {
        return Ansi::RED;
    } else {
        return Ansi::CYAN;
    }
}

void Food::lifetime_tick(){
    if (this->get_type() == FoodType::Trap) {
        lifetime++;
    }
}

int Food::get_lifetime() const {
    return this->lifetime;
}

Snake::Snake(std::initializer_list<Point> points, const char* color, Direction direction) : body(points), color(color), direction(direction)
{}

const std::deque<Point>& Snake::get_body() const {
    return this->body;
}

const char* Snake::get_color() const {
    return this->color;
}

Direction Snake::get_direction() const {
    return this->direction;
}

void Snake::set_direction(Direction direction) {
    this->direction = direction;
}

void Snake::new_head() {
    Point oldHead = this->body.front();

    int x = oldHead.get_x();
    int y = oldHead.get_y();

    if (this->get_direction() == Direction::UP) {
        y--;
    }
    else if (this->get_direction() == Direction::DOWN) {
        y++;
    }
    else if (this->get_direction() == Direction::LEFT) {
        x--;
    }
    else if (this->get_direction() == Direction::RIGHT) {
        x++;
    }

    this->body.push_front(Point(x, y));
}

void Snake::pop() {
    this->body.pop_back();
}

Point Snake::get_head() const{
    return this->body.front();
}