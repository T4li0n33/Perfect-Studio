#pragma once
#include <glm/fwd.hpp>
#include "DrawFunctions.h"
class SceneSelector
{
	//void CheckDoubleClick();
public:
	bool RayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& min, const glm::vec3& max);
	bool CheckRayHit(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const Structure& structure);
	void GetAABB(const Structure& s, glm::vec3& outMin, glm::vec3& outMax);
	bool IsNewPositionSelected(glm::vec3 position);
	glm::vec3 CalculatePlacementOnFace(const glm::vec3& minBox, const glm::vec3& maxBox, const glm::vec3& rayDir);
	PlacementDirection GetPlacementDirection(const glm::vec3& rayDir);
};

