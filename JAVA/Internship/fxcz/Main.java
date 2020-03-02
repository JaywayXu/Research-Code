package fxcz;

class People {
    String name;
    String number;
    People(String name, String number) {
        this.name=name;
        this.number=number;
    }
    String getName() {
        return this.name;
    }
    String getNumber() {
        return number;
    }
}
class Student extends People {
    String student_num;
    Student(String name, String number, String student_num) {
        super(name,number);
        this.student_num=student_num;
    }
    String getName(int a) {
        return "new-"+this.name;
    }
    String getNumber() {
        return student_num;
    }
}

public class Main {
    public static void main(String[] args) {
        People p = new People("abc","12345");
        Student t = new Student("abc","12345","6789");
        System.out.println(t.getName());
        System.out.println(t.getName(1));
        System.out.println(p.getNumber());
        System.out.println(t.getNumber());
    }
}

