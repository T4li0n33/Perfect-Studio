#include <glad/glad.h>
#include <cstddef>
#include <stdlib.h>
#include <array>
#include <vector>
#include <stdexcept>
#include <gl/Gl.h>
#include "Converter.h"
#include "Wardrobe.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma once

class Structure
{
	size_t MaxQuadCount;
	size_t MaxVertexCount;
	size_t MaxIndexCount;
	std::vector<GLuint> CuboidIndices;
	
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
			glm::vec3 Position;
			Vec3 Color;
			Vec2 Texture;
			float TexIndex;
		};


	Structure(Converter Con, Wardrobe Wardrobe);
	~Structure();
	std::vector<Vertex> Vertices;

	//[Object Generators]
	void CreateStruct(int elem_id, float TexIndex, Converter Con, Vertex* target); // Creates a single Cuboid based on passed values
	void Create_Indicies(int loop_amount); // Generates Indices (patterns) of triangles that will be made
	void SetVariables(size_t MaxStructures); // Sets all Structure Class members (such as MaxQuadCount, MaxVertexCount, MaxIndexCount)
	void DrawStructure(Converter Con, Wardrobe wardrobe); //Static method (used Converter data)

	//[Element drawing funciotns]
	void DrawBottom(Converter Con, Vertex* target);
	void DrawCrossBars(Converter Con, Vertex* target);
	void DrawSides(Converter Con, Vertex* target);
	void DrawShelfs(Converter Con, Vertex* target, Wardrobe wardrobe);
	void DrawDrawers(Converter Con, Vertex* target, Wardrobe wardrobe);
	void DrawFronts(Converter Con, Vertex* target, Wardrobe wardrobe);

	//[Geters]
	size_t GetMaxQuadCount(); //Returns MaxQuad
	size_t GetMaxVertexCount(); //Returns MaxVertex
	size_t GetMaxIndexCount(); //Returns MaxIndex
	std::vector<GLuint> GetCuboidIndices(); // Returns Cuboid Indicies (used for traingle draw)
	//std::vector<Structure::Vertex> GetVertices(); //Returns current Verticies vector

	//[General Methods]
	void CheckVennerConfig(vector<string> veneer_config);
	void UpdateStructure(Converter Con);
	void VeneerTexture(Converter Con, float veneer_id, int element_id, Vertex* target);
	void ClearVector(); // Clears the Verticies vector (one that is beeing sent to OpenGl vertex buffer)
};
