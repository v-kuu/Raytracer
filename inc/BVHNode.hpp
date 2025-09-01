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
	std::unique_ptr<BVHNode>					left;
	std::unique_ptr<BVHNode>					right;
	std::vector<std::unique_ptr<AHittable>>		objects;

	BVHNode(std::vector<std::unique_ptr<AHittable>> &objects);

	bool	operator<(const BVHNode &other);

	void		_sortSAH(void);
	HitRecord	intersect(const Ray &ray) const;
	bool		isLeaf(void) const;
};
