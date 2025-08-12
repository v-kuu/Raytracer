#include "../inc/BVHNode.hpp"

bool	BVHNode::isLeaf(void)
{
	return (objects.size() > 0);
}
