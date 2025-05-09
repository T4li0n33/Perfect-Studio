﻿#include "DrawFunctions.h"

using namespace glm;
constexpr auto vertex_on_one_elem = 24;
constexpr auto thickness = 18;
constexpr auto drawer_thickness = 16;
constexpr auto vertex_on_one_side = vertex_on_one_elem/6;
constexpr auto front_texture_id = 1;
constexpr auto SCALE = 100.0f;


void Structure::CreateStruct(int elem_id, float TexIndex, Converter Con, Vertex* target)//Creating cuboid based on input values
{
	int i = 0;
	// Dolna ściana (Bottom face)
	target[i].Position = { 0.0f, 0.0f, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, 0.0f, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, 0.0f, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { 0.0f, 0.0f, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	// Górna ściana (Top face)
	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / SCALE, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, Con.Elements_vector[elem_id].y / SCALE, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, Con.Elements_vector[elem_id].y / SCALE, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / SCALE, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	// Przednia ściana (Front face)
	target[i].Position = { 0.0f, 0.0f, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, 0.0f, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, Con.Elements_vector[elem_id].y / SCALE, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / SCALE, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	// Tylna ściana (Back face)
	target[i].Position = { 0.0f, 0.0f, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, 0.0f, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, Con.Elements_vector[elem_id].y / SCALE, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / SCALE, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	// Lewa ściana (Left face)
	target[i].Position = { 0.0f, 0.0f, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / SCALE, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { 0.0f, Con.Elements_vector[elem_id].y / SCALE, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { 0.0f, 0.0f, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	// Prawa ściana (Right face)
	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, 0.0f, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, Con.Elements_vector[elem_id].y / SCALE, 0.0f };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 0.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, Con.Elements_vector[elem_id].y / SCALE, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 1.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;

	target[i].Position = { Con.Elements_vector[elem_id].x / SCALE, 0.0f, Con.Elements_vector[elem_id].z / SCALE };
	target[i].Color = { 0.5f, 0.5f, 0.5f };
	target[i].Texture = { 0.0f, 1.0f };
	target[i].TexIndex = TexIndex;
	i++;


	VeneerTexture(Con, 1, elem_id, target);
	return;

}

Structure::Structure(Converter Con, Wardrobe Wardrobe) // Class constructor
{
	SetVariables(Con.Elem_Num);
}

Structure::~Structure()
{
}

void Structure::DrawStructure(Converter Con, Wardrobe wardrobe)
{

	Vertices.clear();
	Vertices.shrink_to_fit();
	GLuint VertexAmount = vertex_on_one_elem * Con.Elements_vector.size();
	Vertex* vertices = new Vertex[VertexAmount + 1];
	BasePositionUpdate(wardrobe);
	DrawSides(Con, vertices);
	DrawBlindSide(Con, vertices, wardrobe.GetBaseSettings('x'), wardrobe.GetBaseSettings('z'), DrawDirection);
	DrawBottom(Con, vertices);
	DrawCrossBars(Con, vertices);
	DrawShelfs(Con, vertices, wardrobe);
	DrawDrawers(Con, vertices, wardrobe);
	DrawFronts(Con, vertices, wardrobe);
	CuboidIndices.shrink_to_fit();
	delete[] vertices;
	return;
}

void Structure::CheckVennerConfig(vector<string> veneer_config)
{
	int size = veneer_config.size();
	for (int i = 0; i < size; i++)
	{
		if (veneer_config.at(i) == "")
		{

		}
	}
}

void Structure::UpdateStructure(Converter Con)
{
	SetVariables(Con.Elem_Num);
	//Create_Indicies(Con.Elem_Num);
}

void Structure::VeneerTexture(Converter Con, float veneer_id, int element_id, Vertex *target)
{
	//Con.Elements_vector[element_id].veneer
	int first, second;
	vector<string> veneer_config = Con.Elements_vector[element_id].veneer;
	if (Con.Elements_vector[element_id].x > Con.Elements_vector[element_id].y) {
		first = Con.Elements_vector[element_id].x;
		second = Con.Elements_vector[element_id].y;
	}
	else {
		first = Con.Elements_vector[element_id].y;
		second = Con.Elements_vector[element_id].x;
	}

	if (Con.Elements_vector[element_id].z > first) {
		second = first;
		first = Con.Elements_vector[element_id].z;
	}
	else if (Con.Elements_vector[element_id].z > second) {
		second = Con.Elements_vector[element_id].z;
	}

	

	if ((Con.Elements_vector[element_id].x == thickness) || (Con.Elements_vector[element_id].x == drawer_thickness))
	{
		for (int x = 0; x < vertex_on_one_side * 4 ; x++) // Bottom, Top, Front, Back
		{
			target[x].TexIndex = veneer_id;
		}
	}

	if ((Con.Elements_vector[element_id].y == thickness) || (Con.Elements_vector[element_id].y == drawer_thickness))
	{
		for (int x = 8; x < (vertex_on_one_side * 6); x++) // Left, Right, Front, Back
		{
			target[x].TexIndex = veneer_id;
		}
	}

	if ((Con.Elements_vector[element_id].z == thickness) || (Con.Elements_vector[element_id].z == drawer_thickness)) // Left, Right, Top, Bottom
	{
		int startIndices[4] = { 0, 4, 16, 20 }; // Indeksy początkowe dla kolejnych boków
	
		// Przejdź przez każdy z 4 boków
		for (int i = 0; i < 4; i++)
		{
			int startIndex = startIndices[i]; // Pobierz początkowy indeks dla boku

			// Wybierz teksturę na podstawie veneer_config
			float texIndex = 3;
			if (veneer_config.at(i) == "")
				 texIndex = 0;
			
			// Zastosuj teksturę do 4 wierzchołków na aktualnym boku
			for (int j = 0; j < vertex_on_one_side; j++)
			{
				target[startIndex + j].TexIndex = texIndex;
			}
		}
	}
}

void Structure::UpdateHitboxData()
{
	HitboxVertices.clear();
	bool first = true;

	for (const auto& v : Vertices) {
		if (v.Elem_ID && strcmp(v.Elem_ID, "S") == 0 || v.Elem_ID == "K") {
			HitboxVertices.push_back(v.Position);

			// Oblicz AABB w tej samej pętli
			if (first) {
				HitboxMin = HitboxMax = v.Position;
				first = false;
			}
			else {
				HitboxMin = glm::min(HitboxMin, v.Position);
				HitboxMax = glm::max(HitboxMax, v.Position);
			}
		}
	}

	if (HitboxVertices.empty()) {
		HitboxMin = HitboxMax = glm::vec3(0.0f);
	}
}

void Structure::ShowHitboxes(bool highlight)
{
	for (size_t i = 0; i < Vertices.size(); i++)
	{
		if (Vertices[i].Elem_ID && strcmp(Vertices[i].Elem_ID, "S") == 0)
		{
			if (highlight)
			{
				Vertices.at(i).Color.x = 0.0f;
				Vertices.at(i).Color.y = 1.0f;
				Vertices.at(i).Color.z = 0.0f;
			}
		}
	}
}

void Structure::HideHitboxes()
{
	for (auto& element : ElementVector)
	{
		for (auto& vertex : element.Vertices)
		{
			if ((vertex.Elem_ID && strcmp(vertex.Elem_ID, "S") == 0) ||
				(vertex.Elem_ID && strcmp(vertex.Elem_ID, "K") == 0))
			{
				vertex.Color = { 0.5f, 0.5f, 0.5f };
				vertex.HitAvailable = false;
			}
		}
	}
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

std::vector<Structure::Vertex> Structure::GetVertices()
{
	return Vertices;
}

glm::vec3 Structure::GetBasePositon()
{
	return glm::vec3();
}

const char* Structure::GetStructureRotation()
{
	return Rotation;
}

void Structure::SetStructureBasePosition(glm::vec3 positon)
{
	this->basePosition = positon;
}

void Structure::SetStructureRotation(glm::vec3 normal)
{
	if (std::abs(normal.x) > 0.5f)
	{
		Rotation = "x";
	}
	else if (std::abs(normal.y) > 0.5f)
	{
		Rotation = "y";
	}
	else if (std::abs(normal.z) > 0.5f)
	{
		Rotation = "z";
	}
	else
	{
		Rotation = ""; // Brak rotacji lub nieznana normalna
	}
}


void Structure::SetVariables(size_t MaxStructures)
{
	MaxQuadCount = MaxStructures * 6;
	MaxIndexCount = MaxStructures * 36; // Max Sets of Indices ( Used to draw a triangles )
	MaxVertexCount = MaxQuadCount * 4;
}

void Structure::SetDrawDirection(string direction)
{
	this->DrawDirection = direction;
}

string Structure::GetDrawDirection()
{
	return DrawDirection;
}

void Structure::BasePositionUpdate(Wardrobe wardrobe)
{
	if (DrawDirection == "left")
	{
		basePosition.x = basePosition.x - (wardrobe.GetBaseSettings('x') / 100.f);
		basePosition.y = basePosition.y - (thickness / SCALE);
	}
	else if (DrawDirection == "right")
	{
		basePosition.y = basePosition.y - (thickness / SCALE);
	}
}

glm::vec3 Structure::RotateElement(const Vertex& v)
{
	glm::vec3 p = v.Position;

	if (Rotation == "x")
	{
		// Rotacja 90° wokół osi X (Y <-> Z)
		return glm::vec3(p.x, p.y, p.z);
	}
	else if (Rotation == "y")
	{
		
		// Rotacja 90° wokół osi Y (X <-> Z)
		return glm::vec3(-p.y, p.x, p.z);

	}
	else if (Rotation == "z")
	{
		if (this->DrawDirection == "corner_left" || this->DrawDirection == "left")
		// Rotacja 90° wokół osi Z (X <-> Y)
		return glm::vec3(p.z, p.y, p.x);

		else return glm::vec3(-p.z, p.y, p.x);
	}

	return p; 
}




void Structure::DrawBottom(Converter Con, Vertex* target)
{
	int size = Con.Elements_vector.size();
	glm::vec3 transform = glm::vec3(0.0f);

	for (int z = 0; z < size; z++) {
		if (Con.Elements_vector[z].elem_type == "B") {
			CreateStruct(z, 0, Con, target);
			if (Con.GetWardrobeType() == 2)
				transform = glm::vec3((Con.Elements_vector[1].y / SCALE), 0.0f, 0.0f);

			ElementData element;
			element.ID = "B";

			for (int x = 0; x < vertex_on_one_elem; x++) {
				target[x].Position = transform + basePosition + RotateElement(target[x]);
				target[x].Elem_ID = "B";
				Vertices.push_back(target[x]);
				element.Vertices.push_back(target[x]);
			}

			// Wylicz hitbox:
			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;

			ElementVector.push_back(element);
		}
	}
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
			CreateStruct(z, 0, Con, target);
			ElementData element;
			element.ID = "S";

			switch (next_case)
			{
			case 1 : //Transformation for first side panel

				transform = vec3(0.0f, Con.Elements_vector[0].y / SCALE, 0.0f);
				if (Con.GetWardrobeType() == 2) transform = vec3(0.0f, 0.0f, 0.0f);
				next_case++;
				break;
			case 2: // Transformation for second side panel
				
				transform = vec3((Con.Elements_vector[0].x / SCALE) - (Con.Elements_vector[0].y / SCALE), Con.Elements_vector[0].y / SCALE, 0.0f);
				if (Con.GetWardrobeType() == 2) transform = vec3((Con.Elements_vector[0].x / SCALE + 0.36f) - (Con.Elements_vector[0].y / SCALE), 0.0f, 0.0f);
				next_case++;
				break;
			}
			
			for (int x = 0; x < vertex_on_one_elem; x++)
			{
	
				target[x].Position += transform;
				target[x].Position = RotateElement(target[x]) + basePosition;
				target[x].Elem_ID = "S";
				Vertices.push_back(target[x]);
				element.Vertices.push_back(target[x]);
			}

			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;

			ElementVector.push_back(element);
			Con.AlreadyDrawn(z);
		}

	}
	return;
}

void Structure::DrawBlindSide(Converter Con, Vertex* target, float basex, float basez, string DrawDirection)
{

	int size = Con.Elements_vector.size();
	float finalX = 0.0f;
	glm::vec3 transform = vec3(0.0f, 0.0f, 0.0f);
	for (int z = 0; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "K")
		{
			if (DrawDirection == "left")
			{
				finalX = 0.0f;
			}
			else 
			{ 
				finalX = (basex - Con.Elements_vector[z].x);
			}
			transform = vec3((finalX) / SCALE, 0.0f, basez / SCALE);
			CreateStruct(z, 0, Con, target);
			ElementData element;
			element.ID = "K";

			for (int x = 0; x < vertex_on_one_elem; x++)
			{
				target[x].Position = target[x].Position + transform + basePosition;
				target[x].Elem_ID = "K";
				Vertices.push_back(target[x]);
				element.Vertices.push_back(target[x]);
			}

			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;

			ElementVector.push_back(element);
		}

	}

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
			side_width = Con.Elements_vector[p].x / SCALE;
			side_height = Con.Elements_vector[p].y / SCALE;
		}
	}

	for (int z = 0; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "C" && !Con.Elements_vector[z].alreadydrawn)
		{
			CreateStruct(z, 0, Con, target);
			ElementData element;
			element.ID = "C";
			switch (next_case)
			{
			case 1:
				transform = vec3(side_width, side_height, 0.0f);
				if(Con.GetWardrobeType() == 2) transform = vec3(side_width, side_height - thickness, 0.0f);
				next_case++;
				break;
			case 2:
				transform = vec3(side_width, side_height, (Con.Elements_vector[0].z / SCALE) - (Con.Elements_vector[z].z / SCALE));
				next_case++;
			}

			for (int x = 0; x < vertex_on_one_elem; x++)
			{
				target[x].Position += transform;
				target[x].Position = RotateElement(target[x]) + basePosition;
				target[x].Elem_ID = "C";
				Vertices.push_back(target[x]);
				element.Vertices.push_back(target[x]);
			}

			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;

			ElementVector.push_back(element);
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
			side_width = Con.Elements_vector[p].x / SCALE;
			side_height = Con.Elements_vector[p].y / SCALE;
		}
	}

	for (int z = 0; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "G" && !Con.Elements_vector[z].alreadydrawn)
		{
			CreateStruct(z, 0, Con, target);
	
			ElementData element;
			element.ID = "G";
			transform = vec3(side_width, wardrobe.shelf_ratio[shelf_num]/SCALE, 0.0f);
			shelf_num++;

			for (int x = 0; x < vertex_on_one_elem; x++)
			{
				
				target[x].Position += transform;
				target[x].Position = RotateElement(target[x]) + basePosition;
				target[x].Elem_ID = "G";
				Vertices.push_back(target[x]);
				element.Vertices.push_back(target[x]);
			}
			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;

			ElementVector.push_back(element);
			Con.AlreadyDrawn(z);
		}

	}

	return;
}

void Structure::DrawDrawers(Converter Con, Vertex* target, Wardrobe wardrobe)
{
	int size = Con.Elements_vector.size();
	int drawer_num = 0;
	int back_num = 0;
	float side_width = 0.00f;
	float side_height = 0.00f;
	int next_case = 1;
	float elem_tickness = 0.16f;
	float spacing = (123.00 / 2)/SCALE;
	glm::vec3 transform = vec3(0.0f, 0.0f, 0.0f);

	for (int p = 0; p < size; p++)
	{
		if (Con.Elements_vector[p].elem_type == "S")
		{
			side_width = Con.Elements_vector[p].x / SCALE;
			side_height = Con.Elements_vector[p].y / SCALE;
		}
	}

	for (int z = 0; z < size; z++)
	{
		if (Con.Elements_vector[z].elem_type == "F" && !Con.Elements_vector[z].alreadydrawn)
		{

			CreateStruct(z, wardrobe.GetDrawerTexture(), Con, target); // Get Color ID and shift it by 2 basic textures
			ElementData element;
			element.ID = "F";

			transform = vec3(spacing, (wardrobe.drawer_ratio[drawer_num]) / SCALE, 0.0f);
			drawer_num++;

			for (int x = 0; x < vertex_on_one_elem; x++)
			{

				target[x].Position += transform;
				target[x].Position = RotateElement(target[x]) + basePosition;
				target[x].Elem_ID = "F";
				Vertices.push_back(target[x]);
				element.Vertices.push_back(target[x]);
			}

			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;
			ElementVector.push_back(element);
			Con.AlreadyDrawn(z);

		}

	}
	for (int a = 0; a < size; a++)
	{
		if (Con.Elements_vector[a].elem_type == "E" && !Con.Elements_vector[a].alreadydrawn)
		{
			CreateStruct(a, wardrobe.GetDrawerTexture(), Con, target);
			ElementData element;
			element.ID = "E";
			transform = vec3(spacing + 0.11f, wardrobe.drawer_ratio[back_num] / SCALE, 0.0f);
			back_num++;

			for (int k = 0; k < vertex_on_one_elem; k++)
			{

				target[k].Position += transform;
				target[k].Position = RotateElement(target[k]) + basePosition;
				target[k].Elem_ID = "E";
				Vertices.push_back(target[k]);
				element.Vertices.push_back(target[k]);
			}
			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;
			ElementVector.push_back(element);
			Con.AlreadyDrawn(a);
		}

	}
}

void Structure::DrawFronts(Converter Con, Vertex* target, Wardrobe wardrobe)
{
	// Get the number of elements in Elements_vector (number of elements to be drawn)
	int size = Con.Elements_vector.size();

	// Array storing size values of elements for further transformation
	int table[5] = { 0,0,0,0,0 };

	// Array for previous results (needed for shifts)
	int prev[4] = { 0,0,0,0 };

	// Variable to track the current position in the `table` array
	int p = 1;

	// Transformation vector for element position
	glm::vec3 transform = vec3(0.0f, 0.0f, 0.0f);

	// Drawer number counter
	int drawer_num = 0;

	// First loop: find and store `x` sizes of elements of type "L" (Fronts)
	// if they meet conditions for wardrobe models 1 and 4
	for (int x = 0; x < size; x++)
	{
		if (Con.Elements_vector[x].elem_type == "L" && !Con.Elements_vector[x].alreadydrawn && (wardrobe.GetWardrobeModel(1) || wardrobe.GetWardrobeModel(4)))
		{
			// Save the element's `x` value in the table
			table[p] = Con.Elements_vector[x].x;
			p++;
		}
	}

	// Second loop: find and store `y` sizes of elements of type "L" (Fronts)
	// if they meet conditions for wardrobe models 2 and 3
	for (int x = 0; x < size; x++)
	{
		if (Con.Elements_vector[x].elem_type == "L" && !Con.Elements_vector[x].alreadydrawn && (wardrobe.GetWardrobeModel(2) || wardrobe.GetWardrobeModel(3)))
		{
			// Save the element's `y` value in the table
			table[p] = Con.Elements_vector[x].y;
			p++;
		}
	}

	// Reset the pointer to the first index in the table
	p = 0;

	// Variable holding the sum of shifts for the current transformations
	int result = 0;
	float CornerFrontX;


	// Loop processing all elements of type "L" and applying transformations
	for (int z = 0; z < size; z++)
	{
		if (DrawDirection == "left")
		{
			CornerFrontX = (wardrobe.GetBaseSettings('x') - Con.Elements_vector[z].x);
		}
		else
		{
			CornerFrontX = 0.0f;
		}

		if (Con.Elements_vector[z].elem_type == "L" && !Con.Elements_vector[z].alreadydrawn)
		{
			// Call the function to create the structure for the element at index `z`
			CreateStruct(z, 1, Con, target);
			ElementData element;
			element.ID = "L";

			// Transformation on the `x` axis for models 1 and 4, and on the `y` axis for models 2 and 3
			if (wardrobe.GetWardrobeModel(1) || wardrobe.GetWardrobeModel(4))
			{
				// Calculate the shift on the x-axis based on the `table` array
				result = result + table[p];
				transform = vec3((result + (p * 3) + CornerFrontX)  / SCALE, 0.0f, wardrobe.GetBaseSettings(3) / SCALE);
				p++;
			}
			else
			{
				// Calculate the shift on the y-axis based on the `table` array
				result = result + table[p];
				transform = vec3(0.0f, (result + (p * 3) + CornerFrontX) / SCALE, wardrobe.GetBaseSettings(3) / SCALE);
				p++;
			}

			// Shift the position of the element's vertices by the transformation vector
			for (int x = 0; x < vertex_on_one_elem; x++)
			{
				target[x].Position += transform;
				target[x].Position = RotateElement(target[x]) + basePosition;
				target[x].Elem_ID = "L";
				Vertices.push_back(target[x]);
				element.Vertices.push_back(target[x]);
			}

			glm::vec3 min = element.Vertices[0].Position;
			glm::vec3 max = element.Vertices[0].Position;
			for (const auto& v : element.Vertices) {
				min = glm::min(min, v.Position);
				max = glm::max(max, v.Position);
			}

			element.HitboxMin = min;
			element.HitboxMax = max;

			ElementVector.push_back(element);
			Con.AlreadyDrawn(z);
		}
	}
}

void Structure::ClearVector() // Clears the Verticies vector (one that is beeing sent to OpenGl vertex buffer)
{
	Vertices.clear();
}