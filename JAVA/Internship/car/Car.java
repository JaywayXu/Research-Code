package car;

public class Car {
    protected int passengerNum;
    protected double oilNum;
    protected int date;

    Car(int pn, double on, int d) {
        passengerNum = pn;
        oilNum = on;
        date = d;
    }
    public void run() {
        System.out.println("汽车：");
        System.out.println("客容量：" + passengerNum);
        System.out.println("油储量：" + oilNum);
        System.out.println("生产日期：" + date);
        System.out.println("开始运行");
    }
    public void turnLeft() {
        System.out.println("左转");
    }
    public void turnRight() {
        System.out.println("右转");
    }
}

