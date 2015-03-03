#include "Color.hpp"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
	_r(r),
	_g(g),
	_b(b),
	_a(a)
{}

Color::Color(const Color& o)
{
	*this = o;
}

Color&
Color::operator=(const Color& o)
{
	this->_r = o._r;
	this->_g = o._g;
	this->_b = o._b;
	this->_a = o._a;
	return (*this);
}

Color::~Color(void)
{}


void
Color::setR(int param)
{
	if (param > 255)
		this->_r = 255;
	else
		this->_r = param;
}

void
Color::setG(int param)
{
	if (param > 255)
		this->_g = 255;
	else
		this->_g = param;
}

void
Color::setB(int param)
{
	if (param > 255)
		this->_b = 255;
	else
		this->_b = param;
}

void
Color::setA(int param)
{
	if (param > 255)
		this->_a = 255;
	else
		this->_a = param;
}
