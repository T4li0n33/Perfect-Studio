#include "Converter.h"


void Converter::Calculate(Wardrobe wardrobe)
{

		//Clear and shrink vector to prevent allocation errors
		Elements_vector.clear();
		Elements_vector.shrink_to_fit();

		//Updateing previous base x,y,z,amount,color values (Used to monitor a change of inputs)
		previous_x = wardrobe.GetBaseSettings(1);
		previous_y = wardrobe.GetBaseSettings(2); 
		previous_z = wardrobe.GetBaseSettings(3);
		previous_drawer_color = wardrobe.GetDrawerColor();
		previous_drawer = wardrobe.GetAmount(1);
		previous_shelf = wardrobe.GetAmount(2);
		previous_front = wardrobe.GetAmount(3);

		//Assigning new base values
		float x = wardrobe.GetBaseSettings('x');
		float y = wardrobe.GetBaseSettings('y');
		float z = wardrobe.GetBaseSettings('z');

		// Update amount of shelfs, drawers, fronts and wardrobe type
		int drawer_amount = wardrobe.GetAmount(1);
		int shelf_amount = wardrobe.GetAmount(2);
		int front_amount = wardrobe.GetAmount(3);
		SaveWardrobeType(wardrobe);

		//Assign veener and textures
		string veneer = wardrobe.GetVeener();
		string drawer_veneer = wardrobe.GetDrawerColor(wardrobe.GetDrawerColor());
		
		//Reset of Element Index Assigner
		Elem_Num = 0;
		bool IsWardrobeModelCorner = (wardrobe.GetWardrobeModel(4) == true);
		//Computing the total amount of elements
		Element* Elements = new Element[TotalElements(z, shelf_amount, drawer_amount, front_amount, IsWardrobeModelCorner) + 1 + 3];

		//Convert inputs to element attribiutes and adds them to Elements_vector
		Bottom(x, z, Elements, veneer);
		Crossbars(z, x, Elements, veneer);
		Shelfs(x, z, shelf_amount, Elements, veneer);
		Drawers(x, y, z, drawer_amount, Elements, wardrobe, drawer_veneer);
		Sides(y, z, Elements, veneer);
		if(wardrobe.GetWardrobeModel(4))BlindSide(wardrobe.GetBlindSideSize(), y, Elements, veneer);
		Fronts(x, y, z, Elements, wardrobe, veneer);

		//Delete allocated buffer
		delete []Elements;
		return;
		
}

int Converter::TotalElements(float z, int shelf_amount, int drawer_number, int front_number, bool IsWardrobeModelCorner)
{
	int blindSide = 0;

	if (IsWardrobeModelCorner)
	{
		blindSide = 1;
	}

	int crossbars = 2; // default amount of crossbars

	if (z < 350) // wardrobe below z < 350 should have only one crossbar with size similar to shelf
	{
		crossbars = 1;
	
	}

	//Calculates amount of horizontal objects || [crossbars / bottom-element / shelfs / drawers]
	int horizontal_elements = crossbars + 1 + shelf_amount + drawer_number; 
	int vertical_elements = 2 + drawer_number; //  calculates amount of vertical objects
	int total_elements = horizontal_elements + vertical_elements + front_number + blindSide; // sum of vertical and horizontal objects (depth elements not yet generated)

	return total_elements;
}


void Converter::Crossbars(float z, float x, Element* target, string veneer)
{
	float thickness = 18;
	float crossbar_z = 100; // crossbar z size

	if (z < 350 || GetWardrobeType() == 2) // If size of top is smaller than 350 or it's a cabinet
	{
		//Assigning values and ID
		target[Elem_Num].x = x - 36;
		target[Elem_Num].y = thickness;
		target[Elem_Num].z = z;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "C";

		//Assigning vaneering
		ApplyElementVeneer('C', target, veneer);

		//Pushing element to the vector
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;
		return;
	}

	for (int w = 0; w < 2; w++)
	{
		//Assigning values and ID
		target[Elem_Num].x = x - 36;
		target[Elem_Num].y = thickness;
		target[Elem_Num].z = 100;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "C";

		//Assigning vaneering
		ApplyElementVeneer('C', target, veneer);

		//Pushing element to the vector
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;
		

	}
	return;
}

void Converter::Shelfs(float x, float z, int shelf_amount, Element* target, string veneer)
{
	float thickness = 18;
	for (int i = 0; i < shelf_amount; i++)
	{
		//Assigning values and ID
		target[Elem_Num].x = x - 36;
		target[Elem_Num].y = thickness;
		target[Elem_Num].z = z - 10;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "G";

		//Assigning vaneering
		ApplyElementVeneer('G', target, veneer);
	
		//Pushing element to the vector
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;
	}
	return;
}

void Converter::Bottom(float x, float z, Element* target, string veneer)
{
	//Assigning values and ID
	float thickness = 18;
	target[Elem_Num].x = x;
	if(GetWardrobeType() == 2) target[Elem_Num].x = x - 36;
	target[Elem_Num].y = thickness;
	target[Elem_Num].z = z;
	target[Elem_Num].Elem_ID = Elem_Num;
	target[Elem_Num].elem_type = "B";

	//Assigning vaneering
	//target[Elem_Num].veneer.push_back(veneer); //x1 coord veneer
	//target[Elem_Num].veneer.push_back(""); //x2
	//target[Elem_Num].veneer.push_back(""); //y1 coord veneer
	//target[Elem_Num].veneer.push_back(""); //y2
	ApplyElementVeneer('B', target, veneer);

	//Pushing element to the vector
	Elements_vector.push_back(target[Elem_Num]);
	Elem_Num++;
	return;

	
}

void Converter::Sides(float y, float z, Element* target, string veneer)
{	
	float thickness = 18;

	for (int w = 0; w < 2; w++)
	{
		//Assigning values and ID
		target[Elem_Num].x = thickness;
		target[Elem_Num].y = y - 18.0f;
		if (GetWardrobeType() == 2) target[Elem_Num].y = y; // In cabinets side's height is based on input
		target[Elem_Num].z = z;
		target[Elem_Num].Elem_ID = Elem_Num;
		target[Elem_Num].elem_type = "S";

		//Assigning vaneering
		ApplyElementVeneer('S', target, veneer);

		//Pushing element to the vector
		Elements_vector.push_back(target[Elem_Num]);
		Elem_Num++;
	}

	return;
}

void Converter::BlindSide(float blindSideSize, float y, Element* target, string veneer)
{
	float thickness = 18;
	target[Elem_Num].x = blindSideSize;
	target[Elem_Num].y = y;
	target[Elem_Num].z = thickness;
	target[Elem_Num].Elem_ID = Elem_Num;
	target[Elem_Num].elem_type = "K";

	ApplyElementVeneer('K', target, veneer);

	Elements_vector.push_back(target[Elem_Num]);
	Elem_Num++;
}

void Converter::Drawers(float x, float y, float z, int drawer_number, Element* target, Wardrobe wardrobe, string veneer)
{
		float thickness = 16.00f;
		int i = 0;
	
		if (drawer_number == 3) i = 1;
		for (;i < drawer_number; i++)
		{
			//Assigning values and ID
			target[Elem_Num].x = x - 123;
			target[Elem_Num].y = BlumDrawerHeight(DrawerHeight(wardrobe) - 18.0f); // (height of the drawer)
			target[Elem_Num].z = thickness;
			target[Elem_Num].Elem_ID = Elem_Num;
			target[Elem_Num].elem_type = "E";

			//Assigning vaneering
			ApplyElementVeneer('E', target, veneer);

			//Pushing element to the vector
			Elements_vector.push_back(target[Elem_Num]);
		
			Elem_Num++;

			//Assigning values and ID
			target[Elem_Num].x = x - 101;
			target[Elem_Num].y = thickness;
			target[Elem_Num].z = 500 - 24; // [to change] (depth of the drawer)
			target[Elem_Num].elem_type = "F";
			target[Elem_Num].Elem_ID = Elem_Num;

			//Pushing element to the vector
			Elements_vector.push_back(target[Elem_Num]);

			Elem_Num++;

		}
		if (drawer_number == 3)
		{
			//Assigning values and ID
			target[Elem_Num].x = x - 123;
			target[Elem_Num].y = BlumDrawerHeight(130); // Depends on drawer model
			target[Elem_Num].z = thickness; // [to change] (depth of the drawer)
			target[Elem_Num].Elem_ID = Elem_Num;
			target[Elem_Num].elem_type = "E";

			//Assigning vaneering
			ApplyElementVeneer('E', target, veneer);

			//Pushing element to the vector
			Elements_vector.push_back(target[Elem_Num]);
			Elem_Num++;

			//Assigning values and ID
			target[Elem_Num].x = x - 101;
			target[Elem_Num].y = thickness;
			target[Elem_Num].z = 500 - 24; // [to change] (depth of the drawer)
			target[Elem_Num].elem_type = "F";
			target[Elem_Num].Elem_ID = Elem_Num;

			//Pushing element to the vector
			Elements_vector.push_back(target[Elem_Num]);
			Elem_Num++;
		}

		return;
}

void Converter::Fronts(float x, float y, float z, Element* target, Wardrobe wardrobe, string veneer)
{
	float thickness = 18.00f;

	if (wardrobe.GetWardrobeModel(2) || wardrobe.GetWardrobeModel(3)) // Drawers and cargo
	{
		for (int i = 0; i < wardrobe.GetAmount(3); i++)
		{
			//Assigning values and ID
			target[Elem_Num].x = x - 6.00f; // In drawers 6mm are substracted
			target[Elem_Num].y = FrontHeight(wardrobe, i);
			target[Elem_Num].z = thickness;
			target[Elem_Num].elem_type = "L";
			target[Elem_Num].Elem_ID = Elem_Num;

			//Assigning vaneering
			ApplyElementVeneer('L', target, veneer);

			//Pushing element to the vector
			Elements_vector.push_back(target[Elem_Num]);
			Elem_Num++;
		}
		return;
	}
	
	if (wardrobe.GetWardrobeModel(1) || wardrobe.GetWardrobeModel(4)) // Shelfs and corner
	{
		for (int i = 0; i < wardrobe.GetAmount(3); i++)
		{
			//Assigning values and ID
			target[Elem_Num].x = FrontWidth(wardrobe);
			target[Elem_Num].y = FrontHeight(wardrobe, i);
			target[Elem_Num].z = thickness;
			target[Elem_Num].elem_type = "L";
			target[Elem_Num].Elem_ID = Elem_Num;

			//Assigning vaneering
			ApplyElementVeneer('L', target, veneer);

			//Pushing element to the vector
			Elements_vector.push_back(target[Elem_Num]);
			Elem_Num++;
		}
		return;
	}
}


bool Converter::Checkchanges(Wardrobe wardrobe)
{
	if (wardrobe.GetBaseSettings(1) != previous_x || wardrobe.GetBaseSettings(2) != previous_y || wardrobe.GetBaseSettings(3) != previous_z ||
		wardrobe.GetAmount(2) != previous_shelf || wardrobe.GetAmount(1) != previous_drawer || wardrobe.GetDrawerColor() != previous_drawer_color || wardrobe.GetAmount(3) != previous_front) 
	{
		return true;
	}
	return false;
}

void Converter::AlreadyDrawn(int elem_vector_id)
{
	this->Elements_vector[elem_vector_id].alreadydrawn= true;
}

float Converter::BlumDrawerHeight(float drawer_height)
{
	if (drawer_height < 80) return -1; //Throw an error
	if (drawer_height >= 80 && drawer_height < 98.4) return 69.00f; // Type "N"
	if (drawer_height >= 98.5 && drawer_height < 130.4) return 84.00f; // Type "M"
	if (drawer_height >= 130.5 && drawer_height < 195.9) return 116.00f; // Type "K"
	if (drawer_height >= 196 && drawer_height < 227.9) return 167.00f; // Type "C"
	if (drawer_height >= 228) return 199.00f; // Type "D"

}

float Converter::BlumDrawerDepth(float drawer_depth)
{
	return 0.0f;
}

void Converter::ApplyElementVeneer(char element_id, Element* target, string veneer)
{
	int value = static_cast<int>(element_id);
	switch (value)
	{

		case 66: //Bottom (ID : B)
		{
			target[Elem_Num].veneer.push_back(veneer); //x1 coord veneer
			target[Elem_Num].veneer.push_back(""); //x2
			target[Elem_Num].veneer.push_back(""); //y1 coord veneer
			target[Elem_Num].veneer.push_back(""); //y2
			break;
		}
		case 67 : //Crossbar (ID : C)
		{
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back(""); //x2
			target[Elem_Num].veneer.push_back(""); //x2
			break;
		}

		case 69 : //Drawer back (ID : E)
		{
			target[Elem_Num].veneer.push_back("");
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back("");
			target[Elem_Num].veneer.push_back("");
			break;
		}
		
		case 71 : //Shelf (ID : G)
		{
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back("");
			target[Elem_Num].veneer.push_back("");
			target[Elem_Num].veneer.push_back("");
			break;
		}
		case 76 : //Front (ID : L)
		{
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back(veneer);
			break;
		}

		case 83: //Side (ID :S)
		{
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back("");
			target[Elem_Num].veneer.push_back("");
			target[Elem_Num].veneer.push_back("");
			break;
		}

		case 75:
		{
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back("");
			target[Elem_Num].veneer.push_back(veneer);
			target[Elem_Num].veneer.push_back(veneer);
			break;
		}

		default : 
		{
		std:_Xruntime_error("Element type not recognized");
		}

	}

}

float Converter::FrontHeight(Wardrobe wardrobe, int i)
{
	int size = Elements_vector.size();
	float* ratio_table = wardrobe.drawer_ratio;
	int amount = wardrobe.GetAmount(3);
	float divider = amount;

	

	if (wardrobe.GetWardrobeModel(1) || wardrobe.GetWardrobeModel(4))
	{
		return (wardrobe.GetBaseSettings(2) - 5.00f);
	}

	else
	{

		if (i == 2 && wardrobe.GetAutoRatio(3) && amount == 3) //If auto-ratio is set, there's three drawers and asking for height of third
		{
			return 143.00f;
		}

		if(wardrobe.GetAutoRatio(3) && amount == 3)
		return (wardrobe.GetBaseSettings(2)  + 143.00f - 5.00f - 3.0f * (amount - 1)) / divider; //If auto-ratio is set and there's three drawers
		
		return (wardrobe.GetBaseSettings(2) - 5.00f - 3.0f * (amount - 1)) / divider;
		
	}
}

float Converter::DrawerHeight(Wardrobe wardrobe)
{
	int size = Elements_vector.size();

	if (wardrobe.GetWardrobeModel(1) || wardrobe.GetWardrobeModel(4))
	{
		return (wardrobe.GetBaseSettings(2) - 5.00f);
	}

	else
	{

		int amount = wardrobe.GetAmount(3);
		float first_front = 0.0f;
		float divider = amount;
		if (amount == 3 && wardrobe.GetAutoRatio(3)) {
			first_front = 143; divider = 2;
		}

		float front_height = (wardrobe.GetBaseSettings(2) - first_front - 5.00 - 3 * (amount - 1)) / divider;


		return front_height;
	}
}

float Converter::FrontWidth(Wardrobe wardrobe)
{
	float width = 0.00f;
	if (wardrobe.GetWardrobeModel(2) || wardrobe.GetWardrobeModel(3))
	{
		return (wardrobe.GetBaseSettings(2) - 4.00f);
	}


	if (wardrobe.GetWardrobeModel(4))
	{
		width = wardrobe.GetBaseSettings(1) - wardrobe.GetDiaphragmSize() - 6.00f - wardrobe.GetBlindSideSize();
		return width;
	}

	if(wardrobe.GetWardrobeModel(1))
	{
		int amount = wardrobe.GetAmount(3);
		float front_width = (wardrobe.GetBaseSettings(1) - 4.00f - 3.00f * (amount - 1)) / amount;
		return front_width;
	}
}

void Converter::SaveWardrobeType(Wardrobe wardrobe)
{
	for (int i = 1; i <= 3; ++i)
	{
		if (wardrobe.GetWardrobeType(i))
		{
			this->wardrobe_type = i;
			return;
		}
	}
}

int Converter::GetWardrobeType()
{
	return wardrobe_type;
}

Converter::~Converter()
{
}
