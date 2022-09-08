#ifndef ARMORIAL_COMMON_WIDGETS_FIELDVIEW_H
#define ARMORIAL_COMMON_WIDGETS_FIELDVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QMutex>
#include <QMouseEvent>

#include <Armorial/Geometry/Arc/Arc.h>

#include <Armorial/Common/Enums/Enums.h>
#include <Armorial/Common/Types/Field/Field.h>
#include <Armorial/Common/Types/Traits/Traits.h>
#include <Armorial/Common/Widgets/GLText/GLText.h>

#include <Armorial/Utils/Utils.h>

namespace Common {
namespace Widgets {

    /*!
     * \brief The Common::Widgets::FieldView class provides a QOpenGLWidget override that allows to display a field
     * and a lot of drawing methods using OpenGL.
     */
    class FieldView : public QOpenGLWidget
    {
        Q_OBJECT
    public:
        FieldView(const Common::Types::Field& field, const QString& centralLogoPath = "", QWidget *parent = nullptr);

    protected:
        /*!
         * \brief Override of QOpenGLWidget::initializeGL method that initialize the display lists of robots and ball.
         */
        void initializeGL();

        /*!
         * \brief Override of QOpenGLWidget::paintGL method to draw the field objects.
         */
        void paintGL();

        /*!
         * \brief Override of QOpenGLWidget::mousePressEvent method to handle field view changes.
         */
        void mousePressEvent(QMouseEvent* event);

        /*!
         * \brief Override of QOpenGLWidget::mouseReleaseEvent method to handle field view changes.
         */
        void mouseReleaseEvent(QMouseEvent* event);

        /*!
         * \brief Override of QOpenGLWidget::mouseMoveEvent method to handle field view changes.
         */
        void mouseMoveEvent(QMouseEvent* event);

        /*!
         * \brief Override of QOpenGLWidget::wheelEvent method to handle field zoom changes.
         */
        void wheelEvent(QWheelEvent* event);

        /*!
         * \brief Override of QOpenGLWidet::resizeGL method to handle window resizes.
         * \param width The new window width.
         * \param height The new window height.
         */
        void resizeGL(int width, int height);

        /*!
         * \brief Virtual function that allows Common::Widgets::FieldView implementations to setup which
         * elements they want to draw on the screen.
         * \note By default this implementation draws the field lines and the central logo (if it is set).
         */
        virtual void draw();

        /*!
         * \brief Draw a triangle.
         * \param v1, v2, v3 The vertices of the triangle.
         * \param z The z value where the triangle will be drawed at.
         * \note You need to call this method in the scope of the paintGL() or draw() methods.
         */
        template <typename T>
        std::enable_if_t<Common::Types::has_coordinates_v<T>, void> drawTriangle(const T &v1, const T &v2, const T &v3, const float &z) {
            glBegin(GL_TRIANGLES);
            glVertex3d(v1.x(), v1.y(), z);
            glVertex3d(v2.x(), v2.y(), z);
            glVertex3d(v3.x(), v3.y(), z);
            glEnd();
        }

        /*!
         * \brief Draw a rectangle.
         * \param topLeft, bottomRight The position of the topLeft and bottomRight corners.
         * \param z The z value where the rectangle will be drawed at.
         * \note You need to call this method in the scope of the paintGL() or draw() methods.
         */
        template <typename T>
        std::enable_if_t<Common::Types::has_coordinates_v<T>, void> drawRect(const T &topLeft, const T &bottomRight, const float &z) {
            glBegin(GL_QUADS);
            glVertex3d(topLeft.x(), topLeft.y(), z);
            glVertex3d(bottomRight.x(), topLeft.y(), z);
            glVertex3d(bottomRight.x(), bottomRight.y(), z);
            glVertex3d(topLeft.x(), bottomRight.y(), z);
            glEnd();
        }

        /*!
         * \brief Draw a rectangle.
         * \param v1, v2, v3, v4 The position of the corners of the rectangle.
         * \param z The z value where the rectangle will be drawed at.
         * \note You need to call this method in the scope of the paintGL() or draw() methods.
         */
        template <typename T>
        std::enable_if_t<Common::Types::has_coordinates_v<T>, void> drawRect(const T &v1, const T &v2, const T &v3, const T &v4, const float &z) {
            glBegin(GL_QUADS);
            glVertex3d(v1.x(), v1.y(), z);
            glVertex3d(v2.x(), v2.y(), z);
            glVertex3d(v3.x(), v3.y(), z);
            glVertex3d(v4.x(), v4.y(), z);
            glEnd();
        }

        /*!
         * \brief Draw a arc.
         * \param center The position of the center which the arc will be.
         * \param r1, r2 The start and end draw radius.
         * \param theta1, theta2 The start and end angle of the arc.
         * \param z The z value where the rectangle will be drawed at.
         * \param dTheta
         * \note Using r1 and r2 parameters you can draw a "full filled" arc (r1 = 0, r2 = radius) or
         * a "partially filled" arc, e.g. (r1 = radius - 10, r2 = radius), so this will fill only a 'border'
         * on the arc.
         * \note You need to call this method in the scope of the paintGL() or draw() methods.
         */
        template <typename T>
        std::enable_if_t<Common::Types::has_coordinates_v<T>, void> drawArc(const T &center, const float &r1, const float &r2, const float &theta1, const float &theta2, const float &z, float dTheta = -1) {
            static const float tesselation = 1.0;

            if(dTheta < 0) {
                dTheta = tesselation/r2;
            }

            glBegin(GL_QUAD_STRIP);
            for(float theta = theta1; theta < theta2; theta += dTheta) {
                float c1 = cos(theta);
                float s1 = sin(theta);
                glVertex3d(r2*c1 + center.x(), r2*s1 + center.y(), z);
                glVertex3d(r1*c1 + center.x(), r1*s1 + center.y(), z);
            }

            float c1 = cos(theta2);
            float s1 = sin(theta2);
            glVertex3d(r2*c1 + center.x(), r2*s1 + center.y(), z);
            glVertex3d(r1*c1 + center.x(), r1*s1 + center.y(), z);
            glEnd();
        }

        /*!
         * \tparam T The given type of the position.
         * \tparam V The given type of the orientation.
         * \brief Draws a text with the given size and color in the given position and orientation.
         * \note The position should be passed in meters and needs to have coordinate getters (.x() and .y()) and math operators for float (+, -, *, /).
         * \note The orientation should be passed as radians and needs to be a floating point.
         */
        template<typename T, typename V>
        std::enable_if_t<Common::Types::has_coordinates_v<T> && Common::Types::has_f_math_operators_v<T> && std::is_floating_point_v<V>, void> drawText(const T& position, const V& orientation, const QString& text, const float& textSize, GLText::HAlignOptions hAlign = GLText::LeftAligned, GLText::VAlignOptions vAlign = GLText::MiddleAligned, const QColor& textColor = QColor(Qt::white)) {
            // Draw robot identifier
            _glText.drawString(position * 1000.0, Utils::Angles::radToDeg(orientation), textSize, text.toStdString().c_str(), hAlign, vAlign, textColor);
        }

        /*!
         * \tparam T The given type of the position.
         * \tparam V The given type of the orientation.
         * \brief Draws a robot using the display lists.
         * \param position, orientation The position and orientations which the robot will be drawed at.
         * \param teamColor, robotId The robot pattern parameters.
         * \note The position should be passed in meters and needs to have coordinate getters (.x() and .y()) and math operators for float (+, -, *, /).
         * \note The orientation should be passed as radians and needs to be a floating point.
         */
        template<typename T, typename V>
        std::enable_if_t<Common::Types::has_coordinates_v<T> && std::is_floating_point_v<V>, void> drawRobot(const T& position, const V& orientation, const Common::Enums::Color &teamColor, const uint8_t &robotId) {
            // Draw robot shape
            glPushMatrix();
            glLoadIdentity();
            glTranslated(position.x() * 1000.0, position.y() * 1000.0, 0);
            glRotated(Utils::Angles::radToDeg(orientation), 0, 0, _robotZ);
            glCallList(_robotShape.value(teamColor));
            glPopMatrix();

            // Draw text
            drawText(position, 0.0f, QString("%1").arg(robotId), _idSize, GLText::CenterAligned, GLText::MiddleAligned, QColor(0, 0, 0));
        }

        /*!
         * \tparam T The given type of the position.
         * \brief Draws a ball using the display lists.
         * \note The position should be passed in meters and needs to have coordinate getters (.x() and .y()).
         */
        template<typename T>
        std::enable_if_t<Common::Types::has_coordinates_v<T>, void> drawBall(const T& position) {
            glPushMatrix();
            glLoadIdentity();
            glTranslated(position.x() * 1000.0, position.y() * 1000.0, 0);
            glCallList(_ballShape);
            glPopMatrix();
        }

        /*!
         * \brief Reset the field view ratio.
         */
        void resetView();

        /*!
         * \brief Recompute the field view projection.
         */
        void recomputeProjection();

        /*!
         * \brief Setup the robot display lists for all colors (blue, yellow, undefined).
         */
        virtual void setupRobotDisplayList();

        /*!
         * \brief Setup the ball display list.
         */
        virtual void setupBallDisplayList();

        /*!
         * \brief Draw the central logo if it was defined.
         */
        virtual void drawCentralLogo(const float &centralLogoSize = 400.0);

        /*!
         * \brief setupFieldGeometry
         * \param field
         */
        void setupFieldGeometry(const Common::Types::Field &field);

        /*!
         * \brief getFieldGeometry
         * \return The set field geometry for this FieldView instance.
         */
        Common::Types::Field getFieldGeometry() { return _field; }

        /*!
         * \brief setupCentralLogo
         * \param logoPath
         */
        void setupCentralLogo(const QString& logoPath);

        /*!
         * \brief Draw the field lines using the field objects lists generated from the setupFieldGeometry method.
         */
        void drawFieldLines();

        void setupIdSize(const float& idSize) {
            _idSize = idSize;
        }

        // Display lists
        QMap<Common::Enums::Color, GLuint> _robotShape;
        GLuint _ballShape;
        int _idSize;

        // Field z value references
        static constexpr float _fieldZ = 1.0;
        static constexpr float _robotZ = 2.0;
        static constexpr float _ballZ = 3.0;
        static constexpr float _minZValue = -10.0;
        static constexpr float _maxZValue = 10.0;

    private:
        // Field view
        Common::Types::Field _field;
        float _viewScale;
        float _viewXOffset;
        float _viewYOffset;

        // Mouse events
        bool _leftButton;
        bool _midButton;
        bool _rightButton;
        int _mouseStartX;
        int _mouseStartY;

        // GLText for text rendering
        GLText _glText;

        // Field objects
        QList<Geometry::LineSegment> _fieldLineSegments;
        QList<Geometry::Circle> _fieldCircles;
        QList<Geometry::Arc> _fieldArcs;

        // Central logo
        QString _centralLogoPath;
        QOpenGLTexture *_centralLogo;

        // Mutex to control graphics
        QMutex _graphicsMutex;

    public slots:
        /*!
         * \brief Redraw slot that casts paintGL() method.
         * \note This slot should be called in a thread to enable drawings.
         */
        void redraw();

        /*!
         * \brief Redraw the field lines using a given field.
         * \param field The given field.
         * \note You should cast this slot when the geometry is sent by vision software.
         */
        void geometryChanged(const Common::Types::Field& field);
    };

}
}

#endif // ARMORIAL_COMMON_WIDGETS_FIELDVIEW_H