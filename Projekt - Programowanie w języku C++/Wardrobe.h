#pragma once
class Wardrobe
{
	bool wardrobe_type_bottom = false;//
	bool wardrobe_type_top = false;//
	bool wardrobe_type_unusual = false;//
	bool wardrobe_model_shelf = false;//
	bool wardrobe_model_drawer = false;//
	bool wardrobe_model_corner = false;//
	bool wardrobe_model_cargo = false;//
	bool auto_shelf_ratio = true;//
	bool auto_drawer_ratio = true;//
	bool wardrobe_corner_lemans = false; //
	bool wardrobe_corner_shelf = false; //
	bool wardrobe_type_choosed = false; // 
	bool wardrobe_model_choosed = false; //
	bool wardrobe_size_placed = false; //
	float base_x = 0, base_y = 0, base_z = 0;
	int shelf_number = 0;
	int drawer_number = 0;
	int wardrobe_index = 0;
	
public:
	float previous_s_ratio[4] = { 0,0,0,0 };
	float previous_d_ratio[4] = { 0,0,0,0 };
	float drawer_ratio[4]{ 0,0,0,0 };
	float shelf_ratio[4]{ 0,0,0,0 };
	//[Geters]
	
	// Returns boolean based od i-value /1=bottom/2=top/3=unusual
	bool GetWardrobeType(int i);

	// Returns boolean based od i-value /1=corner_lemans/2=corner_shelf/
	bool GetWardrobeTypeCorner(int i);

	// Returns boolean based od i-value /1=model_shelf/2=model_drawer/3=model_cargo/4=model_corner/
	bool GetWardrobeModel(int i);

	//Returns boolean based on i-value where /1=shelf_ratio/2=drawer_ratio
	bool GetAutoRatio(int i);


	//Returns pointer to table with saved ratio (also checks both tables for emptiness)
	float GetShelfRatio();

	float GetDrawerRatio();

	//Returns amount of drawers - 1/shelfs - 2
	int GetAmount(int i);

	//Checks if all needed inputs are placed
	bool AreOptionsPicked();

	//Returns value of x,y,z where /1 - x/ 2 - y / 3 - z/
	float GetBaseSettings(int i);

	//[Seters]

	//Sets input value for x,y,z where /1 - x/ 2 - y / 3 - z/
	void SetSize(int i, float value);

	//Sets type // 1 - bottom / 2 - top / 3 - unusual / 4 - model_choosed / 5 - size_placed
	void SetWardrobeType(int i);

	//Sets boolean type of corner wardrobe / 1 - lemans / 2 - shelf
	void SetWardrobeTypeCorner(int i);

	//Sets model // 1 - shelf / 2 - drawer / 3 - corner / 4 - cargo
	void SetWardrobeModel(int i);

	//Sets automatic ratio for drawers - 1(F),3(T) / shelfs 2(F), 4(T)
	void SetAutoRatio(int i);

	//Sets amount and height of shelfs in wardrobe
	void SetShelfs(int amount, float* height);

	//Sets amount and height of drawers in wardrobe
	void SetDrawers(int amount, float* height);

	//[Validation and optimalization]
	bool CheckRatioChanges();
};

