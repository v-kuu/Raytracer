#include "../inc/BVHNode.hpp"

BVHNode::BVHNode(std::vector<std::unique_ptr<AHittable>> &objects)
{
	for (std::unique_ptr<AHittable> &ptr : objects)
	{
		volume.extend(ptr->boundingBox());
	}

	if (objects.size() == 1)
	{
		this->objects = std::move(objects);
	}
	else
	{
		std::vector<std::unique_ptr<AHittable>> left_objs;
		std::vector<std::unique_ptr<AHittable>> right_objs;
		std::sort(objects.begin(), objects.end());

		size_t cutoff = objects.size() / 2;
		left_objs.assign(
				std::make_move_iterator(objects.begin()),
				std::make_move_iterator(objects.begin() + cutoff));
		right_objs.assign(
				std::make_move_iterator(objects.begin() + cutoff),
				std::make_move_iterator(objects.end()));
		left = std::make_unique<BVHNode>(left_objs);
		right = std::make_unique<BVHNode>(right_objs);
	}
}

bool	BVHNode::operator<(const BVHNode &other)
{
	return (volume < other.volume);
}

HitRecord	BVHNode::intersect(const Ray &ray) const
{
	HitRecord	closest(std::numeric_limits<float>::max());

	if (volume.intersect(ray))
	{
		if (isLeaf())
		{
			HitRecord hit = objects[0]->detectHit(ray);
			return (hit);
		}
		if (left->volume.intersect(ray))
		{
			HitRecord hit = left->intersect(ray);
			if (hit.t < closest.t && hit.t >= 0)
				closest = hit;
		}
		if (right->volume.intersect(ray))
		{
			HitRecord hit = right->intersect(ray);
			if (hit.t < closest.t && hit.t >= 0)
				closest = hit;
		}
	}
	return (closest);
}

bool	BVHNode::isLeaf(void) const
{
	return (objects.size() == 1);
}
