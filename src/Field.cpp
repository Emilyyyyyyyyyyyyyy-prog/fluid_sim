#include "Field.h"


Field::Field() {}

void Field::set(int xSize, int ySize) {
	this->x = xSize;
	this->y = ySize;
	this->xy = (this->x + 2) * (this->y + 2);
	this->values = new float[(xSize + 2) * (ySize + 2)];
	for (int i = 0; i < this->xy; i++) {
		this->values[i] = 0;
	}
}

Field::~Field(){}
