import java.util.Scanner;
import java.math.BigInteger;
public class ee {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        BigInteger b1, b2;
        while(input.hasNext()) {
            b1 = input.nextBigInteger();
            b2 = input.nextBigInteger();
            if (b1.compareTo(b2)==0){
                System.out.println("infinity");
            }
            else{
                int num = 0;
                BigInteger one = new BigInteger("1");
                for (BigInteger i = new BigInteger("1"); i.compareTo(b1)<=0; i.add(one)){
                    if (b2 == b1.remainder(i)) num++;
                }
                System.out.println(num);
            }
        }
    }
}