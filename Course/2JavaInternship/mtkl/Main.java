package mtkl;

import java.util.Random;

class Fun {
    final int MAX_NUM=100000;
    Random random=new Random();
    double fun() {
        int computer_num=0;
        double quarter_circle_area;
        double point_x;
        double point_y;
        for (int i=0; i<MAX_NUM; i++) {
            point_x=random.nextDouble();
            point_y=random.nextDouble();
            if(Math.pow(point_x,2)+Math.pow(point_y,2)<=1)
                computer_num++;
        }
        quarter_circle_area = (double)computer_num/MAX_NUM;
        return quarter_circle_area;
    }
}

public class Main {
    public static void main(String[] args) {
        Fun a = new Fun();
        for (int i=0; i<10; i++)
            System.out.println(a.fun());
    }
}
