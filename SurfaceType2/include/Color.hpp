#ifndef COLOR_HPP
# define COLOR_HPP

# include <cstdint>

class	Color
{
public:

	uint8_t	_r;
	uint8_t	_g;
	uint8_t	_b;
	uint8_t	_a;

	Color(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);
	Color(const Color& o);
	Color&	operator=(const Color& o);
	virtual ~Color(void);

	void	setR(int param);
	void	setG(int param);
	void	setB(int param);
	void	setA(int param);
};

#endif
