#pragma once
class Settings
{
	bool showWindow = true;
	bool showWindow2 = true; 
	bool project_mode = false;
	bool exit = false;
	bool calc_mode = false;
	bool opengl_presentation_mode = false;
	const unsigned int width = 1200;
	const unsigned int height = 800;

public:
	//[Geters]

	// Returns boolean "show window" /1=window1/2=window2/
	bool GetWindow(int i);

	//Returns boolean based on i-value /1=project_mode/2=calc_mode/3=opengl/4=exit
	bool GetMode(int i);

	//Returns Window width
	int WindowWidth();

	//Returns Window height
	int WindowHeight();
	
	//[Seters]
	
	//Sets boolean visibility of window / 1 - showWindow / 2 - showWindow2
	void SetWindow(int i);

	//Sets mode where  1 - project mode / 2 - calc_mode / 3 - opengl_presentation / 4 - exit
	void SetMode(int i);

	//Repairs the close window issue
	void RepairWindow();

};

