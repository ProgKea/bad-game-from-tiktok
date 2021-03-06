#include "header.h"

int MouseX, MouseY;

int main() {
  init_sdl2();

  while (1) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        break;
      if (e.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&MouseX, &MouseY);
        aim_gun_pos(MouseX, MouseY, &Guns[active_gun]);
      }
      if (e.type == SDL_MOUSEBUTTONDOWN ||
          (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)) {
        shoot_gun(MouseX, MouseY, Guns[active_gun]);
      }
      if (e.type == SDL_MOUSEBUTTONUP ||
          (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)) {
        can_shoot = true;
      }
    }
    SDL_RenderClear(renderer);

    render_score(renderer, 50, 50, 50, (float)WIDTH / 2, (float)HEIGHT / 2);
    update_crates(renderer);
    render_active_gun();

    SDL_SetRenderDrawColor(renderer, 28, 28, 28, 255);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  destroy_guns();
  destroy_crates();

  return 0;
}
