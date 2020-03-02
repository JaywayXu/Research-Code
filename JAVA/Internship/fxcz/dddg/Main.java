package dddg;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner=new Scanner(System.in);
        System.out.print("Fib项数：");
        int item_number=scanner.nextInt();
        long pre1=System.currentTimeMillis();
        System.out.println("递归结果:"+Fibonacci_recuration(item_number));
        long affter1=System.currentTimeMillis();
        System.out.println("递归时间："+(affter1-pre1)+"ms");
        long pre2=System.currentTimeMillis();
        System.out.println("迭代结果:"+Fibonacci_Interation(item_number));
        long affter2=System.currentTimeMillis();
        System.out.println("迭代时间："+(affter2-pre2)+"ms");

    }
    public static long Fibonacci_recuration(int number)                           //递归求解斐波那契数列
    {
        if (number==0)
            return 0;
        if (number==1)
            return 1;
        else
            return Fibonacci_recuration(number-1)+Fibonacci_recuration(number-2);
    }
    public static long Fibonacci_Interation(int number)                          //迭代方法求解斐波那契
    {
        if (number==1)
            return 1;
        long fib_reault=0;
        long fib_firstitem=0;
        long fib_seconditem=1;
        int count=1;
        while (count<number)
        {
            fib_reault=fib_firstitem+fib_seconditem;
            fib_firstitem=fib_seconditem;
            fib_seconditem=fib_reault;
            count++;
        }
        return fib_reault;
    }
}
