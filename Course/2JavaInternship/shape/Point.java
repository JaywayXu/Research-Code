package shape;

public class Point {
    private float point_x;
    private float point_y;

    Point(){};
    Point(float point_x,float point_y)                      //构造函数
    {
        this.point_x=point_x;
        this.point_y=point_y;
    }
    public void setPoint(float point_x,float point_y)      //设置点的坐标
    {
        this.point_x=point_x;
        this.point_y=point_y;
    }
    public float getPoint_x()                               //返回点的横坐标
    {
        return this.point_x;
    }
    public float getPoint_y()                               //返回点的纵坐标
    {
        return this.point_y;
    }
}
