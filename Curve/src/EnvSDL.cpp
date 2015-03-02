#include "EnvSDL.hpp"
#include "Scene.hpp"
#include <iostream>
#include <M_Error.hpp>

/* CONSTRUCT / DESTRUCT */

EnvSDL::EnvSDL(const int width, const int height, const std::string & title, std::ostream & os):
	_S_WIDTH(width),
	_S_HEIGHT(height),
	_title(title),
	_debug(os),
	_win(0),
	_ren(0),
	_text(0)
{}

EnvSDL::~EnvSDL()
{
	if (this->_text != 0)
		SDL_DestroyTexture(this->_text);
	if (this->_ren != 0)
		SDL_DestroyRenderer(this->_ren);
	if (this->_win != 0)
		SDL_DestroyWindow(this->_win);
	SDL_Quit();
}

EnvSDL::EnvSDL(const EnvSDL & o):
	_S_WIDTH(o._S_WIDTH),
	_S_HEIGHT(o._S_HEIGHT),
	_title("Windows SDL"),
	_debug(std::cout)
{
	(void)o;
}

EnvSDL&
EnvSDL::operator=(const EnvSDL & o)
{
	(void)o;
	return *this;
}

/* SDL */

bool
EnvSDL::init(void) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return (M_ERROR(false, "Fail SDL_Init"));
	}
	this->_win = SDL_CreateWindow(this->_title.c_str(), 50, 50, this->_S_WIDTH, this->_S_HEIGHT, SDL_WINDOW_SHOWN);
	if (this->_win == 0) {
		return (M_ERROR(false, "Fail SDL_CreateWindow"));
	}
	this->_ren = SDL_CreateRenderer(this->_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->_ren == 0) {
		return (M_ERROR(false, "Fail SDL_CreateRenderer"));
	}
	return (true);
}

void
EnvSDL::logSDLError(const std::string & msg)
{
	this->_debug << msg << " error: " << SDL_GetError() << std::endl;
}

bool
EnvSDL::loadTexture(const std::string & path)
{
	SDL_Surface	*bmp;

	bmp = SDL_LoadBMP(path.c_str());
	if (bmp == 0) {
		return (M_ERROR(false, "Fail SDL_LoadBMP(%s)", path.c_str()));
	}
	this->_text = SDL_CreateTextureFromSurface(this->_ren, bmp);
	if (this->_text == 0) {
		SDL_FreeSurface(bmp);
		return (M_ERROR(false, "Fail SDL_CreateTextureFromSurface"));
	}
	SDL_FreeSurface(bmp);
	return (true);
}

void
EnvSDL::showRender(void)
{
	SDL_RenderClear(this->_ren);
	SDL_RenderCopy(this->_ren, this->_text, NULL, NULL);
	SDL_RenderPresent(this->_ren);
}

void
EnvSDL::launch(Scene & sc)
{
	bool		run;
	SDL_Event	e;

	run = true;
	while (run == true)
	{
		SDL_WaitEvent(&e);
		if (e.type == SDL_QUIT)
			run = false;
		else if (e.type == SDL_KEYDOWN)
		{
			this->_debug << "key : " << e.key.keysym.sym << std::endl;
			if (e.key.keysym.sym == SDLK_ESCAPE)
				run = false;
		}
		SDL_SetRenderDrawColor(this->_ren, 0, 0, 0, 255);
		SDL_RenderClear(this->_ren);
		sc.drawPts(*this);
		sc.drawBezier2D(*this);
		SDL_RenderPresent(this->_ren);
	}
}

/* DRAWING */

void
EnvSDL::putPixel(int x, int y, const Color & c)
{
	SDL_SetRenderDrawColor(this->_ren, c._r, c._g, c._b, c._a);
	SDL_RenderDrawPoint(this->_ren, x, y);
}

void
EnvSDL::drawLine(int x1, int y1, int x2, int y2, const Color & c)
{
	SDL_SetRenderDrawColor(this->_ren, c._r, c._g, c._b, c._a);
	SDL_RenderDrawLine(this->_ren, x1, y1, x2, y2);
}

void
EnvSDL::drawSquare(int x, int y, int size, const Color & c)
{
	SDL_Rect square;

	square.x = x - size;
	square.y = y - size;
	square.w = size * 2;
	square.h = size * 2;
	SDL_SetRenderDrawColor(this->_ren, c._r, c._g, c._b, c._a);
	SDL_RenderFillRect(this->_ren, &square);
}

/* GETTERS */

int	EnvSDL::getWidthWindow(void) const { return this->_S_WIDTH; }
int	EnvSDL::getHeightWindow(void) const { return this->_S_HEIGHT; }
