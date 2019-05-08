public class Test {
    public static void main(String[] args) {
        // 蒙特卡洛法
        int max = 5000000;
        double x;
        double y;
        int num = 0;
        for (int i=0; i<max; i++) {
            x = Math.random();
            y = Math.random();
            if (x*x<=y && Math.sqrt(x)>=y) num++;
        }
        System.out.println(num/max);
        // 分割矩形法
        double max = 5000000;
        double w;
        double l;
        w = 1/max;
        double x = w/2;
        double sum = 0;
        for (int i=0; i<max; i++) {
            l = Math.sqrt(x) - x*x;
            sum += w*l;
            x += w;
        }
        System.out.println(sum);
    }
}