package paint;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

class myPaint extends JPanel {
    private int w;
    private int h;
    public void paintComponent(final Graphics g) {
        w = getWidth();
        h = getHeight();
        int x0 = 200;
        int y0 = 200;
        g.setColor(Color.BLACK);
        // x轴
        g.drawLine(0,y0,x0*2,y0);
        g.drawLine(x0*2,y0,x0*2-10,y0-10);
        g.drawLine(x0*2,y0,x0*2-10,y0+10);
        // y轴
        g.drawLine(x0,0,x0,y0*2);
        g.drawLine(x0,0,x0-10,10);
        g.drawLine(x0,0,x0+10,10);
        // 符号
        g.drawString("Y",x0-20,20);
        g.drawString("X",x0*2-20,y0+20);
        // sin(x) cos(x)
        for (int x=0; x<x0*2; x++) {
            int y1 = (int) (Math.sin((x-x0)*Math.PI/180)*100);
            int y2 = (int) (Math.cos((x-x0)*Math.PI/180)*100);
            g.drawString(".",x,y0-y1);
            g.drawString(".",x,y0-y2);
        }
    }
}
public class Paint extends JFrame {
    Paint() {
        getContentPane().add(new myPaint());
        setSize(400,400);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    public static void main(String[] args) {
        new Paint();
    }
}
