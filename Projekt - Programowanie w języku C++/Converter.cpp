#include "Converter.h"

Converter::Converter()
{
}

Converter::Element* Converter::Calculate(Element* target, float x, float y, float z, int shelf_amount)
{
		
		float thickness = 18;
		float crossbar = 100;

		auto i = 0;
		target->x = x;
		target->y = thickness;
		target->z = z;
		target++;

		target->x = thickness;
		target->y = y;
		target->z = z;
		target++;

		target->x = thickness;
		target->y = y;
		target->z = z;
		target++;

		target->x = x;
		target->y = thickness;
		target->z = crossbar;
		target++;

		target->x = x;
		target->y = thickness;
		target->z = crossbar;
		target++;

		if (shelf_amount != 0)
		{
			for (int x = 0; x < shelf_amount; x++)
			{
				target->x = x;
				target->y = thickness;
				target->z = (z - 10);
				target++;
			}
		}

		return target;

}


Converter::~Converter()
{
}
