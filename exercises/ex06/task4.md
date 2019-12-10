## Task 4

#### Summary:
The topic of the article is that many threads online are criticism on object oriented programming that are used as an argument to promote entity component systems.
The author talks about the code that is used in these articles and why those are bad code examples, as the break object oriented design rules.

Object oriented programming is a rather old paradigm that became a huge topic in the 90s where new languages added object orientation features as keywords. This lead to a huge increase in OOP programmers that didn't know a lot about the design choices.
It all starts with the "4 pillars of OOP, abstraction, encapsulation, polymorphism and inheritance" which the author calls tools and that you should learn when to use them.
An improvement to this is the SOLID-C mnemonic:
- single responsibility principle -> one responsibility per class
- open/closed principle -> interface for things that may not change, implementations for things that change
- liskov substitution principle -> implementation need to 100% comply the requirements
- interface segregation principle -> interfaces as small as possible
- dependency inversion principle -> outsource communication
- composite reuse principle -> inheritance should be reserved for when its absolutely required

In the provided example code templates are used to find components of a certain type, which makes the code extra generic.
The downside to that is due to this the code is also slow.

If we use templates only when they are needed we resolve performance issues caused by this.