public class Test {
    public static void main(String[] args) {
        double max = 5000000;
        double x, y;
        // 蒙特卡洛法
        int num = 0;
        for (int i=0; i<max; i++) {
            x = Math.random();
            y = Math.random();
            if (x*x<=y && Math.sqrt(x)>=y) num++;
        }
        System.out.println(num/max);
        // 分割矩形法
        double w;
        double l;
        w = 1/max;
        x = w/2;
        // w = 5/max;
        // x = 1+w/2;
        double sum = 0;
        for (int i=0; i<max; i++) {
            l = Math.sqrt(x) - x*x;
            // l = 0.0167*Math.pow(x,5)-0.2917*Math.pow(x,4)+2*Math.pow(x,3)-6.7083*x*x+9.9833*x+61;
            sum += w*l;
            x += w;
        }
        System.out.println(sum);
    }
}