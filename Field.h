class Field {
private:
	int x, y, xy; //field dimentions
	float* values; //containing the field parameters
public:
	Field();
	void set(int xSize, int ySize);
	~Field();

	friend class Fluid;
};
