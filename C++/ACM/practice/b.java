import java.util.Scanner;
import java.math.BigInteger;
public class b {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        BigInteger b1, b2;
        while(input.hasNext()) {
            b1 = input.nextBigInteger();
            b2 = input.nextBigInteger();
            System.out.println(b1.remainder(b2));
        }
    }
}