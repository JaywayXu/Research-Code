
#include <iostream>
using namespace std;
 
#include <cmath>
#include <ctime>
#include "GL/glut.h"

static int cnt = 0;

class solor {
public:
    static void myTimerFunc(int val);//回掉函数，刷新画面
    static void drawSun();//绘制太阳
    static void drawMercury();//绘制水星
    static void drawVenus();//绘制金星
    static void drawEarth();//绘制地球
    static void drawMars();//绘制火星
    static void drawJupiter();//绘制木星
    static void drawSaturn();//绘制土星
    static void drawUranus();//绘制天王星
    static void drawNeptune();//绘制海王星
    static void drawOrbit(unsigned int para);//用来绘制轨道
    static void myDisplay();//在main里调用，显示绘制结果
    static void run(int *argc, char *argv[]);//运行

};

void solor::myTimerFunc(int val){
    cnt++;
    if(cnt>=50000)//上限50000到了就清零
        cnt=0;
    myDisplay();
    glutTimerFunc(1,myTimerFunc,0);
}
 
void solor::drawSun(){
    glPushMatrix();
        glColor4f(1.0,0.0,0.0,0.1);//红色
        glRotatef(cnt,0.0,0.0,-1.0);
        glutSolidSphere(25000000,30,30);
    glPopMatrix();
}
 
void solor::drawMercury(){
    glPushMatrix();
        glColor4f(0.0,1.0,1.0,0.8);//青色
        glRotatef(3.0*cnt,-0.0,0.0,-1.0);
        glTranslatef(50000000.0,0.0,0.0);
        glutSolidSphere(4000000,30,30);
    glPopMatrix();
    drawOrbit(50000000);//画轨道
}
 
void solor::drawVenus(){
    glPushMatrix();
        glColor4f(1.00,0.89,0.0,1.0);//金黄
        glRotatef(2.5*cnt,0.0,0.0,-1.0);
        glTranslatef(60000000,0.0,0.0);
        glutSolidSphere(5000000,30,30);
    glPopMatrix();
    drawOrbit(60000000);//画轨道
}
 
void solor::drawEarth(){
    glPushMatrix();
        glColor4f(0.0,0.0,1.0,0.8);//蓝色
        glRotatef(2.0*cnt,0.0,0.0,-1.0);
        glTranslatef(75000000,0.0,0.0);
        glutSolidSphere(7000000,30,30);
    glPopMatrix();
    drawOrbit(76000000);//画轨道
}

 
void solor::drawMars(){
    glPushMatrix();
        glColor4f(1.00,0.89,0.4,1.0);//黄色偏淡
        glRotatef(1.4*cnt,0.0,0.0,-1.0);
        glTranslatef(90000000,0.0,0.0);
        glutSolidSphere(6000000,30,30);
    glPopMatrix();
    drawOrbit(90000000);//画轨道
}
 
void solor::drawJupiter(){
    glPushMatrix();
        glColor4f(1.00,0.89,0.4,1.0);//黄色偏淡
        glRotatef(1.2*cnt,0.0,0.0,-1.0);
        glTranslatef(110000000,0.0,0.0);
        glutSolidSphere(15000000,20,20);
    glPopMatrix();
    drawOrbit(110000000);//画轨道
}
 
void solor::drawSaturn(){
    glPushMatrix();
        glColor4f(1.0,1.0,0.0,1.0);//黄色
        glRotatef(1.1*cnt,0.0,0.0,-1.0);
        glTranslatef(130000000,0.0,0.0);
        glutSolidSphere(6000000,20,20);
        glutSolidTorus(1000000,11000000,30,30);//绘制土星的“圆环”
    glPopMatrix();
    drawOrbit(130000000);//画轨道
}
 
void solor::drawUranus(){
    glPushMatrix();
        glColor4f(0.0,0.3,1.0,0.5);//青蓝色
        glRotatef(cnt,0.0,0.0,-1.0);
        glTranslatef(145000000,0.0,0.0);
        glutSolidSphere(7500000,20,20);
    glPopMatrix();
    drawOrbit(145000000);//画轨道
}
 
void solor::drawNeptune(){
    glPushMatrix();
        glColor4f(0.0,0.82,1.0,0.5);//青蓝色偏淡
        glRotatef(0.7*cnt,0.0,0.0,-1.0);//考虑到海王星转得最慢，第一个参数最后减到0.7*cnt
        glTranslatef(155000000,0.0,0.0);
        glutSolidSphere(8000000,20,20);
    glPopMatrix();
    drawOrbit(155000000);//画轨道
}
 
void solor::drawOrbit(unsigned int para){
    glPushMatrix();
        glColor4f(1.0,1.0,1.0,0.5);
        glutSolidTorus(100000,para,30,30);//用一个圆环来模拟轨道
    glPopMatrix();
}
 
void solor::myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);//刷新颜色缓冲
    glMatrixMode(GL_PROJECTION);//投影模式
    glLoadIdentity();//加载单位阵
    gluPerspective(62.0,1.0,1,100000000);//透视相关
    glMatrixMode(GL_MODELVIEW);//模型试图
    glLoadIdentity();
    gluLookAt(0,-200000000,200000000,0,0,0,0,0,1);//试点转换
    //调用画星球的函数
    drawSun();
    drawMercury();
    drawVenus();
    drawEarth();
    drawMars();
    drawJupiter();
    drawSaturn();
    drawUranus();
    drawNeptune();
    glutSwapBuffers();//交换缓冲区
}

void solor::run(int *argc, char *argv[]) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutCreateWindow("solor");
    glutDisplayFunc(&solor::myDisplay);
    glutTimerFunc(10, myTimerFunc, 0);
    glutMainLoop();
}
 
int main(int argc,char *argv[]) {
    solor::run(&argc,argv);
    return 0;
}