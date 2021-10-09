#include <iostream>
#include <SDL2/SDL.h>


#define STAND 0
#define MOVE 1
#define JUMP 2
#define FALL 3


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
    int cJumpLen = 0;
    int state = 0;
    int hdirection;
    bool aPressed = false;
    bool dPressed = false;
    bool spPressed = false;
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
    window = SDL_CreateWindow("Hoyien Game :)", 0, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
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
        case SDLK_SPACE:
          spPressed = true;
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
        case SDLK_SPACE:
          spPressed = false;
          break;
      }
    }
  }
  hdirection = 0;
  if (dPressed)
  {
    hdirection++;
    state = MOVE;
  }
  if (aPressed)
  {
    hdirection--;
    state = MOVE;
  }
  if (spPressed)
  {
    state = JUMP;
  }
  else if (pRect.y < height - (height / 100) - (height / 20))
  {
    state = FALL;
  }


  if (state == MOVE)
  {
    pRect.x += 20 * hdirection;
  }
  if (state == JUMP)
  {
    cJumpLen++;
    if (cJumpLen >= 15)
    {
      state = FALL;
    }
    else
    {
      pRect.y -= 20;
      pRect.x += 20 * hdirection;
    }
  }
  if (state == FALL)
  {
    pRect.y += 20;
    pRect.x += 20 * hdirection;
    if (pRect.y >= height - (height / 100) - (height / 20))
    {
      pRect.y = height - (height / 100) - (height / 20);
      state = STAND;
      std::cout << state << std::endl;
      cJumpLen = 0;
    }
  }
  std::cout << state << std::endl;
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
