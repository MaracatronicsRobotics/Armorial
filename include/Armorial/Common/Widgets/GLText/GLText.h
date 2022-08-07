#ifndef ARMORIAL_COMMON_WIDGETS_GLTEXT_H
#define ARMORIAL_COMMON_WIDGETS_GLTEXT_H

#include <QVector>
#include <QtGui>
#include <GL/glu.h>
#include <math.h>
#include <float.h>

#include <Armorial/Common/Types/Traits/Traits.h>

namespace Common {
namespace Widgets {

    class GLText{
        struct Glyph{
            bool compiled;
            GLuint displayListID;
            double width;
            double height;
            double ascent;
            double descent;

            Glyph() {
                compiled=false;
            }
        };

        QVector<Glyph> glyphs;
        QFont font;
        double characterSpacing;

    public:
        typedef enum{
            LeftAligned,
            RightAligned,
            CenterAligned
        } HAlignOptions;

        typedef enum{
            TopAligned,
            BottomAligned,
            MedianAligned,
            MiddleAligned
        } VAlignOptions;

        GLText(QFont font = QFont());

        template<typename T>
        std::enable_if_t<Common::Types::has_coordinates_v<T>, void> drawString(const T& loc, double angle, double size, const char* str, GLText::HAlignOptions hAlign=LeftAligned, GLText::VAlignOptions vAlign=MiddleAligned, QColor textColor=QColor(Qt::white)) {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glTranslated(loc.x(), loc.y(), 0.0);
            glScaled(size, size, 1.0);
            glRotated(angle, 0, 0, 1);

            glColor4f(textColor.redF(), textColor.greenF(), textColor.blueF(), textColor.alphaF());

            switch(hAlign){
                case LeftAligned:{
                    // Normal rendering will achieve this!
                    break;
                }
                case RightAligned:{
                    glTranslated(-getWidth(str), 0, 0);
                    break;
                }
                case CenterAligned:{
                    glTranslated(-0.5 * getWidth(str), 0, 0);
                    break;
                }
            }
            switch(vAlign){
                case BottomAligned: {
                    glTranslated(0.0, getDescent(str), 0.0);
                    break;
                }
                case TopAligned: {
                    glTranslated(0.0, -getAscent(str), 0.0);
                    break;
                }
                case MedianAligned: {
                    // Normal rendering will achieve this!
                    break;
                }
                case MiddleAligned: {
                    glTranslated(0.0, -0.5 * getHeight(str), 0.0);
                    break;
                }
            }

            QVector2D textDir(1, 0);
            double d = 0.0;
            while((*str) > 0){
                drawGlyph((*str));
                d = characterSpacing + (0.5 * getWidth((*str)));
                str++;
                if((*str) > 0) {
                    d += 0.5 * getWidth((*str));
                    glTranslated(d * textDir.x(), d * textDir.y(), 0.0);
                }
            }

            glPopMatrix();
        }

        void drawGlyph(char glyph);
        void initializeGlyph(char ch);
        double getWidth(char ch);
        double getHeight(char ch);
        QVector2D getSize(char ch);
        double getWidth(const char* str);
        double getHeight(const char* str);
        double getAscent(char ch);
        double getDescent(char ch);
        double getAscent(const char* str);
        double getDescent(const char* str);

    private:
        static const char* getPrimitiveType(GLenum type);
        static void tessBeginCB(GLenum which);
        static void tessEndCB();
        static void tessVertexCB(const GLvoid *data);
        static void tessErrorCB(GLenum errorCode);
        static constexpr double FontRenderSize = 1000.0;
    };
}
}

#endif // ARMORIAL_COMMON_WIDGETS_GLTEXT_H
