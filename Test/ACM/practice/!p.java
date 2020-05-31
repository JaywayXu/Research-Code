import java.util.Scanner;
import java.math.BigInteger;
public class p {
    public static BigInteger zero = new BigInteger("0");
    public static BigInteger one = new BigInteger("1");
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        BigInteger b1, b2;
        while(input.hasNext()) {
            b1 = input.nextBigInteger();
            b2 = input.nextBigInteger();
            BigInteger j = zero;
            for (BigInteger i = one;;i.add(one)) {
                if (b2.mod(i).compareTo(zero) == 0) {
                    if (b1.mod(i).compareTo(zero) == 0) {
                        if (gcd(i,b1.multiply(b2).divide(i)).compareTo(zero) != 0) {
                            j = i;
                        }
                    }
                }
            }
            System.out.println(j+" "+b1.multiply(b2).divide(j));
        }
    }
    public static BigInteger gcd(BigInteger a, BigInteger b) {
        if (a.mod(b).compareTo(zero) == 0){
            return b;
        }
        return gcd(b, a.mod(b));
    }
}