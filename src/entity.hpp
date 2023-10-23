#include <algorithm>
#include "snake.hpp"

const int CELL_COUNT = 25;

class Entity {
  public:
    // Dtor unloads texture
    ~Entity();

    // Draw texture at position
    void draw();

    // Return random Vector2 within grid
    Vector2 random_cell();

    // Sets position to a random new position that
    // does not overlap with snake
    void new_pos(Snake snake);

    // Load an image into texture via file path
    void load_texture(const char* path);

    // Return position
    Vector2 get_position() const;

  private:
    Vector2 position;
    Image image;
    Texture2D texture;
};

class Food : public Entity {
  public:
    // Ctor loads texture & randomizes position
    Food(Snake snake);
};

class Obstacle : public Entity {
  public:
    // Ctor loads texture & randomizes position
    Obstacle(Snake snake);
};
