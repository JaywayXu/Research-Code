#include <GL/glut.h>
void Initial()
{
    glEnable(GL_DEPTH_TEST);       // 启用深度测试
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );	//背景为白色
}

void ChangeSize(int w, int h)
{
    if(h == 0)	h = 1;
    glViewport(0, 0, w, h);               // 设置视区尺寸
    glMatrixMode(GL_PROJECTION);    // 指定当前操作投影矩阵堆栈
    glLoadIdentity();                   // 重置投影矩阵

    GLfloat fAspect;
    fAspect = (float)w/(float)h;            // 计算视区的宽高比
    gluPerspective(45.0, fAspect, 1.0, 500.0); // 指定透视投影的观察空间
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display(void)
{
    static float fElect1 = 0.0f;           // 绕原子旋转的角度
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色和深度缓冲区

    glMatrixMode(GL_MODELVIEW);  // 指定当前操作模型视图矩阵堆栈
    glLoadIdentity();                  // 重置模型视图矩阵
    glTranslatef(0.0f, 0.0f, -250.0f);	   //将图形沿z轴负向移动

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(12.0f, 15, 15);      // 绘制红色的原子

    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();                  // 保存当前的模型视图矩阵
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);   // 绕y轴旋转一定的角度
    glTranslatef(90.0f, 0.0f, 0.0f);       // 平移一段距离
    glutSolidSphere(6.0f, 15, 15);       // 画出第一个电子

    glPopMatrix();       // 恢复模型视图矩阵
    glPushMatrix();      // 保存当前的模型视图矩阵
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);     //绕z轴旋转45°
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(-70.0f, 0.0f, 0.0f);
    glutSolidSphere(6.0f, 15, 15);       // 画出第二个电子

    glPopMatrix();        // 恢复模型视图矩阵
    glPushMatrix();       // 保存当前的模型视图矩阵
    glRotatef(-45.0f,0.0f, 0.0f, 1.0f);    //绕z轴旋转-45°
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 60.0f);
    glutSolidSphere(6.0f, 15, 15);      // 画出第三个电子
    glPopMatrix();

    fElect1 += 10.0f;     // 增加旋转步长，产生动画效果
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
    glutCreateWindow("分子动画示例");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(Display);
    glutTimerFunc(500, TimerFunc, 1);     //指定定时器回调函数
    Initial();
    glutMainLoop();
    return 0;
}
