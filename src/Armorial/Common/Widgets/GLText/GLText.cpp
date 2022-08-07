#include <Armorial/Common/Widgets/GLText/GLText.h>

using namespace Common::Widgets;

GLText::GLText(QFont drawFont) {
    glyphs.clear();
    font = drawFont;
    font.setPixelSize(FontRenderSize);

    characterSpacing = 0.1;
}

void GLText::drawGlyph(char glyph) {
    if(glyphs.size() < (glyph + 1)) {
        glyphs.resize(glyph + 1);
    }

    if(!glyphs[glyph].compiled) {
        initializeGlyph(glyph);
    }

    glCallList(glyphs[glyph].displayListID);
}

double GLText::getWidth(char ch) {
    if(glyphs.size() < (ch + 1)) {
        glyphs.resize(ch + 1);
    }

    if(!glyphs[ch].compiled) {
        initializeGlyph(ch);
    }

    return glyphs[ch].width;
}

double GLText::getHeight(char ch) {
    if(glyphs.size() < (ch + 1)) {
        glyphs.resize(ch + 1);
    }

    if(!glyphs[ch].compiled) {
        initializeGlyph(ch);
    }

    return glyphs[ch].height;
}

QVector2D GLText::getSize(char ch) {
    return QVector2D(getWidth(ch),getHeight(ch));
}

double GLText::getWidth(const char* str) {
    double width = 0.0;
    while((*str) > 0){
        width += getWidth(*str);
        str++;
        if((*str) > 0){
            width += characterSpacing;
        }
    }

    return width;
}

double GLText::getHeight(const char* str) {
    double height = 0.0;
    while((*str) > 0){
        height = std::max(height,getHeight(*str));
        str++;
    }

    return height;
}

double GLText::getAscent(char ch) {
    if(glyphs.size() < (ch + 1)) {
        glyphs.resize(ch + 1);
    }

    if(!glyphs[ch].compiled) {
        initializeGlyph(ch);
    }

    return glyphs[ch].ascent;
}

double GLText::getDescent(char ch) {
    if(glyphs.size() < (ch + 1)) {
        glyphs.resize(ch+1);
    }

    if(!glyphs[ch].compiled) {
        initializeGlyph(ch);
    }

    return glyphs[ch].descent;
}

double GLText::getAscent(const char* str) {
    double ascent = 0.0;
    while((*str) > 0){
        ascent = std::max(ascent, getAscent(*str));
        str++;
    }

    return ascent;
}

double GLText::getDescent(const char* str) {
    double descent = 0.0;
    while((*str) > 0){
        descent = std::max(descent,getDescent(*str));
        str++;
    }

    return descent;
}

void GLText::initializeGlyph(char ch) {
    Glyph glyph;
    QPainterPath path;
    path.addText(0, 0, font, QString((QChar)ch));

    QList<QPolygonF> polygons = path.toSubpathPolygons();

    int numVertices = 0;
    double minX = DBL_MAX, minY = DBL_MAX, maxX = -DBL_MAX, maxY = -DBL_MAX;
    for(int i = 0; i < polygons.size(); i++){
        numVertices += polygons[i].size();

        for(int k = 0; k < polygons[i].size(); k++){
            minX = std::min(minX, polygons[i][k].x());
            maxX = std::max(maxX, polygons[i][k].x());
            minY = std::min(minY, polygons[i][k].y());
            maxY = std::max(maxY, polygons[i][k].y());
        }
    }

    glyph.ascent = fabs(minY)/FontRenderSize;
    glyph.descent = fabs(maxY)/FontRenderSize;

    glyph.height = (maxY - minY)/FontRenderSize;
    glyph.width = (maxX - minX)/FontRenderSize;

    GLdouble vertices[numVertices][3];
    int j = 0;
    for(int i = 0; i < polygons.size(); i++){
        for(int k = 0; k < polygons[i].size(); k++){
            vertices[j][0] = polygons[i][k].x()/FontRenderSize;
            vertices[j][1] = -polygons[i][k].y()/FontRenderSize;
            vertices[j][2] = 9;
            j++;
        }
    }

    GLUtesselator* tess = gluNewTess();
    gluTessCallback(tess, GLU_TESS_BEGIN, (_GLUfuncptr) tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (_GLUfuncptr) tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (_GLUfuncptr) tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (_GLUfuncptr) tessVertexCB);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glyph.displayListID = glGenLists(1);
    if(glyph.displayListID == GL_INVALID_VALUE){
        printf("Unable to create display list!\n");
        exit(1);
    }

    glNewList(glyph.displayListID, GL_COMPILE);
    gluTessBeginPolygon(tess, 0);
    j = 0;

    for(int i = 0; i < polygons.size(); i++){
        gluTessBeginContour(tess);
        for(int k=0; k<polygons[i].size(); k++){
            gluTessVertex(tess, vertices[j], vertices[j]);
            j++;
        }
        gluTessEndContour(tess);
    }

    gluTessEndPolygon(tess);
    gluDeleteTess(tess);
    glEndList();
    glPopMatrix();

    glyph.compiled = true;
    glyphs[ch] = glyph;
}

const char* GLText::getPrimitiveType(GLenum type) {
    switch(type) {
        case 0x0000:
            return "GL_POINTS";
            break;
        case 0x0001:
            return "GL_LINES";
            break;
        case 0x0002:
            return "GL_LINE_LOOP";
            break;
        case 0x0003:
            return "GL_LINE_STRIP";
            break;
        case 0x0004:
            return "GL_TRIANGLES";
            break;
        case 0x0005:
            return "GL_TRIANGLE_STRIP";
            break;
        case 0x0006:
            return "GL_TRIANGLE_FAN";
            break;
        case 0x0007:
            return "GL_QUADS";
            break;
        case 0x0008:
            return "GL_QUAD_STRIP";
            break;
        case 0x0009:
            return "GL_POLYGON";
            break;
    }

    return NULL;
}

void GLText::tessBeginCB(GLenum which) {
    glBegin(which);
}

void GLText::tessEndCB() {
    glEnd();
}

void GLText::tessVertexCB(const GLvoid *data) {
    const GLdouble *ptr = (const GLdouble*) data;
    glVertex3dv(ptr);
}

void GLText::tessErrorCB(GLenum errorCode) {
    const GLubyte *errorStr;
    errorStr = gluErrorString(errorCode);
    printf("[ERROR]: %s\n", errorStr);
}
