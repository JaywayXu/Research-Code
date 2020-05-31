#include <GL/glut.h>
void Initial(void)
{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);      //设置窗口背景颜色为白色
		glMatrixMode(GL_PROJECTION);     //设置投影参数
		gluOrtho2D(0.0,200.0,0.0,150.0);
}

void Display(void)
{
		glClear(GL_COLOR_BUFFER_BIT);   //用当前背景色填充窗口
		glColor3f(1.0f, 0.0f, 0.0f);            //设置当前的绘图颜色为红色
		glRectf(50.0f, 100.0f, 150.0f, 50.0f);    //绘制一个矩形
glFlush();                         //处理所有的OpenGL程序
}

int main(int argc, char* argv[])
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //初始化窗口的显示模式
		glutInitWindowSize(400,300);                  //设置窗口的尺寸
		glutInitWindowPosition(100,120);               //设置窗口的位置
		glutCreateWindow("矩形");                    //创建一个名为矩形的窗口
		glutDisplayFunc(Display);                     //设置当前窗口的显示回调函数
		Initial();                                    //完成窗口初始化
		glutMainLoop();                             //启动主GLUT事件处理循环
		return 0;
}
