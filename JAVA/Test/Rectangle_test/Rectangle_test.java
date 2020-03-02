import java.util.Scanner;

public class Rectangle_test{
    public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		Rectangle a;
		a = new Rectangle();
		a.height = input.nextInt();
		a.width = input.nextInt();
		System.out.println(a.getArea() + " " + a.getPerimeter());
    }
}