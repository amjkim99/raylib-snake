#include "game.hpp"


Game::Game()
  : snake(), food(snake), obstacles(), state(TITLE), lastUpdateTime(0), score(0), allowMove(false), obstaclesOn(false), eatSound(LoadSound("resources/eat.mp3")), wallSound(LoadSound("resources/wall.mp3")) {
  InitAudioDevice();
}

Game::~Game() {
  obstacles.clear();
  UnloadSound(eatSound);
  UnloadSound(wallSound);
  CloseAudioDevice();
}

bool Game::interval_passed() {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= INTERVAL_TIME) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

void Game::move() {
  KeyboardKey key = static_cast<KeyboardKey>(GetKeyPressed());
  if (good_direction(key) && allowMove) {
    switch (key) {
      default:
        break;
      case KEY_UP:
        set_direction(KEY_UP);
        state = PLAYING;
        allowMove = false;
        break;
      case KEY_DOWN:
        set_direction(KEY_DOWN);
        state = PLAYING;
        allowMove = false;
        break;
      case KEY_LEFT:
        set_direction(KEY_LEFT);
        state = PLAYING;
        allowMove = false;
        break;
      case KEY_RIGHT:
        set_direction(KEY_RIGHT);
        state = PLAYING;
        allowMove = false;
        break;
    }
  }
}

bool Game::good_direction(KeyboardKey key) {
  switch (key) {
    default:
      break;
    case KEY_UP:
      return snake.get_direction().y != 1;
      break;
    case KEY_DOWN:
      return snake.get_direction().y != -1;
      break;
    case KEY_LEFT:
      return snake.get_direction().x != 1;
      break;
    case KEY_RIGHT:
      return snake.get_direction().x != -1;
      break;
  }
  return false;
}

void Game::set_direction(KeyboardKey key) {
  switch (key) {
    default:
      break;
    case KEY_UP:
      snake.set_direction(UP);
      break;
    case KEY_DOWN:
      snake.set_direction(DOWN);
      break;
    case KEY_LEFT:
      snake.set_direction(LEFT);
      break;
    case KEY_RIGHT:
      snake.set_direction(RIGHT);
      break;
  }
}

void Game::draw_basic() {
  ClearBackground(BLACK);
  DrawRectangleLinesEx(Rectangle{OFFSET - 5, OFFSET - 5, CELL_SIZE * CELL_COUNT + 10, CELL_SIZE * CELL_COUNT + 10}, 5, GREEN);
  DrawText("Snake", OFFSET - 5, 20, 40, GREEN);
  DrawText(TextFormat("%i", score), OFFSET - 5, OFFSET + CELL_SIZE * CELL_COUNT + 10, 40, GREEN);

  draw_difficulty();
}

void Game::draw_title_screen() {
  draw_basic();
  DrawText("Arrow keys to play", SCREEN_WIDTH / 2 - MeasureText("Arrow keys to play", 35) / 2, SCREEN_HEIGHT * 0.75 - 10, 35, GREEN);
  DrawText("TAB to change difficulty", SCREEN_WIDTH / 2 - MeasureText("TAB to change difficulty", 30) / 2, SCREEN_HEIGHT * 0.75 + 30, 30, GREEN);

  snake.draw();
}

void Game::title_input() {
  KeyboardKey key = static_cast<KeyboardKey>(GetKeyPressed());
  switch (key) {
    default:
      break;
    case KEY_UP:
    case KEY_DOWN:
    case KEY_RIGHT:
      state = PLAYING;
      break;
    case KEY_TAB:
      toggle_obstacles();
      break;
  }
}

void Game::draw_difficulty() {
  if (obstaclesOn) {
    DrawText("Easy", SCREEN_WIDTH - OFFSET - MeasureText("Easy", 40) - 40 - MeasureText("Hard", 40), 20, 40, DARKGREEN);
    DrawText("Hard", SCREEN_WIDTH - OFFSET - MeasureText("Hard", 40), 20, 40, GREEN);
  }
  else {
    DrawText("Easy", SCREEN_WIDTH - OFFSET - MeasureText("Easy", 40) - 40 - MeasureText("Hard", 40), 20, 40, GREEN);
    DrawText("Hard", SCREEN_WIDTH - OFFSET - MeasureText("Hard", 40), 20, 40, DARKGREEN);
  }
}

void Game::toggle_obstacles() {
  obstaclesOn = !obstaclesOn;
}

void Game::spawn_obstacle() {
  if (obstaclesOn) {
    Obstacle* newObstacle = new Obstacle(snake);
    obstacles.push_back(newObstacle);
  }
}

void Game::draw_obstacles() {
  for (auto obstacle : obstacles) {
    obstacle->draw();
  }
}

void Game::draw_playing() {
  draw_basic();
  draw_obstacles();
  food.draw();
  snake.draw();
}

void Game::update() {
  if (state == PLAYING) {
    food_check();
    snake.update();
    edge_check();
    tail_check();
    obstacle_check();
  }
}

void Game::food_check() {
  if (Vector2Equals(snake.head(), food.get_position())) {
    food.new_pos(snake);
    snake.eat();
    score++;
    PlaySound(eatSound);

    spawn_obstacle();
  }
}

void Game::edge_check() {
  if (snake.head().x == CELL_COUNT || snake.head().x == -1) {
    lose();
  }
  if (snake.head().y == CELL_COUNT || snake.head().y == -1) {
    lose();
  }
}

void Game::tail_check() {
  Snake headlessSnake(snake);
  headlessSnake.pop_front();
  if (headlessSnake.contains(snake.head())) {
    lose();
  }
}

void Game::obstacle_check() {
  for (auto obstacle : obstacles) {
    if (Vector2Equals(snake.head(), obstacle->get_position())) {
      lose();
    }
  }
}

void Game::draw_lose() {
  draw_basic();
  DrawText("YOU LOSE", SCREEN_WIDTH / 2 - MeasureText("YOU LOSE", 35) / 2, SCREEN_HEIGHT * 0.5 - 20, 35, GREEN);
  DrawText("SCORE: ", SCREEN_WIDTH / 2 - MeasureText("SCORE: ", 35) / 2 - 15, SCREEN_HEIGHT * 0.5 + 20, 35, GREEN);
  DrawText(TextFormat("%i", score), SCREEN_WIDTH / 2 - MeasureText("SCORE: ", 35) / 2 + 125, SCREEN_HEIGHT * 0.5 + 20, 35, GREEN);
  DrawText("R to reset", SCREEN_WIDTH / 2 - MeasureText("R to reset", 35) / 2, SCREEN_HEIGHT * 0.75, 35, GREEN);
  snake.draw();
}

void Game::lose() {
  snake.reset();
  state = LOSE;
  PlaySound(wallSound);
}

void Game::reset() {
  snake.reset();
  obstacles.clear();
  state = TITLE;
  score = 0;
  allowMove = false;
}

void Game::allow_move() {
  allowMove = true;
}

GameState Game::check_state() const {
  return state;
}