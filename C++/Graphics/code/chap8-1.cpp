#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
class Pt3D{
public:
    GLfloat x,y,z;
};

void GetCnk(GLint n, GLint *c)
{
    GLint i,k;
    for(k=0;k<=n;k++){
        c[k]=1;
        for(i=n;i>=k+1;i--) c[k]=c[k]*i;
        for(i=n-k;i>=2;i--) c[k]=c[k]/i;
    }
}

void GetPointPr(GLint *c, GLfloat t, Pt3D *Pt, int ControlN, Pt3D *ControlP)
{
    GLint k,n=ControlN-1;
    GLfloat Bernstein;
    Pt->x=0.0; Pt->y=0.0; Pt->z=0.0;
    for(k=0; k<ControlN; k++){
        Bernstein = c[k]*pow(t,k)*pow(1-t,n-k);
        Pt->x += ControlP[k].x*Bernstein;
        Pt->y += ControlP[k].y*Bernstein;
        Pt->z += ControlP[k].z*Bernstein;
    }
}

void BezierCurve(GLint m, GLint ControlN, Pt3D *ControlP)
{
    GLint *C,i;
    Pt3D CurvePt;
    C = new GLint[ControlN];
    GetCnk(ControlN-1, C);
    glBegin (GL_POINTS);
    for(i=0;i<=m;i++){
        GetPointPr(C,(GLfloat)i/(GLfloat)m, &CurvePt, ControlN, ControlP);
        glVertex2f(CurvePt.x, CurvePt.y);
    }
    glEnd();
    delete [] C;
}

void initial(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLint ControlN=4,m=500;
    Pt3D ControlP[4]={{-80.0,-40.0,0.0},{-10.0,90.0,0.0},{10.0,-90.0,0.0},{80.0,40.0,0.0}};
    glPointSize(2);
    glColor3f(0.0, 0.0, 0.0);
    BezierCurve(m,ControlN,ControlP);
    glBegin (GL_LINE_STRIP);
    for(GLint i=0;i<4;i++)
        glVertex3f(ControlP[i].x,ControlP[i].y,ControlP[i].z);
    glEnd();
    glFlush();
}

void Reshape(GLint newWidth, GLint newHeight)
{
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
}

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInit(&argc,argv);
    glutCreateWindow("Bezier曲线");
    initial();
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}
