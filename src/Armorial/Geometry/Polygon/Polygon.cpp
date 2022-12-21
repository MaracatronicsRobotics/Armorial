#include <Armorial/Geometry/Polygon/Polygon.h>

#include <Armorial/Utils/Utils.h>

#include <algorithm>
#include <math.h>

using namespace Geometry;

Polygon::Polygon(const std::vector<Vector2D> &vertices) {
    _vertices = vertices;
}

void Polygon::insertVertice(const Vector2D &vertice) {
    _vertices.push_back(vertice);
}

std::vector<Vector2D> Polygon::vertices() const {
    return _vertices;
}

void Polygon::move(const Vector2D &amount) {
    for (auto &vertex : vertices()) {
        vertex += amount;
    }
}

Vector2D Polygon::centroid() const {
    size_t sz_vertices = amountOfVertices();
    Vector2D sum = {0.0, 0.0};
    for(size_t i = 0; i < sz_vertices; i++) {
        sum += (_vertices[i] + _vertices[(i + 1) % sz_vertices]) * _vertices[i].crossProduct(_vertices[(i + 1) % sz_vertices]);
    }

    return (sum /= (6.0 * area()));
}

Vector2D Polygon::operator[](size_t id) const {
    return _vertices[id];
}

size_t Polygon::amountOfVertices() const {
    return _vertices.size();
}

std::vector<LineSegment> Polygon::boundary() const {
    std::vector<LineSegment> boundary;
    size_t sz_vertices = amountOfVertices();
    for (size_t i = 0; i < sz_vertices; i++) {
        boundary.push_back({_vertices[i], _vertices[(i + 1) % sz_vertices]});
    }

    return boundary;
}

float Polygon::perimeterLength() const {
    float length = 0;
    std::vector<LineSegment> polygonBoundary = boundary();

    for (auto &ls : polygonBoundary) {
        length += ls.length();
    }

    return length;
}

bool Polygon::isConvex() const {
    // Base case (triangles)
    if (amountOfVertices() < 4) return true;

    bool sign = false;
    bool signSet = false;
    int sz_vertices = amountOfVertices();
    for (int i = 0; i < sz_vertices; i++) {
        Vector2D d1 = _vertices[(i + 2) % sz_vertices] - _vertices[(i + 1) % sz_vertices];
        Vector2D d2 = _vertices[i] - _vertices[(i + 1) % sz_vertices];
        float cross = d1.crossProduct(d2);

        // on a crossproduct of zero the points lie in one line and we can simply ignore this point's contribution to the convexity
        if (!Utils::Compare::isEqual(cross, 0.0f)) {
            if (!signSet) {
                signSet = true;
                sign = cross > 0;
            }
            else if (sign != (cross > 0)) {
                return false;
            }
        }
    }

    return true;
}

bool Polygon::contains(const Vector2D &point) const {
    int c = 0;
    int sz_vertices = amountOfVertices();
    for (int i = 0, j = sz_vertices - 1; i < sz_vertices; j = i++) {
        if (((_vertices[i].y() > point.y()) != (_vertices[j].y() > point.y())) &&
            (point.x() < (_vertices[j].x() - _vertices[i].x()) * (point.y() - _vertices[i].y()) / (_vertices[j].y() - _vertices[i].y()) + _vertices[i].x()))
            c = !c;
    }

    return c;
}

bool Polygon::isOnBoundary(const Vector2D &point) const {
    std::vector<LineSegment> polygonBoundary = boundary();

    for(auto &ls : polygonBoundary) {
        if(ls.isOnLine(point)) {
            return true;
        }
    }

    return false;
}

bool Polygon::doesIntersect(const LineSegment &lineSegment) const {
    std::vector<LineSegment> polygonBoundary = boundary();

    for(auto &ls : polygonBoundary) {
        if(lineSegment.doesIntersect(ls)) {
            return true;
        }
    }

    return false;
}

std::vector<Vector2D> Polygon::getIntersections(const LineSegment &lineSegment) const {
    std::vector<Vector2D> intersections;
    std::vector<LineSegment> polygonBoundary = boundary();

    for (auto &ls : polygonBoundary) {
        std::vector<Vector2D> segmentIntersections = lineSegment.intersects(ls);
        intersections.insert(intersections.end(), segmentIntersections.begin(), segmentIntersections.end());
    }

    std::sort(intersections.begin(), intersections.end());
    intersections.erase(std::unique(intersections.begin(), intersections.end()), intersections.end());
    return intersections;
}

float Polygon::area() const {
    float areaSum = 0.0;
    size_t sz_vertices = amountOfVertices();
    for(size_t i = 0; i < sz_vertices; i++) {
        areaSum += _vertices[i].crossProduct(_vertices[(i + 1) % sz_vertices]);
    }

    return (0.5 * fabs(areaSum));
}

bool Polygon::isSimple() const {
    std::vector<LineSegment> lines;
    size_t numberIntersections = 0;
    for (auto first = _vertices.begin(); first != _vertices.end(); first++) {
        std::optional<LineSegment> boundarySegment;
        if (first == std::prev(_vertices.end())) {
            boundarySegment = LineSegment(*first, _vertices[0]);
        } else {
            boundarySegment = LineSegment(*first, *(first + 1));
        }

        for (auto const &line : lines) {
            numberIntersections += boundarySegment.value().intersects(line).size();
        }

        lines.push_back(boundarySegment.value());
    }

    // If the polygon is not simple, it will intersect more than in the corners.
    return numberIntersections == amountOfVertices();
}
