#pragma once
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
#include <glm/gtx/rotate_vector.hpp> 
class Structure
{
	size_t MaxQuadCount;
	size_t MaxVertexCount;
	size_t MaxIndexCount;
	std::vector<GLuint> CuboidIndices;
	glm::vec3 basePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	string DrawDirection;
	const char* Rotation;
	const char* FatherStructureRotation = "x";

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
			const char* Elem_ID;
			bool HitAvailable = false;
		};

		struct ElementData {
			std::string ID;
			std::vector<Vertex> Vertices;
			std::vector<GLuint> Indices;
			glm::vec3 HitboxMin;
			glm::vec3 HitboxMax;
		};

		struct RayHitInfo {
			std::string ElemID;
			glm::vec3 Normal;    // opcjonalnie: wektor normalny powierzchni
			glm::vec3 HitPoint;  // opcjonalnie: miejsce trafienia
		};

	Structure(Converter Con, Wardrobe Wardrobe);
	~Structure();
	std::vector<Vertex> Vertices;

	std::vector<ElementData> ElementVector;
	std::vector<glm::vec3> HitboxVertices; 
	glm::vec3 HitboxMin, HitboxMax;

	//[Object Generators]
	void CreateStruct(int elem_id, float TexIndex, Converter Con, Vertex* target); // Creates a single Cuboid based on passed values
	//void Create_Indicies(int loop_amount); // Generates Indices (patterns) of triangles that will be made
	//void Create_Indicies(); //Generates Indices (patterns) of trinagle that will be drawn
	void SetVariables(size_t MaxStructures); // Sets all Structure Class members (such as MaxQuadCount, MaxVertexCount, MaxIndexCount)
	void DrawStructure(Converter Con, Wardrobe wardrobe); //Static method (used Converter data)

	//[Element drawing funciotns]
	void SetDrawDirection(string direction);
	string GetDrawDirection();
	void BasePositionUpdate(Wardrobe wardrobe);
	glm::vec3 RotateElement(const Vertex& v);
	void DrawBottom(Converter Con, Vertex* target);
	void DrawCrossBars(Converter Con, Vertex* target);
	void DrawSides(Converter Con, Vertex* target);
	void DrawBlindSide(Converter Con, Vertex* target, float basex, float basez, string DrawDirection);
	void DrawShelfs(Converter Con, Vertex* target, Wardrobe wardrobe);
	void DrawDrawers(Converter Con, Vertex* target, Wardrobe wardrobe);
	void DrawFronts(Converter Con, Vertex* target, Wardrobe wardrobe);

	//[Geters]
	size_t GetMaxQuadCount(); //Returns MaxQuad
	size_t GetMaxVertexCount(); //Returns MaxVertex
	size_t GetMaxIndexCount(); //Returns MaxIndex
	std::vector<GLuint> GetCuboidIndices(); // Returns Cuboid Indicies (used for traingle draw)
	std::vector<Structure::Vertex> GetVertices(); //Returns current Verticies vector
	glm::vec3 GetBasePositon(); //Return position shifted by user selection
	const char* GetStructureRotation();

	//[Seters]
	void SetStructureBasePosition(glm::vec3 positon);
	void SetStructureRotation(glm::vec3 normal);
	//[General Methods]
	void CheckVennerConfig(vector<string> veneer_config);
	void UpdateStructure(Converter Con);
	void VeneerTexture(Converter Con, float veneer_id, int element_id, Vertex* target);

	//Hitbox related methods
	void UpdateHitboxData();
	void ShowHitboxes(bool highlight);
	void HideHitboxes();
	void ClearVector(); // Clears the Verticies vector (one that is beeing sent to OpenGl vertex buffer)
};
