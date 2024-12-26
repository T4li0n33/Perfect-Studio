#pragma once
#include <vector>
#include <string>
#include "Wardrobe.h"
#include <string>
using namespace std;

class Converter
{
private: 

	float previous_x = 0;
	float previous_y = 0;
	float previous_z = 0;
	int previous_shelf = 0;
	int previous_drawer = 0;
	int previous_front = 0;
	int previous_drawer_color = 0;
	bool first_front_bool = true;

public:
	struct Element
	{
		float x = 0;
		float y = 0;
		float z = 0;
		int Elem_ID = 0;
		std::vector<std::string> veneer;
		const char* elem_type = "A"; // B - Bottom, S - Side, C - Crossbars, E - Drawer back, F - Drawer bottom, G - Shelf, L - Front
		bool alreadydrawn = false;
	};

	int Elem_Num = 0;
	std::vector<Element> Elements_vector;

	//[Static Methods]
	// 
	// 
	//Static method that is filling up Elements vector with structures
	void Calculate(Wardrobe wardrobe); 

	//Method to calculete total amount of elements to draw
	int TotalElements(float z, int shelf_amount, int drawer_number, int front_number);

	//[Calc Functions] - used to append elements to an "Elements_vector"
	
	void Crossbars(float z, float x, Element*target, string veneer);

	void Shelfs(float x, float z, int shelf_amount, Element* target, string veneer);

	void Bottom(float x, float z, Element* target, string veneer);

	void Sides(float y, float z, Element* target, string veneer);

	void Drawers(float x, float y, float z, int drawer_number, Element* target, Wardrobe wardrobe, string veneer);

	void Fronts(float x, float y, float z, Element* target, Wardrobe wardrobe, string veneer);

	//[Validatino and Optimalization]

	bool Checkchanges(Wardrobe wardrobe);
	
	//[Updating element status]

	void AlreadyDrawn(int elem_vector_id);

	//[Used assets methods] - Calculates elements sizes based on manufacturer definitions

	float BlumDrawerHeight(float drawer_height);
	float BlumDrawerDepth(float drawer_depth);

	//[Helping functions]

	void ApplyElementVeneer(char element_id, Element* target, string veneer);
	float FrontHeight(Wardrobe wardrobe, int i);
	float DrawerHeight(Wardrobe wardrobe);
	float FrontWidth(Wardrobe wardrobe);

	//Delete object
	~Converter();
};

