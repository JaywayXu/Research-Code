#include <GL/glut.h>
void initial(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glLineWidth(4.0);
    GLfloat ControlP[4][3]={{-80.0,-40.0,0.0},{-10.0,90.0,0.0},
                            {10.0,-90.0,0.0},{80.0,40.0,0.0}};
    glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);
    glEnable(GL_MAP1_VERTEX_3);
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glMapGrid1f(100,0.0,1.0);
    glEvalMesh1(GL_LINE, 0, 100);
    glFlush();
}

void Reshape(GLint newWidth, GLint newHeight)
{
    glViewport(0,0,newWidth,newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
}

int main(int argc,char *argv[])
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
