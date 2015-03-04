## Bezier Curve and Surface

Example of Bezier curves and surfaces approximation, using Casteljau's algorithm.

##### How to try it ?

Just clone the repo, compile with the Makefile and run it.

Test file have to follow the correct syntax in order to be read by the programm. Rules are the following:
* one point is define by his x, y and z coordinates in this order
* coordinates are separeted by a comma
* one point has to be circled by parentheses to separate from the others

An example of file could be : *(x1, y1, z1) (x2, y2, z2) (x3, y3, z3)*

### Curve

SDL2 library has been used for the graphical interface.
Control points of the file are represented by red squares in the graphical interface and are linked by blue line between each others. Bezier curve approximation is represented by all the yellow squares.
50 iterations are computing for the approximation.

### Surfaces

OpenGl library has been used for the graphical interface. Learning the graphical library with the tutorial : http://www.opengl-tutorial.org/beginners-tutorials. OpenGl extension libraries GLEW, GLM and GLFW has been added to the project.

##### Type 1

Comming soon

##### Type 2

Comming soon
