#ifndef CGDI_H
#define CGDI_H
#include <string>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <stdarg.h>
#include <GL/glut.h>
#include "Vec2D.h"


//------------------------------- define some colors
const int NumColors = 15;

//单例模式
#define gdi Cgdi::Instance()

class Cgdi
{
public:
  
    int NumPenColors()const{return NumColors;}

    enum
    {
        red,
        blue, 
        green,
        black,
        pink,
        grey,
        yellow,
        orange,
        purple,
        brown,   
        white,
        dark_green,
        light_blue,
        light_grey,
        light_pink,
        hollow
    };

  
  
private:

    float r,g,b;
    //constructor is private
    Cgdi();
    Cgdi(const Cgdi&);
    Cgdi& operator=(const Cgdi&);

public:

    ~Cgdi();
    
    static Cgdi* Instance();


    //ALWAYS call this before drawing
    void StartDrawing()
        {
            glPushAttrib(GL_CURRENT_BIT);   //< 保存当前属性 
            glPushMatrix();
            
            
        }
  
    //ALWAYS call this after drawing
    void StopDrawing()
        {
            glPopMatrix();
            glPopAttrib();
        }

    void SetColor(float rr, float gg, float bb)
        {
            r = rr;
            g = gg;
            b = bb;
            glColor3f(r,g,b);
        }
    //---------------------------Text
    GLvoid glPrint(float x, float y, const char *fmt, ...);
    void TextAtPos(double x, double y, const std::string &s);
    void TextAtPos(Vector2D pos, const std::string &s);
    void Line(Vector2D from, Vector2D to);
    void Line(double a, double b, double x, double y);
    void Rect(double left, double top, double right, double bot);
    void Circle(double x, double y, double radius);
};
#endif
