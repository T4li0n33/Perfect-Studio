#pragma once
#include <vector>
class Converter
{

public:
	struct Element
	{
		int x;
		int y;
		int z;
	};
	std::vector<Element> Elements_vector;
	Converter::Element* Horizontal_elements(Element* target, int base_x, int base_y, int base_z, int crossbars, int shelf_amount, int drawer_number, int horizontal_elements_amount); //Calculates size of vertical elements, adds it to elements table
	Converter::Element* Vertical_elements(Element* target, int base_x, int base_y, int base_z, int crossbars, int vertical_elements_amount);  //Calculates size of horizontal elements, adds it to elements table
	void Calculate(float x, float y, float z, int shelf_amount, int drawer_number);
	~Converter();
};

