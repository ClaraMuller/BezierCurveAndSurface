#ifndef SCENE_HPP
# define SCENE_HPP

# include "Point.hpp"
# include "Bezier2D.hpp"
# include <vector>

class EnvSDL;

class Scene
{
private:
	std::vector<Point<double>>	_pts;
	Bezier2D			_b2D;


public:

	Scene(void);
	virtual ~Scene(void);

	bool	setPts(const char *path_file);

	void	drawPts(EnvSDL & env) const;
	void	drawBezier2D(EnvSDL & env);
};

#endif
