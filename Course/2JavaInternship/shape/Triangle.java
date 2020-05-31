package shape;

public class Triangle implements Area{
    private Line line_1;
    private Line line_2;
    private Line line_3;
    Triangle() {
        line_1 = new Line();
        line_2 = new Line();
        line_3 = new Line();
    }
    Triangle(Line line1,Line line2,Line line3) {
        this.line_1=line1;
        this.line_2=line2;
        this.line_3=line3;
    }
    public boolean IsTriangle() {
        if (line_1.getLength()+line_2.getLength()>line_3.getLength()&&
                line_1.getLength()+line_3.getLength()>line_2.getLength()&&
                line_2.getLength()+line_3.getLength()>line_1.getLength())
            return true;
        else
            return false;
    }
    public Line getLine_1() {
        return line_1;
    }
    public Line getLine_2() {
        return line_2;
    }
    public Line getLine_3() {
        return line_3;
    }
    public float getArea() {
        if (!IsTriangle()) {
            System.out.println("不能构成三角形，失败！");
            return 0;
        }
        else {
            float p=(line_1.getLength()+line_2.getLength()+line_3.getLength())/2;
            return (float) Math.sqrt(p*(p-line_1.getLength())*(p-line_2.getLength())*(p-line_3.getLength()));
        }
    }
}
