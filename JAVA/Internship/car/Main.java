package car;

public class Main {
    public static void main(String[] args) {
        Car car = new Car(10,34.5,2017);
        BusTruck bustruck = new BusTruck(2,50,2018,23);
        car.run();
        car.turnLeft();
        car.turnRight();
        bustruck.run();
        bustruck.turnLeft();
        bustruck.turnRight();
        bustruck.goodsIn();
    }
}
