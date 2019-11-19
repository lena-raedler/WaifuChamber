/**
 * Created by Lena on 14/11/2019 16:15.
 */
public class manager {
    public static void main(String[] args) {
        Room room = new Room(1, 3);

        Person person1 = new Person("Cindy", "LN", 23);
        Person person2 = new Person("Mandy", "LN", 23);
        Person person3 = new Person("Sandy", "LN", 23);
        Person person4 = new Person("Candy", "LN", 23);

        room.enter(person1);
        room.enter(person2);
        room.enter(person3);
        room.enter(person4);

        room.getPeopleQuantity();
        room.checkPerson(person2);
        room.exit(person4);
        room.exit(person3);
        room.listAllPeople();
    }
}
