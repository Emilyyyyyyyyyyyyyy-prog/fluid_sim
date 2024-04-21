#include "Field.h"
#include <SFML/Graphics.hpp>

class Fluid {
private:
	//Field property declarations
	Field u, u0, uSource;
	Field v, v0, vSource;
	Field density, density0, densitySource;
	Field div, p;

	//Physical property declarations
	float diffusion;
	float viscosity;

	//Simulation parameters
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
