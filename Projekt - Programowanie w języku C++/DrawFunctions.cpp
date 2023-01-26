#include "DrawFunctions.h"


void Structure::Create_Indicies(int loop_amount)
{
	GLuint table[36] = { 0, 1, 3, 1, 2, 3, 4, 5, 7, 5, 6, 7, 0, 1, 4, 1, 4, 5, 2, 3, 7, 2, 6, 7, 0, 3, 4, 3, 4, 7, 1, 2, 5, 2, 5, 6 };

	GLuint* CuboidIndices = new GLuint[MaxIndexCount];
	for (int cuboid_number = 0; cuboid_number < loop_amount; cuboid_number++)
	{
		int next_cuboid_id = 8 * cuboid_number;
		for (int i = 0; i < 36; i++)
		{
			CuboidIndices[i + cuboid_number * 36] = table[i] + next_cuboid_id;
			//else throw std::overflow_error("Too much indices");
		}
	}

	this->CuboidIndices = CuboidIndices;
}

Structure::Vertex* Structure::CreateCuboid(Vertex* target, float x, float y, float z)//Creating cuboid based on input values
{

	float thickness = 0.18f;
	float crossbar = 1.0f;

	target->Position = { 0.0f, 0.0f,  0.0f }; // 0
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 0.0f, 0.0f };
	target++;

	target->Position = { 0.0f , y, 0.0f }; // 1
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 0.0f, 1.0f };
	target++;

	target->Position = { x, y, 0.0f }; // 2
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 1.0f, 1.0f };
	target++;

	target->Position = { x,  0.0f,  0.0f }; //3
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 1.0f, 0.0f };
	target++;

	target->Position = { 0.0f,  0.0f, z };//4
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 0.0f, 0.0f };
	target++;

	target->Position = { 0.0f, y, z };//5
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 0.0f, 1.0f };
	target++;

	target->Position = { x, y, z };//6
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 1.0f, 1.0f };
	target++;

	target->Position = { x,  0.0f, z };//7
	target->Color = { 0.83f, 0.70f, 0.44f };
	target->Texture = { 1.0f, 0.0f };
	target++;


	return target;

}

Structure::Structure(size_t MaxQuadCount, int loop) // Class constructor
{
	SetVariables(MaxQuadCount);
	Create_Indicies(loop);
}

Structure::~Structure()
{

}


std::array<Structure::Vertex, 1000> Structure::Draw_Structure(float x, float y, float z, GLuint type)
{

	std::array<Structure::Vertex, 1000> vertices{};
	Structure::Vertex* buffer = vertices.data();
	buffer = Structure::CreateCuboid(buffer, x, y, z);		
	
	return vertices;
}

size_t Structure::GetMaxQuadCount()
{
	return size_t(MaxQuadCount);
}

size_t Structure::GetMaxVertexCount()
{
	return size_t(MaxVertexCount);
}

size_t Structure::GetMaxIndexCount()
{
	return size_t(MaxIndexCount);
}

GLuint* Structure::GetCuboidIndices()
{
	return CuboidIndices;
}

void Structure::SetVariables(size_t MaxQuad)
{
	MaxQuadCount = MaxQuad;
	MaxIndexCount = MaxQuad * 6;
	int x = MaxQuad / 6;
	MaxVertexCount = (MaxQuad + (2 * static_cast<unsigned long long>(x)));
}