#include <GL/glut.h>

int iPointNum = 0;                     //已确定点的数目
int x1=0,x2=0,y1=0,y2=0;               //确定的点坐标
int winWidth = 400, winHeight = 300;     //窗口的宽度和高度

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);         
}

void ChangeSize(int w, int h)
{
	winWidth = w;	winHeight = h;
	glViewport(0, 0, w, h);                 //指定窗口显示区域
	glMatrixMode(GL_PROJECTION);      //设置投影参数
	glLoadIdentity();
	gluOrtho2D(0.0,winWidth,0.0,winHeight);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); 
	if(iPointNum >= 1)	{
		glBegin(GL_LINES);              //绘制直线段
			glVertex2i(x1,y1);
			glVertex2i(x2,y2);
		glEnd();
	}
	glutSwapBuffers();                    //交换缓冲区
}

void PassiveMouseMove (GLint xMouse, GLint yMouse)
{
	if(iPointNum == 1)	{
		x2 = xMouse;
		y2 = winHeight - yMouse;	
		glutPostRedisplay();
	}	
}


void Key(unsigned char key, int x, int y)
{
	switch(key){
		case 'p':
			if(iPointNum == 0 || iPointNum == 2)	{
				iPointNum = 1;
				x1 = x;	y1 = winHeight - y;
			}
			else	{
				iPointNum = 2;
				x2 = x;	y2 = winHeight - y;
				glutPostRedisplay();
			}
			break;
		default: break;
	}	
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //使用双缓存及RGB模型
	glutInitWindowSize(400,300); 
	glutInitWindowPosition(100,100);
	glutCreateWindow("橡皮筋技术"); 
	glutDisplayFunc(Display); 
	glutReshapeFunc(ChangeSize);                //指定窗口在整形回调函数
	glutKeyboardFunc(Key);        //指定键盘响应函数
	glutPassiveMotionFunc(PassiveMouseMove);    //指定鼠标移动响应函数
	Initial();                                    
	glutMainLoop();                               
	return 0;
}
