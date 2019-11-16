#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>
struct Person {
    std::string first_name;
    std::string last_name;
    int age;
    inline bool operator==(Person& p){
	return (!first_name.compare(p.first_name) && !last_name.compare(p.last_name) && age == p.age);
    }
    Person(std::string fn, std::string ln, int age) : first_name(fn), last_name(ln), age(age) {}
};

class Room {
  public:
    Room(int id, size_t limit) : id(id), limit(limit) {}
    const int id;
    const size_t limit;
    std::vector<std::shared_ptr<Person>> people;

    // Returns true iff the person successfully entered.
    bool enter(std::shared_ptr<Person> p) {
	std::cout << "Person " << (*p).first_name << " " << (*p).last_name << " entering!" << std::endl;
	if(people.size() < limit){
	    if(contains(*p) == -1){
	        people.push_back(p);
		std::cout << "SUCCESS! People in room : " << people.size() << std::endl;
	        return true;
	    }
	    else{
	    	std::cout << "FAILED! Person already in room!" << std::endl;
	    }
	}
	else{
	std::cout << "FAILED! Room full!" << std::endl;
	}
	return false;
    }

    void exit(std::shared_ptr<Person> p) {
	std::cout << "Person " << (*p).first_name << " " << (*p).last_name << " leaving!" << std::endl;
	int tmp = contains(*p);
	if(tmp >= 0){
	   people.erase(people.begin() + tmp);
	   std::cout << "SUCCESS! People in room : " << people.size() << std::endl;
	}
	else{
	std::cout << "FAILED! Person not in room!" << std::endl;
	}
    }

  private:
    int contains(Person& p){
	for(int i= 0; i < people.size();++i){
	    if(*people[i]==p){
		return i;
	    }
	}
	return -1;
    }

};

int main(int argc, char** argv){
    auto p1 = std::make_shared<Person>("John", "Doe", 33);
    auto p2 = std::make_shared<Person>("Micolash", "Cage", 22);
    auto p3 = std::make_shared<Person>("Jane", "Doe", 33);
    auto p4 = std::make_shared<Person>("Oldman", "Jenkins", 90);

    Room r(1, 3);
    r.enter(p1);
    r.enter(p1);
    r.enter(p2);
    r.enter(p3);
    r.enter(p4);
    r.exit(p4);
    r.exit(p3);

}
