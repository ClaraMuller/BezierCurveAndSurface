#ifndef SCENE_HPP
# define SCENE_HPP

# include "Point.hpp"
# include "Bezier2D.hpp"
# include <vector>

class Scene
{
private:
	float		_minx;
	float		_miny;
	float		_minz;
	float		_maxx;
	float		_maxy;
	float		_maxz;
	int		_sizeMap;


public:

	std::vector<Point<double>>	_pts;
	std::vector<Point<double>>	_ptsScale;

	enum
	{
		MARGE = 20,
		BORD = 50
	};

	Scene(int sizeMap);
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

};

#endif
