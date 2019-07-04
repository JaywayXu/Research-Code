#include <GL/glut.h>
#include <math.h>

GLUnurbsObj *pNurb = NULL;// NURBS对象指针
GLint nNumPoints = 4; // 4 X 4
GLfloat ctrlPoints[4][4][3]= {{{  -6.0f, -6.0f, 0.0f},	// u = 0,	v = 0
						      {	  -6.0f, -2.0f, 0.0f},	//			v = 1
							  {   -6.0f,  2.0f, 0.0f},	//			v = 2	
							  {   -6.0f,  6.0f, 0.0f}}, //			    v = 3
							 {{  -2.0f, -6.0f, 0.0f},	// u = 1	v = 0
						      {   -2.0f, -2.0f, 8.0f},	//			v = 1
							  {   -2.0f,  2.0f, 8.0f},	//			v = 2
							  {   -2.0f,  6.0f, 0.0f}},	//			v = 3
							 {{   2.0f, -6.0f,  0.0f }, // u =2		v = 0
							  {    2.0f, -2.0f,  8.0f }, //			v = 1
							  {    2.0f,  2.0f,  8.0f },	//			v = 2
							  {    2.0f,  6.0f,  0.0f }},//			v = 3
                             {{    6.0f,  -6.0f, 0.0f},	// u = 3	v = 0
							  {    6.0f, -2.0f, 0.0f},	//			v = 1
							  {    6.0f,  2.0f, 0.0f},	//			v = 2
							  {    6.0f,  6.0f, 0.0f}}};//			v = 3
GLfloat Knots[8] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void DrawPoints(void) //绘制控制点
{
	int i,j;
	glPointSize(5.0f);
	glColor3ub(255,0,0);
	glBegin(GL_POINTS);
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				glVertex3fv(ctrlPoints[i][j]);	
	glEnd();
}

void Initial()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	//定义NURBS参数
    pNurb = gluNewNurbsRenderer();
    gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 25.0f);
       gluNurbsProperty(pNurb, GLU_DISPLAY_MODE,
                      (GLfloat)GLU_OUTLINE_POLYGON);
}

void ReDraw(void)
{
	glColor3ub(0,0,220);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(330.0f, 1.0f,0.0f,0.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    gluBeginSurface(pNurb);
		gluNurbsSurface(pNurb,	        // NURBS对象指针
			8,                      // 参数化u方向上的结点数目
			Knots,		        	// 参数化u方向上递增的结点值的数组	
			8,                      // 参数化v方向上的结点数目
			Knots,			        // 参数化v方向上递增的结点值的数组
			4 * 3,			       	// 参数化u方向上相邻控制点之间的偏移量
			3,					    // 参数化v方向上相邻控制点之间的偏移量
			&ctrlPoints[0][0][0],       // 包含曲面控制点的数组
			4,                      // 参数化u方向上的阶数
			4,					    // 参数化v方向上的阶数
			GL_MAP2_VERTEX_3);	// 曲面的类型
	gluEndSurface(pNurb);
	
	DrawPoints();
	glPopMatrix();
	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)	xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)	yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)	yRot += 5.0f;
	if(xRot > 356.0f)	xRot = 0.0f;
	if(xRot < -1.0f)	xRot = 355.0f;
	if(yRot > 356.0f)	yRot = 0.0f;
	if(yRot < -1.0f)	yRot = 355.0f;
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	if(h == 0)		h = 1;
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (45.0f, (GLdouble)w/(GLdouble)h, 1.0, 40.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glTranslatef (0.0f, 0.0f, -20.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("NURBS曲面");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	glutSpecialFunc(SpecialKeys);
	Initial();
	glutMainLoop();
	return 0;
}
