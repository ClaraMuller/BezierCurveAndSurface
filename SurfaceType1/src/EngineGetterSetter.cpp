#include "Engine.hpp"

int Engine::getCamX(void) const { return this->_camX; }
int Engine::getCamY(void) const { return this->_camY; }
int Engine::getCamZ(void) const { return this->_camZ; }

void Engine::setCamX(int param) {this->_camX = param; }
void Engine::setCamY(int param) {this->_camY = param; }
void Engine::setCamZ(int param) {this->_camZ = param; }


void
Engine::rotateBy(float x, float y, float z)
{
	this->_camX += x;
	this->_camY += y;
	this->_camZ += z;
}
