#include "wigeon/svg.h"

#include <string>
#include <sstream>


namespace wigeon {

namespace svg {

namespace {

template<typename T>
void print_argument(std::ostream& f, const std::string& name, const T& value) {
  f << " " << name << "=\"" << value << "\"";
}

} // anonymous namespace

void print_header(std::ostream& f, double width, double height) {
  f << "<svg";
  print_argument(f, "width", width);
  print_argument(f, "height", height);
  print_argument(f, "version", "1.1");
  print_argument(f, "xmlns", "http://www.w3.org/2000/svg");
  f << ">";
}

void print_footer(std::ostream& f) {
  f << "</svg>\n";
}

void print(std::ostream& f, const LineSegment2D& segment) {
  f << "<line";
  print_argument(f, "x1", segment.x0());
  print_argument(f, "y1", segment.y0());
  print_argument(f, "x2", segment.x1());
  print_argument(f, "y2", segment.y1());
  f << "/>";
}

void print(std::ostream& f, const Circle2D& circle) {
  f << "<circle";
  print_argument(f, "cx", circle.center().x());
  print_argument(f, "cy", circle.center().y());
  print_argument(f, "cx", circle.radius());
  f << "/>";
}

void print(std::ostream& f, const Triangle2D& triangle) {
  print(f, Polygon2D(triangle));
}

void print(std::ostream& f, const Rectangle2D& rectangle) {
  f << "<rect";
  print_argument(f, "x", rectangle.point01().x());
  print_argument(f, "y", rectangle.point01().y());
  print_argument(f, "width", rectangle.width());
  print_argument(f, "height", rectangle.height());
  f << "/>";
}

void print(std::ostream& f, const Polygon2D& polygon) {
  f << "<polygon points=\"";
  for (auto it=polygon.points.begin(); it!=polygon.points.end(); ++it) {
    f << it->x() << "," << it->y();
    if (it != --polygon.points.end())
      f << " ";
  }
  f << "\"/>";
}

void print(std::ostream& f, const PolyLine2D& polyline) {
  f << "<polyline points=\"";
  for (auto it=polyline.points.begin(); it!=polyline.points.end(); ++it) {
    f << it->x() << "," << it->y();
    if (it != --polyline.points.end())
      f << " ";
  }
  f << "\"/>";
}

void print(std::ostream& f, const PlotObject2D& obj) {
  print_visitor printer(f);
  obj.apply_visitor(printer);
}

void print(std::ostream& f, const PlotObjects2D& obj) {
  f << "<g>"  << std::endl;
  for (auto it=obj.begin(); it!=obj.end(); ++it) {
    f << "  ";
    print(f, *it);
    f << std::endl;
  }
  f << "</g>";
}

} // namespace svg

} // namespace wigeon
