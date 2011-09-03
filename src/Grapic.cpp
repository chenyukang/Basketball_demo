/**
 * @file   Grapic.cpp
 * @author moorekang <moorekang@gmail.com>
 * @date   Sun Jul 18 15:42:36 2010
 * @brief  Grapic类的实现
 */

#include "Grapic.h"


Cgdi* Cgdi::Instance()
{
    static Cgdi instance;
    return &instance;
}


Cgdi::Cgdi()
{
}
Cgdi::~Cgdi()
{
}


GLvoid Cgdi::glPrint(float x, float y,const char *fmt, ...)		       
{
    char   text[256];						
    va_list ap;							
    if (fmt == NULL)						
        return;	
    va_start(ap, fmt);						
    vsprintf(text, fmt, ap);				
    va_end(ap);
    int n = strlen(text);
    //设置要在屏幕上显示字符的起始位置
    glRasterPos2i(x,y);
    //逐个显示字符串中的每个字符
    for (int i = 0; i < n; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *(text+i));
}

void Cgdi::TextAtPos(double x, double y, const std::string &s)
{
    glPrint(x,y,"%s",s.c_str());
}

void Cgdi::TextAtPos(Vector2D pos, const std::string &s)
{
    glPrint(pos.x,pos.y,s.c_str());
}

void Cgdi::Line(Vector2D from, Vector2D to)
{
    glBegin(GL_LINES);
    glVertex2f(from.x, from.y);
    glVertex2f(to.x, to.y);
    glEnd();
}

void Cgdi::Line(double a, double b, double x, double y)
{
    glBegin(GL_LINES);
    glVertex2f(a, b);
    glVertex2f(x, y);
    glEnd();
}

void Cgdi::Rect(double left, double top, double right, double bot)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, bot);
    glVertex2f(right, bot);
    glVertex2f(right, top);
    glVertex2f(left, top);
    glEnd();
}
    
void Cgdi::Circle(double cx, double cy, double radius)
{
    float angle = 0;
    glPointSize(1.2);
    glBegin(GL_POINTS);
    while(angle<=2*PI)
    {
        angle+=0.02;
        float x=radius*cos(angle);
        float y=radius*sin(angle);
        glVertex2f(cx+x,cy+y);
    }
    glEnd();
}


