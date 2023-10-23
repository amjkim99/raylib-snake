#include "game.hpp"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake by amjkim");
  SetTargetFPS(60);

  Game game;

  while (WindowShouldClose() == false) {
    BeginDrawing();

    switch(game.check_state()) {
      case TITLE:
        game.draw_title_screen();
        game.title_input();
        break;
      case PLAYING:
        if (game.interval_passed()) {
          game.allow_move();
          game.update();
        }
        game.move();
        game.draw_playing();
        break;
      case LOSE:
        game.draw_lose();
        if (IsKeyPressed(KEY_R)) {
          game.reset();
        }
        break;
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}