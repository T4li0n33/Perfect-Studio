#pragma once
#include <glm/fwd.hpp>
#include <iostream>
#include "DrawFunctions.h"

class SceneSelector
{
	//void CheckDoubleClick();
public:
	struct RayHitInfo {
		std::string ElemID;
		glm::vec3 Normal;    // opcjonalnie: wektor normalny powierzchni
		glm::vec3 HitPoint;  // opcjonalnie: miejsce trafienia
		glm::vec3 MaxBox;
		glm::vec3 MinBox;
	};
	bool RayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& min, const glm::vec3& max);
	bool CheckRayHit(const glm::vec3& rayOrigin, const glm::vec3& rayDir, Structure& structure, RayHitInfo* outHitInfo, std::vector<Structure::Vertex>& globalVertices);
	void GetAABB(const Structure& s, glm::vec3& outMin, glm::vec3& outMax);
	bool IsNewPositionSelected(glm::vec3 position);
	bool CheckRayTriangleIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDir, Structure& structure, std::vector<Structure::Vertex>& globalVertices, RayHitInfo* outHitInfo = nullptr);
	glm::vec3 CalculatePlacementOnFace(const glm::vec3& minBox, const glm::vec3& maxBox, const glm::vec3& rayDir, const char* FatherStructureRotation, Structure& newStructure, const RayHitInfo& hitInfo);
};

