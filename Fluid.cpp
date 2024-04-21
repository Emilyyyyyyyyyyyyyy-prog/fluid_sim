#include "Fluid.h"
#include <iostream>

Fluid::Fluid() {}


Fluid::Fluid(int f_xSize, int f_ySize, float f_diff, float f_visc, float f_dt, int f_solverIterations) {
	this->xSize = f_xSize;
	this->ySize = f_ySize;
	this->diffusion = f_diff;
	this->viscosity = f_visc;
	this->dt = f_dt;
	this->solverIterations = f_solverIterations;
	this->u.set(this->xSize, this->ySize);
	this->v.set(this->xSize, this->ySize);
	this->density.set(this->xSize, this->ySize);
	this->u0.set(this->xSize, this->ySize);
	this->v0.set(this->xSize, this->ySize);
	this->density0.set(this->xSize, this->ySize);
	this->uSource.set(this->xSize, this->ySize);
	this->vSource.set(this->xSize, this->ySize);
	this->densitySource.set(this->xSize, this->ySize);
	this->div.set(this->xSize, this->ySize);
	this->p.set(this->xSize, this->ySize);
}

void Fluid::update() {
	for (int x = 1; x <= this->xSize; x++) {
		for (int y = 1; y <= this->ySize; y++) {
			this->u0.values[x + y * (this->xSize + 2)] = this->uSource.values[x + y * (this->xSize + 2)];
			this->v0.values[x + y * (this->xSize + 2)] = this->vSource.values[x + y * (this->xSize + 2)];
			this->uSource.values[x + y * (this->xSize + 2)] = 0;
			this->vSource.values[x + y * (this->xSize + 2)] = 0;
		}
	}

	diffuseVelocity();
	projectVelocity();
	swapPointers(this->u0.values, this->u.values);
	swapPointers(this->v0.values, this->v.values);
	advectVelocity();
	projectVelocity();

	for (int x = 1; x <= this->xSize; x++) {
		for (int y = 1; y <= this->ySize; y++) {
			this->density0.values[x + y * (this->xSize + 2)] += this->densitySource.values[x + y * (this->xSize + 2)];
			this->densitySource.values[x + y * (this->xSize + 2)] = 0;
		}
	}

	diffuseDensity();
	swapPointers(this->density0.values, this->density.values);
	advectDensity();

}

void Fluid::reset() {
	for (int x = 1; x <= this->xSize; x++) {
		for (int y = 1; y <= this->ySize; y++) {
			this->u0.values[x + y * (this->xSize + 2)] = 0;
			this->v0.values[x + y * (this->xSize + 2)] = 0;
			this->u.values[x + y * (this->xSize + 2)] = 0;
			this->v.values[x + y * (this->xSize + 2)] = 0;
			this->density0.values[x + y * (this->xSize + 2)] = 0;
			this->densitySource.values[x + y * (this->xSize + 2)] = 0;
		}
	}
}

void Fluid::render(int size, sf::Image& image) {//draw pixel by pixel
	for (int x = 0; x <= this->xSize + 1; x++) {
		for (int y = 0; y <= this->ySize + 1; y++) {
			if (this->density.values[x + y * (this->xSize + 2)] > 1) {
				this->density.values[x + y * (this->xSize + 2)] = 1;
			}
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					image.setPixel(x * size + i, y * size + j, sf::Color(255 * this->density.values[x + y * (this->xSize + 2)], 255 * this->density.values[x + y * (this->xSize + 2)], 255 * this->density.values[x + y * (this->xSize + 2)]));
				}
			}
			this->density0.values[x + y * (this->xSize + 2)] = this->density.values[x + y * (this->xSize + 2)];
			this->u0.values[x + y * (this->xSize + 2)] = this->u.values[x + y * (this->xSize + 2)];
			this->v0.values[x + y * (this->xSize + 2)] = this->v.values[x + y * (this->xSize + 2)];
		}
	}
}
void Fluid::addSource(int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	if (abs(dx) >= abs(dy)) {
		int yi = 1;
		if (dy < 0) {
			yi = -1;
			dy = -dy;
		}
		int D = 2 * dy - dx;
		int y = y0;
		int elementID = 0;
		if (dx > 0) {
			for (int x = x0; x <= x1; x++) {
				elementID = x + (this->xSize + 2) * y;
				this->densitySource.values[elementID] = 1;
				this->uSource.values[elementID] = (x1 - x0) / this->dt;
				this->vSource.values[elementID] = (y1 - y0) / this->dt;
				if (D > 0) {
					y += yi;
					D -= 2 * dx;
				}
				D += 2 * dy;
			}
		}
		else if (dx < 0) {
			D = 2 * dy + dx;
			for (int x = x0; x >= x1; x--) {
				elementID = x + (this->xSize + 2) * y;
				this->densitySource.values[elementID] = 1;
				this->uSource.values[elementID] = (x1 - x0) / this->dt;
				this->vSource.values[elementID] = (y1 - y0) / this->dt;
				if (D > 0) {
					y += yi;
					D += 2 * dx;
				}
				D += 2 * dy;
			}
		}
	}
	else if (abs(dy) > abs(dx)) {
		int xi = 1;
		if (dx < 0) {
			xi = -1;
			dx = -dx;
		}
		int D = 2 * dx - dy;
		int x = x0;
		int elementID = 0;
		if (dy > 0) {
			for (int y = y0; y <= y1; y++) {
				elementID = x + (this->xSize + 2) * y;
				this->densitySource.values[elementID] = 1;
				this->uSource.values[elementID] = (x1 - x0) / this->dt;
				this->vSource.values[elementID] = (y1 - y0) / this->dt;
				if (D > 0) {
					x += xi;
					D -= 2 * dy;
				}
				D += 2 * dx;
			}
		}
		else if (dy < 0) {
			D = 2 * dx + dy;
			for (int y = y0; y >= y1; y--) {
				elementID = x + (this->xSize + 2) * y;
				this->densitySource.values[elementID] = 1;
				this->uSource.values[elementID] = (x1 - x0) / this->dt;
				this->vSource.values[elementID] = (y1 - y0) / this->dt;
				if (D > 0) {
					x += xi;
					D += 2 * dy;
				}
				D += 2 * dx;
			}
		}
	}
}

void Fluid::diffuseVelocity() {
	for (int x = 1; x <= this->xSize; x++) {
		for (int y = 1; y <= this->ySize; y++) {
			this->u.values[x + y * (this->xSize + 2)] = this->u0.values[x + y * (this->xSize + 2)] + this->viscosity * 
				(0.25 * this->u.values[x - 1 + y * (this->xSize + 2)] + 0.25 * this->u.values[x + 1 + y * (this->xSize + 2)] +
				0.25 * this->u.values[x + (y - 1) * (this->xSize + 2)] + 0.25 * this->u.values[x + (y + 1) * (this->xSize + 2)] - 
					this->u0.values[x + y * (this->xSize + 2)]);
			this->v.values[x + y * (this->xSize + 2)] = this->v0.values[x + y * (this->xSize + 2)] + this->viscosity * 
				(0.25 * this->v.values[x - 1 + y * (this->xSize + 2)] + 0.25 * this->v.values[x + 1 + y * (this->xSize + 2)] +
				0.25 * this->v.values[x + (y - 1) * (this->xSize + 2)] + 0.25 * this->v.values[x + (y + 1) * (this->xSize + 2)] -
					this->v0.values[x + y * (this->xSize + 2)]);
		}
	}
	setBoundary(1, this->u);
	setBoundary(2, this->v);
}


void Fluid::advectVelocity() {
	for (int x = 1; x <= this->xSize; x++) {
		for (int y = 1; y <= this->ySize; y++) {
			double ax = 0;
			double ay = 0;
			int ax0 = 0;
			int ax1 = 0;
			int ay0 = 0;
			int ay1 = 0;
			double s0 = 0;
			double s1 = 0;
			double t0 = 0;
			double t1 = 0;
			float dt0 = dt * (this->xSize);

			ax = x - dt0 * this->u.values[x + this->xSize * y];
			ay = y - dt0 * this->v.values[x + this->xSize * y];
			if (ax < 0.5) {
				ax = 0.5;
			}
			if (ax > this->xSize + 0.5) {
				ax = this->xSize + 0.5;
			}
			ax0 = (int)ax;
			ax1 = ax0 + 1;
			if (ay < 0.5) {
				ay = 0.5;
			}
			if (ay > this->xSize + 0.5) {
				ay = this->xSize + 0.5;
			}
			ay0 = (int)ay;
			ay1 = ay0 + 1;
			s1 = ax - ax0;
			s0 = 1 - s1;
			t1 = ay - ay0;
			t0 = 1 - t1;
			this->u.values[x + (this->xSize + 2) * y] = s0 * (t0 * this->u0.values[ax0 + ay0 * (this->xSize + 2)] +
				t1 * this->u0.values[ax0 + ay1 * (this->xSize + 2)]) +
				s1 * (t0 * this->u0.values[ax1 + ay0 * (this->xSize + 2)] + t1 * this->u0.values[ax1 + ay1 * (this->xSize + 2)]);
			this->v.values[x + y * (this->xSize + 2)] = s0 * (t0 * this->v0.values[ax0 + ay0 * (this->xSize + 2)] + 
				t1 * this->v0.values[ax0 + ay1 * (this->xSize + 2)]) +
				s1 * (t0 * this->v0.values[ax1 + ay0 * (this->xSize + 2)] + t1 * this->v0.values[ax1 + ay1 * (this->xSize + 2)]);
		}
	}
	setBoundary(1, this->u);
	setBoundary(2, this->v);
}


void Fluid::projectVelocity() {
	float h = 1.0 / this->xSize;

	//project
	for (int i = 1; i <= this->xSize; i++) {
		for (int j = 1; j <= this->ySize; j++) {
			this->div.values[i + j * (this->xSize + 2)] = -0.5 * h * (this->u.values[i + 1 + j * (this->xSize + 2)] - 
				this->u.values[i - 1 + j * (this->xSize + 2)] + this->v.values[i + (j + 1) * (this->xSize + 2)] - 
				this->v.values[i + (j - 1) * (this->xSize + 2)]);
			this->p.values[i + j * (this->xSize + 2)] = 0;
		}
	}
	setBoundary(1, this->u);
	setBoundary(2, this->v);

	for (int k = 0; k < this->solverIterations; k++) {
		for (int i = 1; i <= this->xSize; i++) {
			for (int j = 1; j <= this->ySize; j++) {
				this->p.values[i + j * (this->xSize + 2)] = (this->div.values[i + j * (this->xSize + 2)] + 
					this->p.values[i - 1 + j * (this->xSize + 2)] + this->p.values[i + 1 + j * (this->xSize + 2)] +
					this->p.values[i + (j - 1) * (this->xSize + 2)] + this->p.values[i + (j + 1) * (this->xSize + 2)]) / 4;
			}
		}
	}
	setBoundary(0, this->density);

	for (int i = 1; i <= this->xSize; i++) {
		for (int j = 1; j <= this->ySize; j++) {
			this->u.values[i + j * (this->xSize + 2)] -= 0.5 * (this->p.values[i + 1 + j * (this->xSize + 2)] - 
				this->p.values[i - 1 + j * (this->xSize + 2)]) / h;
			this->v.values[i + j * (this->xSize + 2)] -= 0.5 * (this->p.values[i + (j + 1) * (this->xSize + 2)] - 
				this->p.values[i + (j - 1) * (this->xSize + 2)]) / h;
		}
	}
	setBoundary(1, this->u);
	setBoundary(2, this->v);
}


void Fluid::diffuseDensity() {
	for (int x = 1; x <= this->xSize; x++) {
		for (int y = 1; y <= this->ySize; y++) {
			this->density.values[x + y * (this->xSize + 2)] = this->density0.values[x + y * (this->xSize + 2)] + 
				this->diffusion * (0.25 * this->density.values[x - 1 + y * (this->xSize + 2)] + 0.25 * this->density.values[x + 1 + y * (this->xSize + 2)] +
				0.25 * this->density.values[x + (y - 1) * (this->xSize + 2)] + 0.25 * this->density.values[x + (y + 1) * (this->xSize + 2)] -
					this->density0.values[x + y * (this->xSize + 2)]);
		}
	}
	setBoundary(0, this->density);
}


void Fluid::advectDensity() {

	double ax = 0;
	double ay = 0;
	int ax0 = 0;
	int ax1 = 0;
	int ay0 = 0;
	int ay1 = 0;
	double s0 = 0;
	double s1 = 0;
	double t0 = 0;
	double t1 = 0;
	float dt0 = this->dt * (this->xSize);

	for (int x = 1; x <= this->xSize; x++) {
		for (int y = 1; y <= this->xSize; y++) {
			ax = x - dt0 * this->u.values[x + (this->xSize + 2) * y];
			ay = y - dt0 * this->v.values[x + (this->ySize + 2) * y];
			if (ax < 0.5) {
				ax = 0.5;
			}
			if (ax > (this->xSize + 2) - 1.5) {
				ax = (this->xSize + 2) - 1.5;
			}
			ax0 = (int)ax;
			ax1 = ax0 + 1;
			if (ay < 0.5) {
				ay = 0.5;
			}
			if (ay > (this->ySize + 2) - 1.5) {
				ay = (this->ySize + 2) - 1.5;
			}
			ay0 = (int)ay;
			ay1 = ay0 + 1;
			s1 = ax - ax0;
			s0 = 1 - s1;
			t1 = ay - ay0;
			t0 = 1 - t1;
			this->density.values[x + (this->xSize + 2) * y] = s0 * (t0 * this->density0.values[ax0 + (this->xSize + 2) * ay0] +
				t1 * this->density0.values[ax0 + (this->xSize + 2) * ay1]) +
				s1 * (t0 * this->density0.values[ax1 + (this->xSize + 2) * ay0] + t1 * this->density0.values[ax1 + (this->xSize + 2) * ay1]);
		}
	}
	setBoundary(0, this->density);
}

void Fluid::setBoundary(int d, Field f)
{
	for (int i = 1; i <= this->xSize; i++) {
		f.values[0 + (this->xSize + 2) * i] = (d == 1 ? -f.values[1 + (this->xSize + 2) * i] : f.values[1 + (this->xSize + 2) * i]);
		f.values[(this->xSize + 1) + (this->xSize + 2) * i] = (d == 1 ? -f.values[this->xSize + (this->xSize + 2) * i] : f.values[this->xSize + (this->xSize + 2) * i]);
		f.values[i + (this->xSize + 2) * 0] = (d == 2 ? -f.values[i + (this->xSize + 2) * 1] : f.values[i + (this->xSize + 2) * 1]);
		f.values[i + (this->xSize + 2) * (this->xSize + 1)] = (d == 2 ? -f.values[i + (this->xSize + 2) * (this->xSize)] : f.values[i + (this->xSize + 2) * (this->xSize)]);
		/*v.values[0 + (xSize + 2)*i] = 0;
		v.values[(xSize+1) + (xSize + 2)*i] = 0;
		v.values[i + (xSize + 2) * 0] = 0;
		v.values[i + (xSize + 2) * (xSize + 1)] = 0;
		u.values[0 + (xSize + 2)*i] = 0;
		u.values[(xSize+1) + (xSize + 2)*i] = 0;
		u.values[i + (xSize + 2) * 0] = 0;
		u.values[i + (xSize + 2) * (xSize + 1)] = 0;*/
	}
	f.values[0 + (this->xSize + 2) * 0] = 0.5 * (f.values[1 + (this->xSize + 2) * 0] + f.values[0 + (this->xSize + 2) * 1]);
	f.values[0 + (this->xSize + 2) * (this->xSize + 1)] = 0.5 * (f.values[1 + (this->xSize + 2) * (this->xSize + 1)] + f.values[0 + (this->xSize + 2) * (this->xSize)]);
	f.values[this->xSize + 1 + 0] = 0.5 * (f.values[this->xSize + 0] + f.values[this->xSize + 1 + 1]);
	f.values[this->xSize + 1 + (this->xSize + 2) * (this->xSize + 1)] = 0.5 * (f.values[this->xSize + (this->xSize + 2) * (this->xSize + 1)] + f.values[this->xSize + 1 + (this->xSize + 2) * (this->xSize)]);

}

void Fluid::swapPointers(float*& x0, float*& x1) {
	float* memory = x0;
	x0 = x1;
	x1 = memory;
}

Fluid::~Fluid() {}