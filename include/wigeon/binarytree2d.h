#pragma once

#include <memory>
#include <map>

#include "wigeon/collections.h"
#include "wigeon/within.h"


namespace wigeon {

using LeafObjects = std::map<int, std::unique_ptr<BoundingBox2D>>;


class BinaryTree {
  public:
    BinaryTree(std::shared_ptr<BoundingBox2D> max_boundingbox, double min_area)
        : min_area(min_area), max_boundingbox(max_boundingbox) {set_subboundingboxes();}

    BinaryTree(const BoundingBox2D& max_boundingbox, double min_area)
        : min_area(min_area), max_boundingbox(new BoundingBox2D(max_boundingbox)) {set_subboundingboxes();}

    void expand_boundingbox(const BoundingBox2D&);
    void set_subboundingboxes();

    bool create_node0();
    bool create_node1();

    bool insert(size_t id, const BoundingBox2D& bbox);

    void find(std::vector<int>& results, const BoundingBox2D& bbox) const;
    std::vector<int> find(const BoundingBox2D& bbox) const;

    double min_area;
    std::unique_ptr<BoundingBox2D> boundingbox;
    std::shared_ptr<BoundingBox2D> max_boundingbox;

    std::unique_ptr<BinaryTree> node0;
    std::unique_ptr<BinaryTree> node1;
    std::shared_ptr<BoundingBox2D> max_boundingbox0;
    std::shared_ptr<BoundingBox2D> max_boundingbox1;
    LeafObjects objects;
};

} // namespace wigeon
