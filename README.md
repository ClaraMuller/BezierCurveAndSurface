# Bezier Curve and Surface

Example of Bezier curves and surfaces approximation, using Casteljau's algorithm.

##### How to try it ?

Just clone the repo, compile with the Makefile and run it.

Test file have to follow the correct syntax in order to be read by the programm. Rules are the following:
* one point is define by his x, y and z coordinates in this order
* coordinates are separeted by a comma
* one point has to be circled by parentheses to separate from the others

An example of file could be : *(x1, y1, z1) (x2, y2, z2) (x3, y3, z3)*

## Curve

SDL2 library has been used for the graphical interface.

##### Caption

* Control points of the file are represented by **red squares** in the graphical interface and are linked by **blue line** between each others.
* Bezier curve approximation is represented by all the **yellow squares**.

50 iterations are computing for the approximation.

## Surfaces



OpenGl library has been used for the graphical interface. Learning the graphical library with the tutorials :
* http://www.opengl-tutorial.org/beginners-tutorials.
* http://guillaume.belz.free.fr/doku.php

OpenGl extension libraries GLEW, GLM and GLFW has been added to the project.

##### **Moves**

Rotations around x, y, z axis with the right button mouse and zoom with up and down arrow on the keybord.

##### **Caption**

Height of the vertices is represented by different colors.
* **green** : land with zero height
* **grey** : land with negative height
* **brown** : land with positive height
* **white** : highest point of controls

Real and artificial points of contols are visible.
* **yellow** : Points of control read in file parameter. To each point of the file, four others point are added : two at the map extremity and two at LIM distance of the real point in order to accentuate the landscape relief.
* **violet / red** : artificial control points set at the extremity of the map.
* **red** : new points computed with bezier approximaton. Approximation is computed between yellow, violet and red point. This new points are saved in order to compute the global surface in the next step.

##### **Drawing Mode**

You can give the parameter "MULTI" after the control point file for trying a new drawing mode. By default, only one Bezier curve go through all the control points and this curve is used for computing the surface. If the "multi" option is choosen, a bezier curve will be approximated for each control point. It computes a different surface, mostly smoother but also with less reliefs.

### Type 1
Control points of the first type has to be between 0 entre the number of iterations of Bezier approximation (here we choose 100) because the map is define between 0 and the number of approximation too.

### Type 2

For the second type, I tried to imitate more like a games tray than a real landscape. So I divided the map into squares, and for each square, check if a control point is inside it. If I found out one or several, I compute the surface like in the first surface type but with the square delimitation.


