#include "game.hpp"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake by amjkim");
  SetTargetFPS(60);

  Game game;

  while (WindowShouldClose() == false) {
    BeginDrawing();

    switch(game.check_state()) {
      case TITLE:
        game.title_input();
        game.draw_title_screen();
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
        game.lose_input();
        game.draw_lose();
        break;
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}