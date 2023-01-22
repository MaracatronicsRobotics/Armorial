#ifndef ARMORIAL_GEOMETRY_POLYGON_H
#define ARMORIAL_GEOMETRY_POLYGON_H

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/LineSegment/LineSegment.h>

namespace Geometry {
    /*!
     * \brief The Geometry::Polygon class provides a interface that describe polygon objects in the field.
     */
    class Polygon
    {
    public:
        /*!
         * \brief Geometry::Polygon default constructor.
         */
        Polygon() = default;

        /*!
         * \brief Geometry::Polygon constructor that receives a given list of vertices.
         * \param vertices The given list of vertices.
         */
        Polygon(const std::vector<Vector2D> &vertices);

        /*!
         * \brief Insert a vertice in the list of vertices.
         * \param vertice The given vertice.
         */
        void insertVertice(const Vector2D &vertice);

        /*!
         * \brief Remove a vertice from the list of vertices.
         * \param Index of the vertice to remove in the list.
         */
        void removeVertice(const int index);

        /*!
         * \return The list of vertices that defines this polygon.
         */
        std::vector<Vector2D> vertices() const;

        /*!
         * \brief Move all the vertices by a given amount.
         * \param dir The given amount.
         */
        void move(const Vector2D &amount);

        /*!
         * \brief Computes the centroid of this polygon instance.
         * \return The centroid of polygon represented by a Vector2D.
         */
        [[nodiscard]] Vector2D centroid() const;

        /*!
         * \brief Descbribes the operator [] that returns the vertice at the index \ref id
         * \param id The given id.
         * \return The vertice at the index \ref id.
         */
        [[nodiscard]] Vector2D operator[](size_t id) const;

        /*!
         * \return The amount of vertices that belongs to this polygon.
         */
        [[nodiscard]] size_t amountOfVertices() const;

        /*!
         * \return A list that contains all the line segments that forms the boundary.
         */
        [[nodiscard]] std::vector<LineSegment> boundary() const;

        /*!
         * \return The perimeter length for this polygon instance.
         */
        [[nodiscard]] float perimeterLength() const;

        /*!
         * \brief Computes if this polygon instance defines a convex hull.
         * \return True if this polygon is convex and False otherwise.
         */
        [[nodiscard]] bool isConvex() const;

        /*!
         * \brief Check if this polygon contains a given point.
         * \param point The given point.
         * \return True if this polygon contains the given point and False otherwise.
         */
        [[nodiscard]] bool contains(const Vector2D &point) const;

        /*!
         * \brief Check if the boundary of this polygon contains a given point.
         * \param point The given point.
         * \return True if the boundary of this polygon contains the given point and False otherwise.
         */
        [[nodiscard]] bool isOnBoundary(const Vector2D &point) const;

        /*!
         * \brief Check if this polygon intersect a given line segment.
         * \param lineSegment The given line segment.
         * \return True if this polygon intersects a given line segment and False otherwise.
         */
        [[nodiscard]] bool doesIntersect(const LineSegment &lineSegment) const;

        /*!
         * \brief Compute the intersection points of this polygon with a given line segment.
         * \param lineSegment The given line segment.
         * \return A list containing the points which this polygon intersects with the given line segment.
         */
        [[nodiscard]] std::vector<Vector2D> getIntersections(const LineSegment &lineSegment) const;

        /*!
         * \brief Computes the area of this polygon using Shoelace formula.
         * \return The computed area of this polygon.
         * \note This method should not work properly for complex polygons.
         */
        [[nodiscard]] float area() const;

        /*!
         * \brief Check if this polygon instance is a simple polygon (its boundary does not intersect with each other)
         * \return True if this polygon is simple and False otherwise.
         * \note This method use a O(n²) approach.
         */
        bool isSimple() const;

    private:
        std::vector<Vector2D> _vertices;
    };
}

#endif // ARMORIAL_GEOMETRY_POLYGON_H
