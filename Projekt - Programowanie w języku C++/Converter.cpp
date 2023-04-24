#include "Converter.h"


Converter::Element* Converter::Horizontal_elements(Element* target, int base_x, int base_y, int base_z, int crossbars, int shelf_amount, int drawer_number,  int horizontal_elements_amount)
{
	float thickness = 18;
	float crossbar_z = 100; // crossbar z size
	int s = 0;
	int x = 0;
	int d = 0;

	target[0].x = base_x;
	target[0].y = thickness; // bottom part (essential in every wardrobe)
	target[0].z = base_z;
	Elements_vector.push_back(target[0]);
	for (int i = 1; i <= horizontal_elements_amount; i++)
	{	

		if (crossbars > 1 && s < crossbars)
		{
			target[i].x = base_x;
			target[i].y = thickness;
			target[i].z = crossbar_z;
			s++;
			Elements_vector.push_back(target[i]);
			i++;
			
		}
		if (shelf_amount > 0 && x < shelf_amount)
		{
			target[i].x = base_x - 36 ;
			target[i].y = thickness;
			target[i].z = base_z - 10;
			x++;
			Elements_vector.push_back(target[i]);
			i++;
		}
		if (crossbars == 0) // wardrobe below z < 350 should have only one crossbar with size similar to shelf
		{
			target[i].x = base_x - 36;
			target[i].y = thickness;
			target[i].z = base_z;
			Elements_vector.push_back(target[i]);
			i++;
		}
		if (drawer_number > 0 && d <= drawer_number)
		{
			target[i].x = base_x - 101;
			target[i].y = thickness;
			target[i].z = base_z; // [to change] (depth of the drawer)
			Elements_vector.push_back(target[i]);
			i++;
		}
		
	}
	
	return target;
}

Converter::Element* Converter::Vertical_elements(Element* target, int base_x, int base_y, int base_z, int drawer_number, int vertical_elements_amount)
{
	float thickness = 18;
	int d = 0;
	int size = Elements_vector.size();

	target[0].x = thickness;
	target[0].y = base_y;
	target[0].z = base_z;
	Elements_vector.push_back(target[0]);

	target[0].x = thickness;
	target[0].y = base_y; 
	target[0].z = base_z;
	Elements_vector.push_back(target[0]);

	for (int i = 0; i < vertical_elements_amount; i++)
	{
		if (drawer_number > 0 && d <= drawer_number)
		{
			target[size].x = thickness;
			target[size].y = base_y;
			target[size].z = base_z; // [to change] (depth of the drawer)
			Elements_vector.push_back(target[i]);
			size++;
		}


		//if (d == drawer_number && i < vertical_elements_amount)
		//{
		//	target[size].x = base_x - 123;
		//	target[size].y = 199; // [to change] (height of the drawer)
		//	target[size].z = thickness;
		//	Elements_vector.push_back(target[i]);
		//	size++;
		//}
		
		return target;
	}
	
}

void Converter::Calculate(float x, float y, float z, int shelf_amount, int drawer_number)
{
		int crossbars = 2; // default amount of crossbars
		
		if (z < 350) // wardrobe below z < 350 should have only one crossbar with size similar to shelf
		{
			crossbars = 0;
		}
		
		int horizontal_elements = crossbars + 1 + shelf_amount + drawer_number; //  calculates amount of horizontal objects || [crossbars / bottom-element / shelfs / drawers]

		if (z < 350) // wardrobe below z < 350 should have only one crossbar with size similar to shelf
		{
	
			horizontal_elements++;
		}
		int vertical_elements = 2 + drawer_number; //  calculates amount of vertical objects
		int total_elements = horizontal_elements + vertical_elements; // sum of vertical and horizontal objects (depth elements not yet generated)
		Element* Elements = new Element[total_elements + 1];
		Horizontal_elements(Elements, x, y, z, crossbars, shelf_amount, drawer_number, horizontal_elements);
		Vertical_elements(Elements, x, y, z, drawer_number, vertical_elements);
	
}


Converter::~Converter()
{
}
