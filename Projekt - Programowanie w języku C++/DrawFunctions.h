#include <glad/glad.h>
#include <cstddef>
#include <stdlib.h>
#include <array>
#include <vector>
#include <stdexcept>

class Structure
{
	size_t MaxQuadCount;
	size_t MaxVertexCount;
	size_t MaxIndexCount;
	GLuint* CuboidIndices;

	public:

		struct Vec2
		{
			float s, t;
		};

		struct Vec3
		{
			float x, y, z;
		};

		struct Vertex 
		{
			Vec3 Position;
			Vec3 Color;
			Vec2 Texture;
		};


	Structure(size_t MaxQuadCount, int loop);
	~Structure();

	Vertex* CreateCuboid(Vertex* target, float x, float y, float z);
	void Create_Indicies(int loop_amount);
	void SetVariables(size_t MaxQuadCount);
	std::array<Structure::Vertex, 1000> Draw_Structure(float x, float y, float z, GLuint type);
	size_t GetMaxQuadCount();
	size_t GetMaxVertexCount();
	size_t GetMaxIndexCount();
	GLuint* GetCuboidIndices();
};
