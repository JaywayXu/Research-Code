#include <windows.h>
#include <GL/glut.h>

#define POINT_SIZE 5

void MidBresenhamCircle(int x0, int y0, int r) { //BH画圆
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);
    int x,y,d;
    x=0;y=r;d=1-r;
    while (x<=y) {
        glVertex2i(x0+x,y0+y);
        glVertex2i(x0+y,y0+x);
        glVertex2i(x0-x,y0+y);
        glVertex2i(x0-y,y0+x);
        glVertex2i(x0+x,y0-y);
        glVertex2i(x0+y,y0-x);
        glVertex2i(x0-x,y0-y);
        glVertex2i(x0-y,y0-x);
        if (d<0) d+=2*(x)+3;
        else {
            d+=2*(x-y)+5;
            y--;
        }
        x++;
    }
    glEnd();
}

void draw() {
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    MidBresenhamCircle(50,50,30);
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(520, 400);
    glutCreateWindow("Opengl");
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
