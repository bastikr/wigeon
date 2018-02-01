#pragma once

#include <string>
#include <sstream>

#include <boost/variant.hpp>

#include "wigeon/linesegment2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/collections.h"


namespace wigeon {

namespace svg {

void print_header(std::ostream&, double width, double height);
void print_footer(std::ostream&);
void print(std::ostream&, const LineSegment2D&);
void print(std::ostream&, const Circle2D&);
void print(std::ostream&, const Triangle2D&);
void print(std::ostream&, const Rectangle2D&);
void print(std::ostream&, const Polygon2D&);
void print(std::ostream&, const PolyLine2D&);


class print_visitor : public boost::static_visitor<> {
  public:
    print_visitor(std::ostream& os) : os(os) {}

    template <typename T>
    void operator()(const T& object) {
      print(os, object);
    }

    std::ostream& os;
};

void print(std::ostream&, const PlotObject2D&);
void print(std::ostream&, const PlotObjects2D&);

template<typename T>
std::string print(const T object) {
  std::stringstream f;
  print(f, object);
  return f.str();
}

} // namespace svg

} // namespace wigeon
