#pragma once
#include <vector>
#include <memory>
#include "AHittable.hpp"
#include "AABB.hpp"

struct	BVHNode
{
	AABB						volume;
	std::shared_ptr<BVHNode>	left;
	std::shared_ptr<BVHNode>	right;
	std::vector<AHittable*>		objects;

	bool	isLeaf(void);
};
