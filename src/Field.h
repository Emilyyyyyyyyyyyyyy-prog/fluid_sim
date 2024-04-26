class Field {
private:
	int x, y, xy;  //field dimensions
	float* values;  //array containing the field parameters
public:
	Field();
	void set(int xSize, int ySize);  //set size and values
	~Field();

	friend class Fluid;
};
