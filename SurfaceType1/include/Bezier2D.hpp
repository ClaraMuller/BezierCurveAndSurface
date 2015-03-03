#ifndef BEZIER2D_HPP
# define BEZIER2D_HPP

# include <vector>
# include <Point.hpp>

class EnvSDL;

class	Bezier2D
{
private:

	const unsigned int			_iter;
	std::vector<Point<double> >	_aprox;

	Bezier2D(const Bezier2D& o);
	Bezier2D&	operator=(const Bezier2D& o);

public:
	Bezier2D(const int iter = 100);
	virtual ~Bezier2D(void) = default;

	unsigned int				getIter(void) const;
	std::vector<Point<double>> &	getAprox(void);

	void	clearAprox(void);

	void	casteljau(const std::vector<Point<double>> & v, float t);
	void	compute(const std::vector<Point<double> > & v);

};

#endif
