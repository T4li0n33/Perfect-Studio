#pragma once
#include <string>


class Wardrobe
{
	bool wardrobe_type_bottom = false;
	bool wardrobe_type_top = false;
	bool wardrobe_type_unusual = false;
	bool wardrobe_model_shelf = false;
	bool wardrobe_model_drawer = false;
	bool wardrobe_model_corner = false;
	bool wardrobe_model_cargo = false;
	bool auto_shelf_ratio = true;
	bool auto_drawer_ratio = true;
	bool auto_front_ratio = true;
	bool wardrobe_corner_lemans = false;
	bool wardrobe_corner_shelf = false;
	bool wardrobe_type_choosed = false;
	bool wardrobe_model_choosed = false;
	bool wardrobe_size_placed = false;
	bool with_front = false;
	bool front_bool = true;
	

	float base_x = 0, base_y = 0, base_z = 0;
	int shelf_number = 0;
	int drawer_number = 0;
	int wardrobe_index = 0;
	int fronts_amount = 0;
	int selected_drawer_color = 0; //0 = gray, 1 = white, 2 = black
	float blind_side_size = 0.00f;
	float diaphragm_size = 0.00f;
	std::string veneer;

public:
	
	float previous_s_ratio[4] = { 0,0,0,0 };
	float previous_d_ratio[4] = { 0,0,0,0 };
	float previous_f_ratio[4]{ 0,0,0,0 };
	float drawer_ratio[4]{ 0,0,0,0 };
	float shelf_ratio[4]{ 0,0,0,0 };
	float front_ratio[4]{ 0,0,0,0 };
	//[Geters]
	
	// Returns boolean based od i-value /1=bottom/2=top/3=unusual
	bool GetWardrobeType(int i);

	// Returns boolean based od i-value /1=corner_lemans/2=corner_shelf/
	bool GetWardrobeTypeCorner(int i);

	// Returns boolean based od i-value /1=model_shelf/2=model_drawer/3=model_cargo/4=model_corner/
	bool GetWardrobeModel(int i);

	//Returns boolean based on i-value where /1=shelf_ratio/2=drawer_ratio
	bool GetAutoRatio(int i);


	//Returns Front boolean 1 - with_front /  2 - front_bool
	bool GetFrontBool(int i);

	//Returns pointer to table with saved ratio (also checks both tables for emptiness)
	float GetShelfRatio();
	float GetDrawerRatio();

	//Returns amount of drawers - 1/shelfs - 2 / 3-fronts
	int GetAmount(int i);

	//Returns veener color (string)
	std::string GetVeener();

	//Returns id of selected drawer color
	
	int GetDrawerColor();

	int GetDrawerTexture();

	std::string GetDrawerColor(int id);

	//Checks if all needed inputs are placed
	bool AreOptionsPicked();
	
	
	float GetBaseSettings(int i);
	float GetBaseSettings(char i);

	//Returns diaphragm size
	float GetDiaphragmSize();

	//Returns size of blind side in corner wardrobe
	float GetBlindSize();

	//[Seters]

	//Sets input value for x,y,z where /1 - x/ 2 - y / 3 - z/
	void SetSize(int i, float value);

	//Sets type // 1 - bottom / 2 - top / 3 - unusual / 4 - model_choosed / 5 - size_placed
	void SetWardrobeType(int i);

	//Sets boolean type of corner wardrobe / 1 - lemans / 2 - shelf
	void SetWardrobeTypeCorner(int i);

	//Sets model // 1 - shelf / 2 - drawer / 3 - corner / 4 - cargo
	void SetWardrobeModel(int i);

	//Sets automatic ratio for drawers - 2(F),3(T) / shelfs 1(F), 4(T) / fronts 5(F), 6(T)
	void SetAutoRatio(int i);

	//Sets boolean for front calculations (with_front - 1 is false, 2 is true)(front_boolean - 3 is false, 4 is true)
	void SetFrontBool(int i);

	//Sets amount and height of shelfs in wardrobe
	void SetShelfs(int amount, float* height);

	//Sets amount and height of drawers in wardrobe
	void SetDrawers(int amount, float* height);

	//Sets amount and height of fronts
	void SetFronts(int amount, float* width);

	void SetDrawerColor(int color);

	void SetVeenerColor(std::string color);

	//void SetFirstFront(bool t);
	//[Validation and optimalization]
	bool CheckRatioChanges();
};

