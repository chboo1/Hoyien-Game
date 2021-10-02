#include <iostream>
#include <SDL2/SDL.h>


const int width = 1000;
const int height = 1000;


class Main
{
  public:
    bool init();
    bool loadGraphics();
    bool loadAudio();
    bool initRects();
    void gameloop();
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* p = NULL;
    SDL_Event e;
    SDL_Rect groundRect = {0, height - height / 100, width, height / 100};
    SDL_Rect pRect;
    bool quit = false;
    int hspeed = 0;
    int vspeed = 0;
    bool aPressed = false;
    bool dPressed = false;
    Main()
    {
      if (!init() || !loadGraphics() || !initRects())
      {
        std::cout << "Failed to initialize '~' :/" << std::endl;
      }
      else
      {
        while (!quit)
        {
          gameloop();
        }
      }
    }
};


bool Main::init()
{
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL has Failed :/ " << SDL_GetError();
  }
  else
  {
    window = SDL_CreateWindow("Hoyien Game :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
      success = false;
      std::cout << "The window apparently wasn't paid enough and didn't appear :/ " << SDL_GetError();
    }
    else
    {
      screenSurface = SDL_GetWindowSurface(window);
      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    }
  }
  return success;
}


bool Main::loadGraphics()
{
  p = SDL_LoadBMP("graphics/frame_1.bmp");
  bool success = true;
  if (p == NULL)
  {
    success = false;
  }
  return true;
}


bool Main::initRects()
{
  pRect.x = 0;
  pRect.y =  width - (width / 100 * 6);
  return true;
}


void Main::gameloop()
{
  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
    {
      quit = true;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch(e.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          quit = true;
          break;
        case SDLK_a:
          aPressed = true;
          break;
        case SDLK_d:
          dPressed = true;
          break;
      }
    }
    else if (e.type == SDL_KEYUP)
    {
      switch(e.key.keysym.sym)
      {
        case SDLK_a:
          aPressed = false;
          break;
        case SDLK_d:
          dPressed = false;
          break;
      }
    }
  }
  if (dPressed)
  {
    if (hspeed < 5)
    {
      hspeed++;
    }
    if (aPressed)
    {
      hspeed = 0;
    }
  }
  if (aPressed)
  {
    if (hspeed > -5)
    {
      hspeed--;
    }
    if (dPressed)
    {
      hspeed = 0;
    }
  }
  if (!dPressed && !aPressed)
  {
    if (hspeed < 0)
    {
      hspeed++;
    }
    if (hspeed > 0)
    {
      hspeed--;
    }
  }
  pRect.x += hspeed;
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_FillRect(screenSurface, &groundRect, SDL_MapRGB(screenSurface->format,  0xA5, 0x4A, 0x2A));
  SDL_BlitSurface(p, NULL, screenSurface, &pRect);
  SDL_UpdateWindowSurface(window);
}


int main(int argc, char* args[])
{
  Main daclass;
  return 0;
}
