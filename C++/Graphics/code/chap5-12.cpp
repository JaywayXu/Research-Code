#include <GL/glut.h>
GLuint lineList; //指定显示列表ID
void Initial()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glLineWidth(12.0f);
    glColor4f (0.0, 0.6, 1.0, 1.0);
    lineList = glGenLists(1);
    glNewList(lineList, GL_COMPILE);  //定义显示列表
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(4.0f, 2.0f);
    glVertex2f(2.0f, 5.0f);
    glEnd();
    glEndList();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    if(h == 0)		h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        gluOrtho2D(0.0, 5.0, 0.0, 6.0*(GLfloat)h/(GLfloat)w);
    else
        gluOrtho2D(0.0, 5.0*(GLfloat)w/(GLfloat)h, 0.0, 6.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Displayt(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(lineList);
    glFlush();
}

void Displayw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH);      //使用反走样
    glEnable (GL_BLEND);             //启用混合函数
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //指定混合函数
    glCallList(lineList);
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInit(&argc,argv);
    glutCreateWindow("原始图形");
    glutDisplayFunc(Displayt);
    glutReshapeFunc(ChangeSize);
    Initial();

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(300, 300);
    glutInitWindowSize(300, 300);
    glutCreateWindow("反走样图形");
    glutDisplayFunc(Displayw);
    glutReshapeFunc(ChangeSize);
    Initial();
    glutMainLoop();
}