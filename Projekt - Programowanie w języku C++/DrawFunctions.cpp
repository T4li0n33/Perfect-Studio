#include "DrawFunctions.h"

using namespace glm;

void Structure::Create_Indicies(int loop_amount)
{
	CuboidIndices.clear();
	CuboidIndices.shrink_to_fit();
	GLuint table[] = {0,1,2,2,3,0,4,5,6,6,7,4,1,6,5,5,2,1,7,0,3,3,4,7,3,2,5,5,4,3,7,6,1,1,0,7};
	
	GLuint* CuboidID = new GLuint[MaxIndexCount+1];
	for (int cuboid_number = 0; cuboid_number < loop_amount; cuboid_number++)
	{
		int next_cuboid_id = 8 * cuboid_number;
		for (int i = 0; i < 36; i++)
		{
			CuboidID[i + cuboid_number * 36] = table[i] + next_cuboid_id;
			if (i >=36)  throw std::overflow_error("Too much indices was generated");
		}
	}

	for (int x = 0 ; x<MaxIndexCount+1; x++)
	{
		CuboidIndices.push_back(CuboidID[x]);
	}
	delete[] CuboidID;
	return;
}

void Structure::CreateStruct(int elem_id, Converter Con, Vertex* target)//Creating cuboid based on input values
{
	int i = 0;
	target[i].Position = { 0.0f, 0.0f,  0.0f }; // 0
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 0.0f };

	i++;

	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / 100.0f , 0.0f }; // 1
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 1.0f };
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / 100.0f, Con.Elements_vector[elem_id].y / 100.0f, 0.0f }; // 2
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 1.0f };
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / 100.0f,  0.0f,  0.0f }; //3
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 0.0f };
	i++;



	target[i].Position = { Con.Elements_vector[elem_id].x / 100.0f,  0.0f, Con.Elements_vector[elem_id].z / 100.0f };//4
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 0.0f };
	i++;



	target[i].Position = { Con.Elements_vector[elem_id].x / 100.0f , Con.Elements_vector[elem_id].y / 100.0f , Con.Elements_vector[elem_id].z / 100.0f };//5
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 1.0f, 1.0f };
	i++;


	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / 100.0f , Con.Elements_vector[elem_id].z / 100.0f };//6
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 1.0f };
	i++;


	target[i].Position = { 0.0f,  0.0f, Con.Elements_vector[elem_id].z / 100.0f };//7
	target[i].Color = { 0.83f, 0.70f, 0.44f };
	target[i].Texture = { 0.0f, 0.0f };
	i++;


	return;

}

Structure::Structure(Converter Con, Wardrobe Wardrobe) // Class constructor
{
	SetVariables(Con.Elem_Num);
	Create_Indicies(Con.Elem_Num);
}

Structure::~Structure()
{
}

void Structure::DrawStructure(Converter Con, Wardrobe wardrobe)
{

	Vertices.clear();
	Vertices.shrink_to_fit();

	GLuint VertexAmount = 8 * Con.Elements_vector.size();
	Vertex* vertices = new Vertex[VertexAmount + 1];
	DrawSides(Con, vertices);
	DrawBottom(Con, vertices);
	DrawCrossBars(Con, vertices);
	DrawShelfs(Con, vertices, wardrobe);
	CuboidIndices.shrink_to_fit();
	delete[] vertices;
	return;
}

void Structure::UpdateStructure(Converter Con)
{
	SetVariables(Con.Elem_Num);
	Create_Indicies(Con.Elem_Num);
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

std::vector<GLuint> Structure::GetCuboidIndices()
{ 
	return CuboidIndices;
}

void Structure::SetVariables(size_t MaxStructures)
{
	MaxQuadCount = MaxStructures * 6;
	MaxIndexCount = MaxQuadCount * 128; // Max Sets of Indices ( Used to draw a triangles )
	MaxVertexCount = MaxQuadCount * 4;
}

void Structure::DrawBottom(Converter Con, Vertex* target)
{
	int size = Con.Elements_vector.size();
	for (int z = 0; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "B")
		{
			CreateStruct(z, Con, target);

			for (int x = 0; x < 8; x++)
			{
				Vertices.push_back(target[x]);
			}
		}

	}

	return;
}

void Structure::DrawSides(Converter Con, Vertex* target)
{
	int size = Con.Elements_vector.size();
	int z= 0;
	int next_case = 1;
	glm::vec3 transform = vec3(0.0f, 0.0f, 0.0f);
	for (; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "S" && !Con.Elements_vector[z].alreadydrawn)
		{
			CreateStruct(z, Con, target);

			switch (next_case)
			{
			case 1 :
				transform = vec3(0.0f, Con.Elements_vector[0].y / 100.0f, 0.0f);
				next_case++;
				break;
			case 2:
				transform = vec3((Con.Elements_vector[0].x / 100.00f) - (Con.Elements_vector[0].y / 100.00f), Con.Elements_vector[0].y / 100.0f, 0.0f);
				next_case++;
			}
			
			for (int x = 0; x < 8; x++)
			{
	
				target[x].Position = target[x].Position + transform;
				Vertices.push_back(target[x]);
			}
			Con.AlreadyDrawn(z);
		}

	}
	return;
}

void Structure::DrawCrossBars(Converter Con, Vertex* target)
{
	int size = Con.Elements_vector.size();
	float side_width = 0.00f;
	float side_height = 0.00f;
	int next_case = 1;
	float elem_tickness = 0.18f;
	glm::vec3 transform = vec3(0.0f, 0.0f, 0.0f);
	
	for (int p = 0; p < size; p++)
	{
		if (Con.Elements_vector[p].elem_type == "S")
		{
			side_width = Con.Elements_vector[p].x / 100.00f;
			side_height = Con.Elements_vector[p].y / 100.00f;
		}
	}

	for (int z = 0; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "C" && !Con.Elements_vector[z].alreadydrawn)
		{
			CreateStruct(z, Con, target);

			switch (next_case)
			{
			case 1:
				transform = vec3(side_width, side_height, 0.0f);
				next_case++;
				break;
			case 2:
				transform = vec3(side_width, side_height, (Con.Elements_vector[0].z / 100.0f) - (Con.Elements_vector[z].z / 100.00f));
				next_case++;
			}

			for (int x = 0; x < 8; x++)
			{

				target[x].Position = target[x].Position + transform;
				Vertices.push_back(target[x]);
			}
			Con.AlreadyDrawn(z);
		}

	}

	return;
}

void Structure::DrawShelfs(Converter Con, Vertex* target , Wardrobe wardrobe)
{
	int size = Con.Elements_vector.size();
	int shelf_num = 0;
	float side_width = 0.00f;
	float side_height = 0.00f;
	int next_case = 1;
	float elem_tickness = 0.18f;
	glm::vec3 transform = vec3(0.0f, 0.0f, 0.0f);

	for (int p = 0; p < size; p++)
	{
		if (Con.Elements_vector[p].elem_type == "S")
		{
			side_width = Con.Elements_vector[p].x / 100.00f;
			side_height = Con.Elements_vector[p].y / 100.00f;
		}
	}

	for (int z = 0; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "G" && !Con.Elements_vector[z].alreadydrawn)
		{
			CreateStruct(z, Con, target);
	
			transform = vec3(side_width, wardrobe.shelf_ratio[shelf_num]/100.00f, 0.0f);
			shelf_num++;

			for (int x = 0; x < 8; x++)
			{
				
				target[x].Position = target[x].Position + transform;
				Vertices.push_back(target[x]);
			}
			Con.AlreadyDrawn(z);
		}

	}

	return;
}
void Structure::ClearVector() // Clears the Verticies vector (one that is beeing sent to OpenGl vertex buffer)
{
	Vertices.clear();
}