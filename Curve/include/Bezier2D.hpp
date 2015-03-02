#ifndef BEZIER2D_HPP
# define BEZIER2D_HPP

# include <list>
# include <vector>
# include <Point.hpp>

class	Bezier2D
{
private:

	const unsigned int		_iter;
	std::list<Point<double> >	_aprox;

	Bezier2D(const Bezier2D& o);
	Bezier2D&	operator=(const Bezier2D& o);

public:
	Bezier2D(const int iter = 50);
	virtual ~Bezier2D(void) = default;

	unsigned int			getIter(void) const;
	std::list<Point<double> > &	getAprox(void);

	void	casteljau(const std::vector<Point<double>> & v, float t);
	void	clearAprox(void);
};

#endif
