#pragma once
class Converter
{

public:
	struct Element
	{
		int x;
		int y;
		int z;
	};
	Converter();
	Element* Calculate(Element* target, float x, float y, float z, int shelf_amount);
	~Converter();
};

