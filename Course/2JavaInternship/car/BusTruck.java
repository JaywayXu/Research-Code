package car;

public class BusTruck extends Car{
    protected int goodsNum;

    BusTruck(int pn, double on, int d, int gn) {
        super(pn, on, d);
        goodsNum = gn;
    }
    public void run() {
        System.out.println("货车：");
        System.out.println("客容量：" + passengerNum);
        System.out.println("油储量：" + oilNum);
        System.out.println("生产日期：" + date);
        System.out.println("载货量" + goodsNum);
        System.out.println("货物卡车开始运行");
    }
    public void turnLeft() {
        System.out.println("货车左转");
    }
    public void turnRight() {
        System.out.println("货车右转");
    }
    public void goodsIn() {
        System.out.println("货物上车");
    }
}
