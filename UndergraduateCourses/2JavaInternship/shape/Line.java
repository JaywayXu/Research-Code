package shape;

public class Line {
    private Point point_start;
    private Point point_stop;
    Line() {
        point_start=new Point();
        point_stop=new Point();
    }
    Line(float x1,float y1,float x2,float y2) {
        point_start=new Point();
        point_stop=new Point();
        point_start.setPoint(x1,y1);
        point_stop.setPoint(x2,y2);
    }
    public float getLength()
    {
        float x_length=Math.abs(point_start.getPoint_x()-point_stop.getPoint_x());
        float y_length=Math.abs(point_start.getPoint_y()-point_stop.getPoint_y());
        return (float) Math.sqrt(Math.pow(x_length,2)+Math.pow(y_length,2));
    }
}
