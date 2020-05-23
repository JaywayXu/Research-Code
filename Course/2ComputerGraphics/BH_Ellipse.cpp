#include <GL/glut.h>

#define POINT_SIZE 5

void MidBresenhamEllipse(int x0, int y0, int a, int b) { //BH画圆
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);
    int x,y;
    float d1,d2;
    x=0;y=b;
    d1=b*b+a*a*(-b+0.25);
    glVertex2i(x0+x,y0+y);
    glVertex2i(x0-x,y0+y);
    glVertex2i(x0+x,y0-y);
    glVertex2i(x0-x,y0-y);
    while (b*b*(x+1)<a*a*(y-0.5)) {
        if (d1<0){
            d1+=b*b*(2*x+3);
            x++;
        } else {
            d1+=b*b*(2*x+3)+a*a*(-2*y+2);
            x++; y--;
        }
        glVertex2i(x0+x,y0+y);
        glVertex2i(x0-x,y0+y);
        glVertex2i(x0+x,y0-y);
        glVertex2i(x0-x,y0-y);
    }
    d2 = b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
    while (y>0) {
        if (d2<=0) {
            d2+=b*b*(2*x+2)+a*a*(-2*y+3);
            x++; y--;
        } else {
            d2+=a*a*(-2*y+3);
            y--;
        }
        glVertex2i(x0+x,y0+y);
        glVertex2i(x0-x,y0+y);
        glVertex2i(x0+x,y0-y);
        glVertex2i(x0-x,y0-y);
    }
    glEnd();
}

void draw() {
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    MidBresenhamEllipse(90,60,80,40);
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
