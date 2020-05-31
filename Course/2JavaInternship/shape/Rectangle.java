package shape;

public class Rectangle implements Area{
    private Line line_1;
    private Line line_2;
    Rectangle() {
        line_1=new Line();
        line_2=new Line();
    };
    Rectangle(Line l1,Line l2) {
        line_1 = l1;
        line_2 = l2;
    }
    public Line getLine_1() {
        return line_1;
    }
    public Line getLine_2() {
        return line_2;
    }
    public float getArea() {
        return line_1.getLength() * line_2.getLength();
    }
}
