#include "wigeon/svg.h"

#include <boost/variant.hpp>

#include <string>
#include <sstream>


namespace wigeon {

namespace svg {

Properties& Properties::add(std::string name, std::string value) {
  properties.insert(Item(name, value));
  return *this;
}

namespace {

template<typename T>
void print_argument(std::ostream& f, const std::string& name, const T& value) {
  f << " " << name << "=\"" << value << "\"";
}

} // anonymous namespace

void print_header(std::ostream& f, const Properties& properties) {
  f << "<svg";
  print_argument(f, "version", "1.1");
  print_argument(f, "xmlns", "http://www.w3.org/2000/svg");
  for (auto property: properties.properties) {
    print_argument(f, property.first, property.second);
  }
  f << ">";
}

void print_footer(std::ostream& f) {
  f << "</svg>\n";
}

void print(std::ostream& f, const LineSegment2D& segment, const Properties& properties) {
  f << "<line";
  for (auto property: properties.properties) {
    print_argument(f, property.first, property.second);
  }
  print_argument(f, "x1", segment.x0());
  print_argument(f, "y1", segment.y0());
  print_argument(f, "x2", segment.x1());
  print_argument(f, "y2", segment.y1());
  f << "/>";
}

void print(std::ostream& f, const Circle2D& circle, const Properties& properties) {
  f << "<circle";
  for (auto property: properties.properties) {
    print_argument(f, property.first, property.second);
  }
  print_argument(f, "cx", circle.center().x());
  print_argument(f, "cy", circle.center().y());
  print_argument(f, "r", circle.radius());
  f << "/>";
}

void print(std::ostream& f, const Triangle2D& triangle, const Properties& properties) {
  print(f, Polygon2D(triangle), properties);
}

void print(std::ostream& f, const Rectangle2D& rectangle, const Properties& properties) {
  f << "<rect";
  for (auto property: properties.properties) {
    print_argument(f, property.first, property.second);
  }
  print_argument(f, "x", rectangle.point01().x());
  print_argument(f, "y", rectangle.point01().y());
  print_argument(f, "width", rectangle.width());
  print_argument(f, "height", rectangle.height());
  f << "/>";
}

void print(std::ostream& f, const Polygon2D& polygon, const Properties& properties) {
  f << "<polygon";
  for (auto property: properties.properties) {
    print_argument(f, property.first, property.second);
  }
  f << " points=\"";
  for (auto it=polygon.points.begin(); it!=polygon.points.end(); ++it) {
    f << it->x() << "," << it->y();
    if (it != --polygon.points.end())
      f << " ";
  }
  f << "\"/>";
}

void print(std::ostream& f, const PolyLine2D& polyline, const Properties& properties) {
  f << "<polyline";
  for (auto property: properties.properties) {
    print_argument(f, property.first, property.second);
  }
  f << " points=\"";
  for (auto it=polyline.points.begin(); it!=polyline.points.end(); ++it) {
    f << it->x() << "," << it->y();
    if (it != --polyline.points.end())
      f << " ";
  }
  f << "\"/>";
}

void print(std::ostream& f, const Area2D& area,
           const Properties& exterior_properties,
           const Properties& interior_properties) {
  f << "<g";
  print_argument(f, "id", "exterior");
  for (auto property: exterior_properties.properties) {
    print_argument(f, property.first, property.second);
  }
  f << ">"  << std::endl;
  for (auto it=area.exterior_curves.begin(); it!=area.exterior_curves.end(); ++it) {
    print(f, *it);
    f << std::endl;
  }
  f << "</g>" << std::endl;

  f << "<g";
  print_argument(f, "id", "interior");
  for (auto property: interior_properties.properties) {
    print_argument(f, property.first, property.second);
  }
  f << ">"  << std::endl;
  for (auto it=area.interior_curves.begin(); it!=area.interior_curves.end(); ++it) {
    print(f, *it);
    f << std::endl;
  }
  f << "</g>";
}

namespace {

class print_visitor : public boost::static_visitor<> {
  public:
    print_visitor(std::ostream& os, const Properties& properties)
        : os(os), properties(properties) {}

    template <typename T>
    void operator()(const T& object) {
      print(os, object, properties);
    }

    std::ostream& os;
    const Properties& properties;
};

} // anonymous namespace

void print(std::ostream& f, const PlotObject2D& obj, const Properties& properties) {
  print_visitor visitor(f, properties);
  obj.apply_visitor(visitor);
}

void print(std::ostream& f, const PlotObjects2D& obj, const Properties& properties) {
  f << "<g>"  << std::endl;
  for (auto it=obj.begin(); it!=obj.end(); ++it) {
    f << "  ";
    print(f, *it, properties);
    f << std::endl;
  }
  f << "</g>";
}

} // namespace svg

} // namespace wigeon
