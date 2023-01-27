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
	std::vector<Vertex> Vertices;
	Vertex* CreateCuboid(Vertex* target, float x, float y, float z, float side); // Creates a single Cuboid based on passed values 
	void Create_Indicies(int loop_amount); // Generates Indices of triangles that will be made
	void SetVariables(size_t MaxQuadCount); // Sets all Structure Class members (such as MaxQuadCount, MaxVertexCount, MaxIndexCount)
	void DrawStructure(float x, float y, float z, GLuint NumberofCuboids); // Creates Structure of Cuboids (use CreateCuboid func.)
	size_t GetMaxQuadCount(); //Returns MaxQuad
	size_t GetMaxVertexCount(); //Returns MaxVertex
	size_t GetMaxIndexCount(); //Returns MaxIndex
	GLuint* GetCuboidIndices(); // Returns Cuboid Indicies (used for traingle draw)
	std::vector<Structure::Vertex> GetVertices(); //Returns current Verticies vector
	void ClearVector(); // Clears the Verticies vector (one that is beeing sent to OpenGl vertex buffer)
};
