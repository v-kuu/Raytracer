#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "AHittable.hpp"
#include "HitRecord.hpp"
#include "AABB.hpp"

class	AHittable;

struct	BVHNode
{
	AABB										volume;
	std::shared_ptr<BVHNode>					left;
	std::shared_ptr<BVHNode>					right;
	std::vector<std::shared_ptr<AHittable>>		objects;

	BVHNode(std::vector<std::shared_ptr<AHittable>> &objects);

	bool	operator<(const BVHNode &other);

	HitRecord	intersect(const Ray &ray) const;
	bool		isLeaf(void) const;
};
