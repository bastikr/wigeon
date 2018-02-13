#include "wigeon/binarytree2d.h"

#include <algorithm>


namespace wigeon {

void BinaryTree::expand_boundingbox(const BoundingBox2D& bbox) {
  if (!boundingbox) {
    boundingbox = std::unique_ptr<BoundingBox2D>(new BoundingBox2D(bbox));
  } else {
    boundingbox = std::unique_ptr<BoundingBox2D>(new BoundingBox2D(combine(*boundingbox, bbox)));
  }
}

void BinaryTree::set_subboundingboxes() {
  Point2D origin = max_boundingbox->origin();
  double width = max_boundingbox->width();
  double height = max_boundingbox->height();

  if (width > height) {
    max_boundingbox0 = std::shared_ptr<BoundingBox2D>(new BoundingBox2D(origin - Vector2D(width/8, 0), 0.75*width, height));
    max_boundingbox1 = std::shared_ptr<BoundingBox2D>(new BoundingBox2D(origin + Vector2D(width/8, 0), 0.75*width, height));
  } else {
    max_boundingbox0 = std::shared_ptr<BoundingBox2D>(new BoundingBox2D(origin - Vector2D(0, height/8), width, 0.75*height));
    max_boundingbox1 = std::shared_ptr<BoundingBox2D>(new BoundingBox2D(origin + Vector2D(0, height/8), width, 0.75*height));
  }
}

bool BinaryTree::create_node0() {
  if (node0)
    return true;

  if (max_boundingbox0->area() < min_area)
    return false;

  node0 = std::unique_ptr<BinaryTree>(new BinaryTree(max_boundingbox0, min_area));
  return true;
}

bool BinaryTree::create_node1() {
  if (node1)
    return true;

  if (max_boundingbox1->area() < min_area)
    return false;

  node1 = std::unique_ptr<BinaryTree>(new BinaryTree(max_boundingbox1, min_area));
  return true;
}

bool BinaryTree::insert(size_t id, const BoundingBox2D& bbox) {
  if (!within(bbox, *max_boundingbox))
    return false;
  if (within(bbox, *max_boundingbox0) && create_node0()) {
    node0->insert(id, bbox);
    expand_boundingbox(bbox);
    return true;
  }
  if (within(bbox, *max_boundingbox1)  && create_node1()) {
    node1->insert(id, bbox);
    expand_boundingbox(bbox);
    return true;
  }
  expand_boundingbox(bbox);
  objects[id] = std::unique_ptr<BoundingBox2D>(new BoundingBox2D(bbox));
  return true;
}

void BinaryTree::find(std::vector<int>& results, const BoundingBox2D& bbox) const {
  if (boundingbox && !overlap(bbox, *boundingbox))
    return;
  for (auto& object: objects) {
    if (overlap(bbox, *object.second))
      results.push_back(object.first);
  }
  if (node0)
    node0->find(results, bbox);
  if (node1)
    node1->find(results, bbox);
}

std::vector<int> BinaryTree::find(const BoundingBox2D& bbox) const {
  std::vector<int> results;
  find(results, bbox);
  return results;
}

} // namespace wigeon
