import java.math.BigInteger;
import java.util.Scanner;

public class BigNumber {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = Integer.parseInt(sc.nextLine());
        for (int i = 0; i<x; i++) {
            String sa = sc.next();
            String sb = sc.next();
            BigInteger a = new BigInteger(sa);
            BigInteger b = new BigInteger(sb);
            if (i == x-1) {
                System.out.println("Case "+(i+1)+":");
                System.out.println(a+" + "+b+" = "+a.add(b));
            }
            else {
                System.out.println("Case "+(i+1)+":");
                System.out.println(a+" + "+b+" = "+a.add(b));
                System.out.println();
            }
        }
    }
}