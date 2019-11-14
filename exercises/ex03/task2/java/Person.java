/**
 * Created by Lena on 14/11/2019 16:05.
 */
public class Person {
    private String firstName;
    private String lastName;
    private int age;

    Person(String firstName, String lastName, int age) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
    }

    public void print() {
        System.out.print(this.firstName + " " + this.lastName);
    }
}
