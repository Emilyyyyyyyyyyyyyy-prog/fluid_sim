#include "Field.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Fluid {
private:
	//field property declarations
	//here we use 1) without index - parameters of a specific point; 2) with index 0 - initial movement; 3) with index source - parameters of sources
	Field u, u0, uSource;  //x_speed
	Field v, v0, vSource;  //y_speed
	Field density, density0, densitySource;
	Field div, p; //division, pressure

	//physical property declarations
	float diffusion;
	float viscosity;

	//simulation parameters
	float dt;
	int solverIterations;
	int xSize, ySize;
	
	//fluid physics functions
	void diffuseVelocity();
	void diffuseDensity();
	void advectVelocity();
	void advectDensity();
	void projectVelocity();
	void setBoundary(int d, Field x);
	void swapPointers(float*& x0, float*& x1);
public:
	Fluid();
	Fluid(int f_xSize, int f_ySize, float f_diff, float f_visc, float f_dt, int f_solverIterations);
	~Fluid();

	void addSource(int x0, int y0, int x, int y);
	void update();
	void reset();
	void render(int sixe, sf::Image& image);
};
