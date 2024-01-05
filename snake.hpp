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
    // Default ctor
    Snake();

    // Copy ctor
    Snake(Snake &other);

    // Draw snake
    void draw();

    // Add segment to front of snake
    // If segmentsToAdd > 0, decrement
    // Else, remove back segment
    void update();

    // Add segment to front of snake
    void add_front();

    // Pop front segment
    void pop_front();

    // Pop back segment
    void pop_back();

    // Reset snake body & direction to default
    void reset();

    // Increment segmentsToAdd
    void eat();

    // Set direction to dir
    void set_direction(Vector2 dir);

    // Return direction
    Vector2 get_direction() const;

    // Return Vector2 at front of body
    Vector2 head() const;

    // Return true if body contains vec
    bool contains(Vector2 vec) const;

  private:
    std::deque<Vector2> body;
    Vector2 direction;
    int segmentsToAdd;
};