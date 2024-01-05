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
    // Default ctor, initializes audio
    Game();

    // Clean up obstacles and audio
    ~Game();

    // Draw background, screen rectangle, title, score, & difficulties
    void draw_basic();

    // Draw title screen
    void draw_title_screen();

    // Draw difficulty options
    void draw_difficulty();

    // Draw obstacles
    void draw_obstacles();

    // Draw gameplay screen
    void draw_playing();

    // Draw lose screen
    void draw_lose();

    // Handle title screen inputs
    void title_input();

    // Handle lose screen inputs
    void lose_input();

    // Toggle obstaclesOn
    void toggle_obstacles();

    // Spawns a new obstacle
    void spawn_obstacle();

    // Returns true if currentTime seconds have passed
    bool interval_passed();

    // Handle snake movement inputs
    void move();

    // Return true if key press is compatible with current direction
    bool good_direction(KeyboardKey key) const;

    // Set snake direction
    void set_direction(KeyboardKey key);

    // Update snake and run collision checks
    void update();

    // If snake hits food, move food, increase snake size,
    // increment score, & play eatSound
    // Spawn obstacle if obstaclesOn is true
    void food_check();

    // Lose game if snake hits edge of grid
    void edge_check();

    // Lose game if snake hits itself
    void tail_check();

    // Lose game if snake hits obstacle
    void obstacle_check();

    // Set game state to LOSE, play wallSound
    void lose();

    // Reset snake, clear obstacles, return to title,
    // set score to 0
    void reset();

    // Set allowMove to true
    void allow_move();

    // Return game state
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