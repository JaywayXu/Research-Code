#include <GL/glut.h>
GLenum DepthFunc = GL_LESS; //用于确定当前的深度比较测试方式
void Initial()
{
	glEnable(GL_DEPTH_TEST);   // 启用深度测试
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fAspect;
	fAspect = (float)w/(float)h;
	gluPerspective(45.0, fAspect, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);   
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	if(key == 'l' || key == 'L')
	{
		DepthFunc = GL_LESS;
		glClearDepth (1.0); //不同的比较测试方式需要不同的初始化值
	}
	else if(key == 'g' || key == 'G')
	{
		DepthFunc = GL_GREATER;
		glClearDepth (0.0);
	}
	glutPostRedisplay();
}
void Display(void)
{
	static float fElect1 = 0.0f;      
	glDepthFunc(DepthFunc);  //设置深度比较测试方式
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -250.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(12.0f, 15, 15); 
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(90.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15); 
	
glPopMatrix(); 
	glPushMatrix(); 
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f); 
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);  
	glTranslatef(-70.0f, 0.0f, 0.0f);  
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	glPushMatrix(); 
	glRotatef(-45.0f,0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();	
	fElect1 += 10.0f;
	if(fElect1 > 360.0f)	fElect1 = 10.0f;
	glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("深度测试示例");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
    glutTimerFunc(500, TimerFunc, 1); 
	Initial();
	glutMainLoop();
	return 0;
}
