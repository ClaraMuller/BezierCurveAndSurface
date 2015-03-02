#ifndef ENVSDL_HPP
# define ENVSDL_HPP

# include <SDL2/SDL.h>
# include <string>
# include <iostream>

# include <Color.hpp>
# include <Point.hpp>

class Scene;

class EnvSDL
{
private:
	const int		_S_WIDTH;
	const int		_S_HEIGHT;
	const std::string	_title;
	std::ostream		&_debug;
	SDL_Window		*_win;
	SDL_Renderer		*_ren;
	SDL_Texture		*_text;

	EnvSDL(const EnvSDL & o);
	EnvSDL & operator=(const EnvSDL & o);

public:
	EnvSDL(const int width, const int height, const std::string & title, std::ostream & os);
	virtual ~EnvSDL();

	bool	init(void);
	bool	loadTexture(const std::string & path_bmp_file);
	void	showRender(void);
	void	logSDLError(const std::string &msg);
	void	launch(Scene & sc);

	void	putPixel(int x, int y, const Color & c);
	void	drawLine(int x1, int y1, int x2, int y2, const Color & c);
	void	drawSquare(int x, int y, int size, const Color & c);

	int	getWidthWindow(void) const;
	int	getHeightWindow(void) const;

};

#endif
