#pragma once

#include <string>
#include <sstream>

#include "wigeon/circle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/polygon2d.h"


namespace wigeon {

namespace svg {

void print_header(std::ostream&, double width, double height);
void print_footer(std::ostream&);
void print(std::ostream&, const Circle2D&);
void print(std::ostream&, const Rectangle2D&);
void print(std::ostream&, const LineSegment2D&);
void print(std::ostream&, const Polygon2D&);

template<typename T>
std::string print(const T object) {
  std::stringstream f;
  print(f, object);
  return f.str();
}

} // namespace svg

} // namespace wigeon
