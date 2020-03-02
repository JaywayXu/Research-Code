//g++ -o test -Wall BH_Line.cpp -mwindows glut32.lib -lopengl32 -lglu32 && test
#include <windows.h>
#include <GL/glut.h>

#define POINT_SIZE 5

void Line1(int x0, int y0, int x1, int y1) { //k>1
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);
    int x, y, dx, dy, e;
    dx = x1-x0;dy = y1-y0;
    e = -dy;x = x0;y = y0;
    while (y <= y1) {
        glVertex2i(x,y);
        y++;
        e = e+2*dx;
        if (e>0) {
            x++;
            e = e-2*dy;
        }
    }
    glEnd();
}

void Line2(int x0, int y0, int x1, int y1) { //0<k<1
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);
    int x, y, dx, dy, e;
    dx = x1-x0;dy = y1-y0;
    e = -dx;x = x0;y = y0;
    while (x <= x1) {
        glVertex2i(x,y);
        x++;
        e = e+2*dy;
        if (e>0) {
            y++;
            e = e-2*dx;
        }
    }
    glEnd();
}

void Line3(int x0, int y0, int x1, int y1) { //-1<k<0
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);
    int x, y, dx, dy, e;
    dx = x1-x0;dy = y0-y1;
    e = -dx;x = x0;y = y0;
    while (x <= x1) {
        glVertex2i(x,y);
        x++;
        e = e+2*dy;
        if (e>0) {
            y--;
            e = e-2*dx;
        }
    }
    glEnd();
}

void Line4(int x0, int y0, int x1, int y1) { //k<-1
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);
    int x, y, dx, dy, e;
    dx = x1-x0;dy = y0-y1;
    e = -dy;x = x0;y = y0;
    while (y >= y1) {
        glVertex2i(x,y);
        y--;
        e = e+2*dx;
        if (e>0) {
            x++;
            e = e-2*dy;
        }
    }
    glEnd();
}

void BresenhamLine(int x0, int y0, int x1, int y1) { //BH画线
    if (x0>x1) { //转换坐标
        int x = x0; int y = y0;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
    }
    //判断k的值并调用相应函数
    float k = ((float)y1-(float)y0)/((float)x1-(float)x0);
    if (k>1) Line1(x0,y0,x1,y1);
    else if (k>0) Line2(x0,y0,x1,y1);
    else if (k>-1) Line3(x0,y0,x1,y1);
    else Line4(x0,y0,x1,y1);
}

void draw() {
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    //glRectf(50.0f, 100.0f, 150.0f, 50.0f);
    BresenhamLine(50,50,70,90);
    BresenhamLine(50,50,90,70);
    BresenhamLine(50,50,90,30);
    BresenhamLine(50,50,70,10);
    BresenhamLine(50,50,30,90);
    BresenhamLine(50,50,10,70);
    BresenhamLine(50,50,10,30);
    BresenhamLine(50,50,30,10);
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(480, 480);
    glutCreateWindow("Opengl");
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

