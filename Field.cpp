#include "Field.h"
#include <vector>

Field::Field() {
	this->x = 200;
	this->y = 200;
	this->xy = (this->x + 2) * (this->y + 2);
	for (int i = 0; i < this->xy; i++) {
		this->values.push_back(0);
	}
}

void Field::set(int xSize, int ySize) {
	this->x = xSize;
	this->y = ySize;
	this->xy = (this->x + 2) * (this->y + 2);
	for (int i = 0; i < this->xy; i++) {
		this->values.push_back(0);
	}
}

Field::~Field(){}