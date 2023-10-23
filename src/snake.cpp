#include "snake.hpp"

Snake::Snake()
  : body({Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}}), direction({1, 0}), segmentsToAdd(0) { }

Snake::Snake(Snake &other)
  : body(other.body), direction(other.get_direction()), segmentsToAdd(0) { }

void Snake::draw() {
  for (size_t i = 0; i < body.size(); i++) {
    float x = body[i].x;
    float y = body[i].y;
    Rectangle segment = Rectangle{OFFSET + x * CELL_SIZE, OFFSET + y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    DrawRectangleRounded(segment, 0.5, 6, GREEN);
  }
}

void Snake::update() {
  add_front();
  if (segmentsToAdd > 0) {
    segmentsToAdd--;
  }
  else {
    pop_back();
  }
}

void Snake::add_front() {
  body.push_front(Vector2Add(body[0], direction));
}

void Snake::pop_front() {
  body.pop_front();
}

void Snake::pop_back() {
  body.pop_back();
}

void Snake::reset() {
  body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  direction = {1, 0};
}

void Snake::eat() {
  segmentsToAdd++;
}

void Snake::set_direction(Vector2 dir) {
  direction = dir;
}

Vector2 Snake::get_direction() const {
  return direction;
}

Vector2 Snake::head() const {
  return body[0];
}

bool Snake::contains(Vector2 vec) const {
  for (size_t i = 0; i < body.size(); i++) {
    if (Vector2Equals(body[i], vec)) {
      return true;
    }
  }
  return false;
}