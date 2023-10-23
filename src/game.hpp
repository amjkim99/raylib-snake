#include "entity.hpp"

const double INTERVAL_TIME = 0.2;
const int SCREEN_WIDTH = 2 * OFFSET + CELL_SIZE * CELL_COUNT;
const int SCREEN_HEIGHT = 2 * OFFSET + CELL_SIZE * CELL_COUNT;

enum GameState {
  TITLE = 0,
  PLAYING,
  LOSE
};

class Game {
  public:
    Game();

    ~Game();

    bool interval_passed();

    void move();

    bool good_direction(KeyboardKey key);

    void set_direction(KeyboardKey key);

    void draw_basic();

    void draw_title_screen();

    void title_input();

    void draw_difficulty();

    void toggle_obstacles();

    void spawn_obstacle();

    void draw_obstacles();

    void draw_playing();

    void update();

    void food_check();

    void edge_check();

    void tail_check();

    void obstacle_check();

    void draw_lose();

    void lose();

    void reset();

    void allow_move();

    GameState check_state() const;

  private:
    Snake snake;
    Food food;
    std::vector<Obstacle*> obstacles;
    GameState state;
    double lastUpdateTime;
    int score;
    bool allowMove;
    bool obstaclesOn;
    Sound eatSound;
    Sound wallSound;
};