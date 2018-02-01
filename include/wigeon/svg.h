#pragma once

#include <map>
#include <string>
#include <sstream>

#include "wigeon/linesegment2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/collections.h"


namespace wigeon {

namespace svg {

struct Properties {
  using Item = std::pair<std::string, std::string>;

  Properties& add(std::string name, std::string value);

  std::map<std::string, std::string> properties;
};

void print_header(std::ostream&, const Properties& = Properties());
void print_footer(std::ostream&);
void print(std::ostream&, const LineSegment2D&, const Properties& = Properties());
void print(std::ostream&, const Circle2D&, const Properties& = Properties());
void print(std::ostream&, const Triangle2D&, const Properties& = Properties());
void print(std::ostream&, const Rectangle2D&, const Properties& = Properties());
void print(std::ostream&, const Polygon2D&, const Properties& = Properties());
void print(std::ostream&, const PolyLine2D&, const Properties& = Properties());
void print(std::ostream&, const PlotObject2D&, const Properties& = Properties());
void print(std::ostream&, const PlotObjects2D&, const Properties& = Properties());

template<typename T>
std::string print(const T object, const Properties& properties = Properties()) {
  std::stringstream f;
  print(f, object, properties);
  return f.str();
}

} // namespace svg

} // namespace wigeon
