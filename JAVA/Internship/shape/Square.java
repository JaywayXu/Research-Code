package shape;

public class Square implements Area{
    private Line line;
    Square(Line l) {
        line = l;
    }
    public Line getLine() {
        return line;
    }
    public float getArea() {
        return line.getLength() * line.getLength();
    }
}
