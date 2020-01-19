#include "stone.hpp"
#include <SDL2/SDL.h>
#include <iostream>

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

Stone::~Stone() {}

void Stone::update() {}

void Stone::draw(SDL_Renderer*& renderer) {
    if(isBlack) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    DrawCircle(renderer, 50 + x * 30, 50 + y * 30, 15);
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);
   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);
   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawLine(renderer, centreX + x, centreY - y,
                                   centreX + x, centreY + y);
      SDL_RenderDrawLine(renderer, centreX - x, centreY - y,
                                   centreX - x, centreY + y);
      SDL_RenderDrawLine(renderer, centreX + y, centreY - x,
                                   centreX + y, centreY + x);
      SDL_RenderDrawLine(renderer, centreX - y, centreY - x,
                                   centreX - y, centreY + x);
      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }
      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}
