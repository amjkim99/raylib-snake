#include <iostream>
#include <vector>
#include <deque>
#include <raylib.h>
#include <raymath.h>

const float CELL_SIZE = 30;
const float OFFSET = 75;


const Vector2 UP = {0, -1};
const Vector2 DOWN = {0, 1};
const Vector2 LEFT = {-1, 0};
const Vector2 RIGHT = {1, 0};

class Snake {
  public:
    Snake();

    Snake(Snake &other);

    void draw();

    void update();

    void add_front();

    void pop_front();

    void pop_back();

    void reset();

    void eat();

    void set_direction(Vector2 dir);

    Vector2 get_direction() const;

    Vector2 head() const;

    bool contains(Vector2 vec) const;

  private:
    std::deque<Vector2> body;
    Vector2 direction;
    int segmentsToAdd;
};