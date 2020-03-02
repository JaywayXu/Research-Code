public class elephant_and_icebox{
	public static void main(String args[]){
		int size = 2;
		Icebox aIcebox = new Icebox(size);
		Elephant firstElephant = new Elephant("bob");
		Elephant secondElephant = new Elephant("tom");
		aIcebox.open();
		aIcebox.push(firstElephant);
		aIcebox.push(secondElephant);
		aIcebox.pop();
		aIcebox.pop();
		aIcebox.pop();
		aIcebox.close();
		aIcebox.push(firstElephant);
		aIcebox.pop();
	}
}
