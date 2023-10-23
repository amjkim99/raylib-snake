#include <algorithm>
#include "snake.hpp"

const int CELL_COUNT = 25;

class Entity {
  public:
    ~Entity();

    void draw();

    Vector2 random_cell();

    void new_pos(Snake snake);

    void load_texture(const char* path);

    Vector2 get_position() const;

  private:
    Vector2 position;
    Image image;
    Texture2D texture;
};

class Food : public Entity {
  public:
    Food(Snake snake);
};

class Obstacle : public Entity {
  public:
    Obstacle(Snake snake);
};
