#include "Converter.h"


void Converter::Calculate(Wardrobe wardrobe)
{

	Elements_vector.clear();
	Elements_vector.shrink_to_fit(); //Clear and shrink vector to prevent allocation errors
		previous_x = wardrobe.GetBaseSettings(1);
		previous_y = wardrobe.GetBaseSettings(2); //Update base x,y,z values
		previous_z = wardrobe.GetBaseSettings(3);
		previous_drawer = wardrobe.GetAmount(1);
		previous_shelf = wardrobe.GetAmount(2); // Update amount of shelfs and drawers
		
		Elem_Num = 0;
		Element* Elements = new Element[TotalElements(wardrobe.GetBaseSettings(3), wardrobe.GetAmount(2), wardrobe.GetAmount(1)) + 1];
		Bottom(wardrobe.GetBaseSettings(1), wardrobe.GetBaseSettings(3), Elements);
		Crossbars(wardrobe.GetBaseSettings(3), wardrobe.GetBaseSettings(1), Elements);
		Shelfs(wardrobe.GetBaseSettings(1), wardrobe.GetBaseSettings(3), wardrobe.GetAmount(2), Elements);
		Drawers(wardrobe.GetBaseSettings(1), wardrobe.GetBaseSettings(2), wardrobe.GetBaseSettings(3), wardrobe.GetAmount(1), Elements);
		Sides(wardrobe.GetBaseSettings(2), wardrobe.GetBaseSettings(3), Elements); // Calculates all needed elements and adds them to Elements_vector
		delete []Elements;
		return;
		
}

int Converter::TotalElements(float z, int shelf_amount, int drawer_number)
{

	int crossbars = 2; // default amount of crossbars

	if (z < 350) // wardrobe below z < 350 should have only one crossbar with size similar to shelf
	{
		crossbars = 1;
	
	}

	int horizontal_elements = crossbars + 1 + shelf_amount + drawer_number; //  calculates amount of horizontal objects || [crossbars / bottom-element / shelfs / drawers]
	int vertical_elements = 2 + drawer_number; //  calculates amount of vertical objects
	int total_elements = horizontal_elements + vertical_elements; // sum of vertical and horizontal objects (depth elements not yet generated)

	return total_elements;
}

void Converter::Crossbars(float z, float x, Element* target)
{
	float thickness = 18;
	float crossbar_z = 100; // crossbar z size

	if (z < 350)
	{
		target[Elem_Num].x = x - 36;
		target[Elem_Num].y = thickness;
		target[Elem_Num].z = z;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "C";
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;
		return;
	}

		target[Elem_Num].x = x - 36;
		target[Elem_Num].y = thickness;
		target[Elem_Num].z = 100;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "C";
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;

		target[Elem_Num].x = x - 36;
		target[Elem_Num].y = thickness;
		target[Elem_Num].z = 100;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "C";
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;
		return;
}

void Converter::Shelfs(float x, float z, int shelf_amount, Element* target)
{
	float thickness = 18;
	for (int i = 0; i < shelf_amount; i++)
	{
		target[Elem_Num].x = x - 36;
		target[Elem_Num].y = thickness;
		target[Elem_Num].z = z - 10;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "G";
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;
	}
	return;
}

void Converter::Bottom(float x, float z, Element* target)
{
	float thickness = 18;
	target[Elem_Num].x = x;
	target[Elem_Num].y = thickness;
	target[Elem_Num].z = z;
	target[Elem_Num].Elem_ID = Elem_Num;
	target[Elem_Num].elem_type = "B";
	Elements_vector.push_back(target[Elem_Num]);
	Elem_Num++;
	return;
}

void Converter::Sides(float y, float z, Element* target)
{	
	float thickness = 18;

	target[Elem_Num].x = thickness;
	target[Elem_Num].y = y;
	target[Elem_Num].z = z;
	target[Elem_Num].Elem_ID = Elem_Num;
	target[Elem_Num].elem_type = "S";
	Elements_vector.push_back(target[Elem_Num]);
	Elem_Num++;

	target[Elem_Num].x = thickness;
	target[Elem_Num].y = y;
	target[Elem_Num].z = z;
	target[Elem_Num].Elem_ID = Elem_Num;
	target[Elem_Num].elem_type = "S";
	Elements_vector.push_back(target[Elem_Num]);
	Elem_Num++;

	return;
}

void Converter::Drawers(float x, float y, float z, int drawer_number, Element* target)
{
		float thickness = 18.00f;
		int i = 0;
		if (drawer_number == 3)
		{
			target[Elem_Num].x = thickness;
			target[Elem_Num].y = y;
			target[Elem_Num].z = z; // [to change] (depth of the drawer)
			target[Elem_Num].Elem_ID = Elem_Num;
			target[Elem_Num].elem_type = "E";
			Elements_vector.push_back(target[Elem_Num]);
			Elem_Num++;

			target[Elem_Num].x = x - 101;
			target[Elem_Num].y = thickness;
			target[Elem_Num].z = z; // [to change] (depth of the drawer)
			target[Elem_Num].elem_type = "F";
			target[Elem_Num].Elem_ID = Elem_Num;
			Elements_vector.push_back(target[Elem_Num]);
			Elem_Num++;
			i = 1;
		}
	
		for (;i < drawer_number; i++)
		{
			target[Elem_Num].x = x - 123;
			target[Elem_Num].y = 199; // [to change] (height of the drawer)
			target[Elem_Num].z = thickness;
			target[Elem_Num].Elem_ID = Elem_Num;
			target[Elem_Num].elem_type = "E";
			Elements_vector.push_back(target[Elem_Num]);
		
			Elem_Num++;

			target[Elem_Num].x = x - 101;
			target[Elem_Num].y = thickness;
			target[Elem_Num].z = z; // [to change] (depth of the drawer)
			target[Elem_Num].elem_type = "F";
			target[Elem_Num].Elem_ID = Elem_Num;
			Elements_vector.push_back(target[Elem_Num]);
			Elem_Num++;
		}


		return;
}


bool Converter::Checkchanges(Wardrobe wardrobe)
{
	if (wardrobe.GetBaseSettings(1) != previous_x || wardrobe.GetBaseSettings(2) != previous_y || wardrobe.GetBaseSettings(3) != previous_z ||
		wardrobe.GetAmount(2) != previous_shelf || wardrobe.GetAmount(1) != previous_drawer)
	{
		return true;
	}
	return false;
}

void Converter::AlreadyDrawn(int elem_vector_id)
{
	this->Elements_vector[elem_vector_id].alreadydrawn= true;
}

Converter::~Converter()
{
}
