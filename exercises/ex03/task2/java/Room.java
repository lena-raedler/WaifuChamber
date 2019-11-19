/**
 * Created by Lena on 14/11/2019 16:09.
 */
import java.io.*;
import java.util.*;

public class Room {
    private long limit; //64 bit long
    private int id;
    private ArrayList<Person> people = new ArrayList<>();

    Room(int id, long limit) {
        this.id = id;
        this.limit = limit;
    }

    public boolean enter(Person person) {
        if(people.size() < limit && !isInside(person)) {
            people.add(person);
            return true;
        } else {
            return false;
        }
    }

    public void exit(Person person) {
        people.remove(person);
    }

    public void getPeopleQuantity() {
        System.out.println(people.size() + " persons inside.");
    }

    private boolean isInside(Person person) {
        if(people.contains(person)) {
            return true;
        } else {
            return false;
        }
    }

    public void checkPerson(Person person) {
        if(isInside(person)) {
            person.print();
            System.out.println( " is inside");
        } else {
            person.print();
            System.out.println(" is not inside");
        }
    }

    public void listAllPeople() {
        for(Person person : people) {
            person.print();
            System.out.println();
        }
    }
}
