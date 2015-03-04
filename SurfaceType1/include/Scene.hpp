#ifndef SCENE_HPP
# define SCENE_HPP

# include "Point.hpp"
# include "Bezier2D.hpp"
# include <vector>

class Scene
{
private:
	float						_minx;
	float						_miny;
	float						_minz;
	float						_maxx;
	float						_maxy;
	float						_maxz;
	Bezier2D					_b2D;


public:

	std::vector<Point<double>>	_pts;

	enum
	{
		MARGE = 20,
		BORD = 50
	};

	Scene(void);
	virtual ~Scene(void);

	bool	setPts(const char *path_file);
	void	setMinXYZ(void);
	void	setMaxXYZ(void);

	float	getMinX(void) const;
	float	getMinY(void) const;
	float	getMinZ(void) const;
	float	getMaxX(void) const;
	float	getMaxY(void) const;
	float	getMaxZ(void) const;

	int								getBezierIter(void) const;
	std::vector<Point<double>> &	getBezierAprox(void);
	void							clearBezierAprox(void);

	void	computeBezier2D(void);
	void	computeBezier2D(std::vector<Point<double>> & pts);
};

#endif
