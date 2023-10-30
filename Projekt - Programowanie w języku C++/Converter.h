#pragma once
#include <vector>
#include <string>
#include "Wardrobe.h"

class Converter
{
private: 

	float previous_x = 0;
	float previous_y = 0;
	float previous_z = 0;
	int previous_shelf = 0;
	int previous_drawer = 0;

public:
	struct Element
	{
		float x = 0;
		float y = 0;
		float z = 0;
		int Elem_ID = 0;
		std::vector<char> veneer;
		const char* elem_type = "A"; // B - Bottom, S - Side, C - Crossbars, E - Drawer back, F - Drawer bottom, G - Shelf
		bool alreadydrawn = false;
	};

	int Elem_Num = 0;
	std::vector<Element> Elements_vector;

	//[Static Methods]
	void Calculate(Wardrobe wardrobe); // Static method that is filling up Elements vector with structures
	int TotalElements(float z, int shelf_amount, int drawer_number);

	//[Calc Functions] - used to append elements to an "Elements_vector"
	void Crossbars(float z, float x, Element*target);
	void Shelfs(float x, float z, int shelf_amount, Element* target);
	void Bottom(float x, float z, Element* target);
	void Sides(float y, float z, Element* target);
	void Drawers(float x, float y, float z, int drawer_number, Element* target);

	//[Validatino and Optimalization]

	bool Checkchanges(Wardrobe wardrobe);
	
	//[Updating element status]

	void AlreadyDrawn(int elem_vector_id);

	~Converter();
};

