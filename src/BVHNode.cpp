#include "../inc/BVHNode.hpp"

BVHNode::BVHNode(std::vector<AHittable*> &objects)
{
	for (AHittable* ptr : objects)
	{
		volume.extend(ptr->boundingBox());
	}

	if (objects.size() == 1)
	{
		this->objects = objects;
	}
	else
	{
		std::vector<AHittable*> left_objs;
		std::vector<AHittable*> right_objs;
		std::sort(objects.begin(), objects.end());

		size_t cutoff = objects.size() / 2;
		left_objs.assign(objects.begin(), objects.begin() + cutoff);
		right_objs.assign(objects.begin() + cutoff, objects.end());
		left = std::make_shared<BVHNode>(left_objs);
		right = std::make_shared<BVHNode>(right_objs);
	}
}

bool	BVHNode::operator<(const BVHNode &other)
{
	return (volume < other.volume);
}

HitRecord	BVHNode::intersect(const Ray &ray) const
{
	if (volume.intersect(ray))
	{
		if (isLeaf())
			return (objects[0]->detectHit(ray));
		if (left->volume.intersect(ray))
			return (left->intersect(ray));
		if (right->volume.intersect(ray))
			return (right->intersect(ray));
	}
	return (HitRecord(NAN));
}

bool	BVHNode::isLeaf(void) const
{
	return (objects.size() == 1);
}
