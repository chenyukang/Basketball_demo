/**
 * @file   main.cpp
 * @author moorekang <moorekang@gmail.com>
 * @date   Sun Jul 18 14:14:48 2010
 * 
 * @brief  主程序 面板控制 GUI响应
 * 
 * 
 */
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
using namespace std;

int   main_window;
/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui, *glui2;
GLUI_Spinner    *Viewpoint_x, *Viewpoint_y;
GLUI_Spinner    *Viewpoint_z;
GLUI_RadioGroup *radio;
GLUI_Panel      *obj_panel;

float obj_pos[] = { 0.0, 0.0, -50.0 };
int last_x,last_y;

void update()
{
    if ( glutGetWindow() != main_window ) 
        glutSetWindow(main_window);  
    usleep(1000);
    GAME->Update();
    glui->sync_live();
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-obj_pos[0],-obj_pos[1],-obj_pos[2] ); 
    GAME->Render();
    //draw the secen
    glPopMatrix();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

/***************************************** myGlutMouse() **********/
void myGlutMouse(int button, int button_state, int x, int y )
{
  if ( button == GLUT_RIGHT_BUTTON && button_state == GLUT_DOWN ) {
    last_x = x;
    last_y = y;
  }
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f,0.0f,70.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
    glutPostRedisplay();
}

void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'w':
        obj_pos[1]+=0.35;
        break;
    case 's':
        obj_pos[1]-=0.35;
        break;
    case 'a':
        GAME->ChangeRenderRegionFlag();
        break;
    case 'd':
        obj_pos[0]+=0.35;
        break;
    case 'i':
        obj_pos[2]+=0.35;
        break;
    case 'o':
        obj_pos[2]-=0.35;
        break;
    case 'p':
        GAME->ChangePauseFlag();
        break;
    case 'r':
        obj_pos[0] = obj_pos[1] = 0;
        obj_pos[2]=-50.0;
        break;
    }
    glutPostRedisplay();
}

/************ myGlutIdle() ***********/
void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  

  glutPostRedisplay();
}


void reset()
{
    
}

int main(int argc,char* argv[])
{
   
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(1200,700);
    glutInitWindowPosition(100,100);
    
    main_window=glutCreateWindow ("BaskeBall");
    init();
    
    glutDisplayFunc(display);
    GLUI_Master.set_glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myGlutMouse);

    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/
  
    /*** Create the side subwindow ***/
    glui = GLUI_Master.create_glui_subwindow( main_window, 
                                              GLUI_SUBWINDOW_RIGHT );
    
    glui->set_main_gfx_window( main_window );
    GLUI_Master.set_glutIdleFunc( update );

    /*** Create the bottom subwindow ***/
    glui2 = GLUI_Master.create_glui_subwindow( main_window, 
                                               GLUI_SUBWINDOW_BOTTOM );
    glui2->set_main_gfx_window( main_window );

    GLUI_Translation *trans_xy = 
        new GLUI_Translation(glui2, "Trans XY", GLUI_TRANSLATION_XY, obj_pos );
    trans_xy->set_speed( .15 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x = 
        new GLUI_Translation(glui2, "Trans X", GLUI_TRANSLATION_X, obj_pos );
    trans_x->set_speed( .15 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = 
        new GLUI_Translation( glui2, "Trans Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
    trans_y->set_speed( .15 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = 
        new GLUI_Translation( glui2, "Trans Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
    trans_z->set_speed( .35 );

  
    glutMainLoop();
    return EXIT_SUCCESS;
}
