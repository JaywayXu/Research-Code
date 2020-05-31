package shape;

public class Main {
    public static void main(String[] args) {
        Line l1=new Line( 0f,0f,50f,50f);
        Line l2=new Line(0f,0f,70f,80f);
        Line l3=new Line(0f,0f,1000f,1000f);
        Square square = new Square(l1);
        Rectangle rectangle = new Rectangle(l1,l2);
        Triangle triangle = new Triangle(l1,l2,l3);
        System.out.println("正方形面积："+square.getArea());
        System.out.println("长方形面积："+rectangle.getArea());
        System.out.println("三角形面积："+triangle.getArea());
    }
}
