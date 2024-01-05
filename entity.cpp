#include "entity.hpp"

Entity::~Entity() {
  UnloadTexture(texture);
}

void Entity::draw() {
  DrawTexture(texture, OFFSET + get_position().x * CELL_SIZE, OFFSET + get_position().y * CELL_SIZE, WHITE);
}

Vector2 Entity::random_cell() {
  float x = GetRandomValue(0, CELL_COUNT - 1);
  float y = GetRandomValue(0, CELL_COUNT - 1);
  return Vector2{x, y};
}

void Entity::new_pos(Snake snake) {
  position = random_cell();
  while (snake.contains(position)) {
    position = random_cell();
  }
}

void Entity::load_texture(const char* path) {
  image = LoadImage(path);
  texture = LoadTextureFromImage(image);
  UnloadImage(image);
}

Vector2 Entity::get_position() const {
  return position;
}

Food::Food(Snake snake) {
  const char* path = "resources/food.png";
  load_texture(path);
  new_pos(snake);
}

Obstacle::Obstacle(Snake snake) {
  const char* path = "resources/obstacle.png";
  load_texture(path);

  snake.add_front();
  new_pos(snake);
}