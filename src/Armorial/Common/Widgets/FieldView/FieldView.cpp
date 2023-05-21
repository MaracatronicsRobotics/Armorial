#include <Armorial/Common/Widgets/FieldView/FieldView.h>

#include <spdlog/spdlog.h>

#define FIELD_COLOR 0.0,0.0,0.0,1.0
#define FIELD_LINES_COLOR 1.0,1.0,1.0,1.0
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace Common::Widgets;

FieldView::FieldView(const Common::Types::Field &field, const QString &centralLogoPath, QWidget *parent) : QOpenGLWidget(parent), _field(field) {
    // Set format
    QSurfaceFormat format;
    format.setDepthBufferSize(32);
    format.setSamples(16);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    this->setFormat(format);

    // Setup central logo path
    _centralLogoPath = centralLogoPath;

    // Setup field geometry
    setupFieldGeometry(field);

    // Setup central logo texture as nullptr
    _centralLogo = nullptr;

    // Setup default id size
    _idSize = 100;
}

void FieldView::setupFieldGeometry(const Common::Types::Field &field) {
    // Setup _field
    _field = field;

    // Get field constraints
    const float fieldLength = field.length();
    const float fieldWidth = field.width();
    const float goalDepth = field.goalDepth();
    const float goalWidth = field.goalWidth();

    // Cleanup lists
    _fieldLineSegments.clear();
    _fieldCircles.clear();
    _fieldArcs.clear();

    // Set field center circle
    _fieldCircles.push_back(field.centerCircle());

    // Create field rectangle
    Geometry::Rectangle fieldRect = field.field();
    std::vector<Geometry::LineSegment> fieldLines = fieldRect.boundary();
    for(auto &ls : fieldLines) {
        _fieldLineSegments.push_back(ls);
    }

    // Create left goal defense area rectangle
    Geometry::Rectangle leftPenaltyArea = field.leftPenaltyArea();
    std::vector<Geometry::LineSegment> leftPenaltyAreaLines = leftPenaltyArea.boundary();
    for(auto &ls : leftPenaltyAreaLines) {
        _fieldLineSegments.push_back(ls);
    }

    // Create right goal defense area rectangle
    Geometry::Rectangle rightPenaltyArea = field.rightPenaltyArea();
    std::vector<Geometry::LineSegment> rightPenaltyAreaLines = rightPenaltyArea.boundary();
    for(auto &ls : rightPenaltyAreaLines) {
        _fieldLineSegments.push_back(ls);
    }

    // Create left goal area
    Geometry::Rectangle leftGoal({-fieldLength/2.0f - goalDepth, goalWidth/2.0f}, {-fieldLength/2.0f, -goalWidth/2.0f});
    std::vector<Geometry::LineSegment> leftGoalLines = leftGoal.boundary();
    for(auto &ls : leftGoalLines) {
        _fieldLineSegments.push_back(ls);
    }

    // Create right goal area
    Geometry::Rectangle rightGoal({fieldLength/2.0f, goalWidth/2.0f}, {fieldLength/2.0f + goalDepth, -goalWidth/2.0f});
    std::vector<Geometry::LineSegment> rightGoalLines = rightGoal.boundary();
    for(auto &ls : rightGoalLines) {
        _fieldLineSegments.push_back(ls);
    }

    // Setup field quadrant lines
    _fieldLineSegments.push_back(Geometry::LineSegment({-fieldLength/2.0f, 0.0}, {fieldLength/2.0f, 0.0}));
    _fieldLineSegments.push_back(Geometry::LineSegment({0.0, fieldWidth/2.0f}, {0.0, -fieldWidth/2.0f}));
}

void FieldView::setupCentralLogo(const QString &logoPath) {
    // Initialize central logo texture
    _centralLogo = new QOpenGLTexture(QImage(logoPath));
    _centralLogo->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _centralLogo->setMagnificationFilter(QOpenGLTexture::Linear);
}

void FieldView::setupRobotDisplayList() {
    magic_enum::enum_for_each<Common::Enums::Color>([this] (auto color) {
        // Check if key for color is already registered
        if(!_robotShape.keys().contains(color)) {
            _robotShape.insert(color, GL_INVALID_VALUE);
        }

        // Check if robot shape was been already set and delete if True
        if(_robotShape.value(color) != GL_INVALID_VALUE) {
            glDeleteLists(_robotShape.value(color), 1);
        }

        // Generate a display list
        _robotShape.insert(color, glGenLists(1));
        if(_robotShape.value(color) == GL_INVALID_VALUE) {
            spdlog::error("Failed to create robot shape display list.");
        }

        // Draw in the display list
        glNewList(_robotShape.value(color), GL_COMPILE);

        // Setup color for internal shape
        if(color == Common::Enums::Color::BLUE)        glColor3d(0.2549, 0.4941, 1.0);
        else if(color == Common::Enums::Color::YELLOW) glColor3d(1.0, 0.9529, 0.2431);
        else                                           glColor3d(0.5882,0.5882,0.5882);

        // Drawing triangle (robot front)
        float theta1 = 40.0*(M_PI/180.0);
        float theta2 = 2.0*M_PI - theta1;
        drawTriangle(QVector2D(0, 0), QVector2D(90.0*cos(theta1), 90.0*sin(theta1)),
                     QVector2D(90.0*cos(theta2), 90.0*sin(theta2)), _robotZ);
        drawArc(QVector2D(0, 0), 0, 90, theta1, theta2, _robotZ);

        // Setup color for body
        if(color == Common::Enums::Color::BLUE)        glColor3d(0.0706, 0.2314, 0.6275);
        else if(color == Common::Enums::Color::YELLOW) glColor3d(0.8, 0.6157, 0.0);
        else                                           glColor3d(0.2745,0.2745,0.2745);

        // Draw robot body
        drawArc(QVector2D(0, 0), 80, 90, theta1, theta2, _robotZ + 0.01);
        drawRect(QVector2D(90.0 * cos(theta1)-10, 90.0 * sin(theta1)),
                 QVector2D(90.0 * cos(theta2), 90.0 * sin(theta2)), _robotZ + 0.01);

        // Setup color for wheels
        glColor3d(0.5, 0.5, 0.5);

        // Draw robot wheels
        drawRect(QVector2D(90.0*cos(theta1), 90.0*sin(theta1)),
                 QVector2D(90.0*cos(theta1) + 3.5, 90.0*sin(theta1) + 3.5),
                 QVector2D(90.0*cos(theta1 + (M_PI/6)), 90.0*sin(theta1 + (M_PI/6))),
                 QVector2D(90.0*cos(theta1 + (M_PI/6)) + 3.5, 90.0*sin(theta1 + (M_PI/6)) + 3.5),
                 _robotZ + 0.02);

        drawRect(QVector2D(-90.0*cos(theta1), 90.0*sin(theta1)),
                 QVector2D(-90.0*cos(theta1) - 3.5, 90.0*sin(theta1) + 3.5),
                 QVector2D(-90.0*cos(theta1 + (M_PI/6)), 90.0*sin(theta1 + (M_PI/6))),
                 QVector2D(-90.0*cos(theta1 + (M_PI/6)) - 3.5, 90.0*sin(theta1 + (M_PI/6)) + 3.5),
                 _robotZ + 0.02);

        drawRect(QVector2D(90.0*cos(theta2), 90.0*sin(theta2)),
                 QVector2D(90.0*cos(theta2) + 3.5, 90.0*sin(theta2) - 3.5),
                 QVector2D(90.0*cos(theta2 - (M_PI/6)), 90.0*sin(theta2 - (M_PI/6))),
                 QVector2D(90.0*cos(theta2 - (M_PI/6)) + 3.5, 90.0*sin(theta2 - (M_PI/6)) - 3.5),
                 _robotZ + 0.02);

        drawRect(QVector2D(-90.0*cos(theta2), 90.0*sin(theta2)),
                 QVector2D(-90.0*cos(theta2) - 3.5, 90.0*sin(theta2) - 3.5),
                 QVector2D(-90.0*cos(theta2 - (M_PI/6)), 90.0*sin(theta2 - (M_PI/6))),
                 QVector2D(-90.0*cos(theta2 - (M_PI/6)) - 3.5, 90.0*sin(theta2 - (M_PI/6)) - 3.5),
                 _robotZ + 0.02);

        glEndList();
    });
}

void FieldView::setupBallDisplayList() {
    // Check if ball shape was been already set and delete if True
    if(_ballShape != GL_INVALID_VALUE) {
        glDeleteLists(_ballShape, 1);
    }

    // Generate a display list
    _ballShape = glGenLists(1);
    if(_ballShape == GL_INVALID_VALUE) {
        spdlog::error("Failed to create ball shape display list.");
    }

    // Draw in the display list
    glNewList(_ballShape, GL_COMPILE);

    glColor3d(1.0, 0.5059, 0.0);
    drawArc(QVector2D(0, 0), 0, 16, -M_PI, M_PI, _ballZ);
    glColor3d(0.8706, 0.3490, 0.0);
    drawArc(QVector2D(0, 0), 15, 21, -M_PI, M_PI, _ballZ);

    glEndList();
}

float FieldView::getLineThickness() {
    return _lineThickness;
}

void FieldView::initializeGL() {
    // Setup display lists
    setupRobotDisplayList();
    setupBallDisplayList();

    // Setup central logo
    if(_centralLogo == nullptr && !_centralLogoPath.isEmpty()) {
        setupCentralLogo(_centralLogoPath);
    }

    // Setup font
    QFont textFont = this->font();
    textFont.setWeight(QFont::Bold);
    textFont.setPointSize(80);
    _glText = GLText(textFont);
}

void FieldView::paintGL() {
    _graphicsMutex.lock();

    glClearColor(FIELD_COLOR);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glPushMatrix();

    draw();

    glPopMatrix();

    _graphicsMutex.unlock();
}

void FieldView::draw() {
    drawFieldLines();
    drawCentralLogo();
}

void FieldView::drawFieldLines() {
    glColor4f(FIELD_LINES_COLOR);

    for (auto &l : _fieldLineSegments) {
        const float half_thickness = 0.5f * getLineThickness();
        Geometry::Vector2D perp = (l.end() - l.start()).normalize();
        perp = {-perp.y(), perp.x()};

        const Geometry::Vector2D v1 = l.start() - (perp * half_thickness);
        const Geometry::Vector2D v2 = l.end() + (perp * half_thickness);

        drawRect(v1, v2, _fieldZ);
    }


    for (auto &c : _fieldCircles) {
        const float half_thickness = 0.5 * getLineThickness();
        drawArc(c.center(), c.radius() - half_thickness, c.radius() + half_thickness, 0.0, 2.0 * M_PI, _fieldZ);
    }

    for (auto &a : _fieldArcs) {
        drawArc(a.center(), a.radius() - getLineThickness(), a.radius() + getLineThickness(), a.startAngle().value(), a.endAngle().value(), _fieldZ);
    }
}

void FieldView::drawCentralLogo(const float &centralLogoSize) {
    // If no central logo has set, just pass
    if(_centralLogo == nullptr) {
        return ;
    }

    // Bind the opengltexture
    _centralLogo->bind();

    // Draw
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glScalef(1.0f, -1.0f, 1.0f);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-centralLogoSize, -centralLogoSize, _fieldZ + 0.01);
    glTexCoord2f(0, 1); glVertex3d(-centralLogoSize, centralLogoSize, _fieldZ + 0.01);
    glTexCoord2f(1, 1); glVertex3d(centralLogoSize, centralLogoSize, _fieldZ + 0.01);
    glTexCoord2f(1, 0); glVertex3d(centralLogoSize, -centralLogoSize, _fieldZ + 0.01);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void FieldView::mousePressEvent(QMouseEvent* event) {
    _leftButton = event->buttons().testFlag(Qt::LeftButton);
    _midButton = event->buttons().testFlag(Qt::MiddleButton);
    _rightButton = event->buttons().testFlag(Qt::RightButton);

    if(_leftButton) {
        setCursor(Qt::ClosedHandCursor);
    }
    if(_midButton) {
        setCursor(Qt::SizeVerCursor);
    }
    if(_leftButton || _midButton) {
        _mouseStartX = event->x();
        _mouseStartY = event->y();
    }
}

void FieldView::mouseReleaseEvent(QMouseEvent* event) {
    setCursor(Qt::ArrowCursor);
}

void FieldView::mouseMoveEvent(QMouseEvent* event) {
    bool leftButton = event->buttons().testFlag(Qt::LeftButton);
    bool midButton = event->buttons().testFlag(Qt::MiddleButton);

    if(leftButton) {
        _viewXOffset -= _viewScale * float(event->x() - _mouseStartX);
        _viewYOffset += _viewScale * float(event->y() - _mouseStartY);
        _mouseStartX = event->x();
        _mouseStartY = event->y();
        recomputeProjection();
    }
    else if(midButton) {
        float zoomRatio = static_cast<float>(event->y() - _mouseStartY)/500.0;
        _viewScale = _viewScale * (1.0 + zoomRatio);
        recomputeProjection();
        _mouseStartX = event->x();
        _mouseStartY = event->y();
    }
}

void FieldView::wheelEvent(QWheelEvent* event) {
    float zoomRatio = -static_cast<float>(event->angleDelta().y())/1000.0;
    _viewScale = _viewScale * (1.0 + zoomRatio);
    recomputeProjection();
}

void FieldView::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    resetView();
}

void FieldView::resetView() {
    _viewScale = (_field.length() + 500.0) / width();
    _viewScale = std::max(_viewScale, (_field.width() + 500.0f) / height());

    _viewXOffset = _viewYOffset = 0.0;
    recomputeProjection();
}

void FieldView::recomputeProjection() {
    makeCurrent();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5 * _viewScale * width() + _viewXOffset, 0.5 * _viewScale * width() + _viewXOffset,
            -0.5 * _viewScale*height() + _viewYOffset, 0.5 * _viewScale * height() + _viewYOffset,
            _minZValue, _maxZValue);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    doneCurrent();
}

void FieldView::redraw() {
    _graphicsMutex.lock();
    update();
    _graphicsMutex.unlock();
}

void FieldView::geometryChanged(const Common::Types::Field& field) {
    _graphicsMutex.lock();
    setupFieldGeometry(field);
    _graphicsMutex.unlock();

    resetView();
}
