# Low-Level Design (LLD) Patterns — Beginner Lessons

Beginner-friendly design pattern lessons using plain-language analogies, Excalidraw diagrams, and runnable C++17 examples.

## Which pattern should I use?

Open the [LLD Pattern Guide](./LLD%20Pattern%20Guide.excalidraw) for a visual decision guide.

| If your main problem is… | Start with… | Category |
|---|---|---|
| Switching an object's behavior without changing the object using it | [Strategy](#behavioral-design-patterns) | Behavioral |
| Centralizing the choice and construction of one product | [Simple Factory](#creational-design-patterns) | Creational |
| Creating several related products that belong to one family | [Abstract Factory](#creational-design-patterns) | Creational |
| Constructing one complex object with optional settings in readable steps | [Builder](#creational-design-patterns) | Creational |
| Creating similar objects by copying a prepared template and changing a few details | [Prototype](#creational-design-patterns) | Creational |
| Providing one shared instance when there is a genuine single-instance requirement | [Singleton](#creational-design-patterns) | Creational |

These patterns solve different problems and can be used together. Prefer the simplest design that fits the actual requirement.

## Creational Design Patterns

Creational patterns focus on how objects are created.

### Simple Factory

This lesson centralizes a choice among vehicle types. Simple Factory is a common object-creation idiom, distinct from the GoF Factory Method pattern. Adding a vehicle means updating the factory's selection logic.

- [Vehicle factory diagram](./Creational%20Design%20Patterns/Factory%20Pattern/Factory%20Pattern.excalidraw)
- [Vehicle factory C++17 example](./Creational%20Design%20Patterns/Factory%20Pattern/factory_pattern.cpp)

### Abstract Factory Pattern

Create a family of related products through a shared factory interface. The example creates cars and trucks from matching Honda or Toyota families. Adding a brand can be done by adding its factory and products; adding a new product type requires changing the abstract factory and its concrete implementations.

- [Abstract Factory diagram](./Creational%20Design%20Patterns/Abstract%20Factory%20Pattern/Abstract%20Factory%20Pattern.excalidraw)
- [Abstract Factory C++17 example](./Creational%20Design%20Patterns/Abstract%20Factory%20Pattern/abstract_factory.cpp)

### Builder Pattern

Construct one complex object step by step using named settings rather than a long list of positional constructor arguments. The car example requires an engine, gives optional settings defaults, validates the finished configuration, and returns a separate `Car` value from `build()`. Use a new builder for a new configuration; reusing a mutable builder can carry previous choices forward. A builder adds code, so a simple constructor is often clearer for small objects.

- [Car builder diagram](./Creational%20Design%20Patterns/Builder%20Pattern/Builder%20Pattern.excalidraw)
- [Car builder C++17 example](./Creational%20Design%20Patterns/Builder%20Pattern/builder_pattern.cpp)

### Prototype Pattern

Create a new object by cloning a configured prototype, then customize only the fields that differ. The game-character example implements a polymorphic `clone()` returning an owning `std::unique_ptr`. Its value and string fields copy independently; if a prototype later owns pointers or shared resources, define shallow-versus-deep copy behavior deliberately. Cloning is not inherently faster than construction; it is useful when prepared state is worth reusing.

- [Character prototype diagram](./Creational%20Design%20Patterns/Prototype%20Pattern/Prototype%20Pattern.excalidraw)
- [Character prototype C++17 example](./Creational%20Design%20Patterns/Prototype%20Pattern/prototype_pattern.cpp)

### Singleton Pattern

Provide a shared access point to one instance when the design truly requires one. The C++ example uses a function-local static (Meyers Singleton), whose initialization is thread-safe in C++11 and later. That does not automatically make other operations on the logger thread-safe. Global access can also hide dependencies and make tests harder.

- [Singleton diagram](./Creational%20Design%20Patterns/Singleton%20Pattern/Singleton%20Pattern.excalidraw)
- [Singleton C++17 example](./Creational%20Design%20Patterns/Singleton%20Pattern/singleton_pattern.cpp)

## Behavioral Design Patterns

Behavioral patterns focus on how objects communicate and how responsibilities or behaviors vary.

### Strategy Pattern

Encapsulate interchangeable behaviors behind interfaces. The robot **has** behavior objects and delegates to them, so abilities can be combined without making a subclass for every combination. This is composition rather than inheritance for behavior reuse.

- [Robot abilities diagram](./Behavioral%20Design%20Patterns/Strategy%20Pattern/Strategy.excalidraw)
- [Robot abilities C++17 example](./Behavioral%20Design%20Patterns/Strategy%20Pattern/strategy.cpp)
- [Payment strategy diagram](./Behavioral%20Design%20Patterns/Strategy%20Pattern/Payment%20Strategy.excalidraw)
- [Payment strategy C++17 example](./Behavioral%20Design%20Patterns/Strategy%20Pattern/payment_strategy.cpp)

## Structural Design Patterns

Structural patterns focus on how objects and classes are combined into larger structures or simpler interfaces. This category is ready for lessons; no structural pattern lessons have been added yet. See [the category folder](./Structural%20Design%20Patterns/README.md).

## Compile and run an example

The examples use standard C++17 and can be built with `g++`:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic "Behavioral Design Patterns/Strategy Pattern/strategy.cpp" -o strategy
./strategy
```

Replace the source path and output name with the example you want to run. On Windows PowerShell, run the resulting executable as `.\strategy.exe`.

## Repository layout

```text
Creational Design Patterns/
  Abstract Factory Pattern/
  Builder Pattern/
  Factory Pattern/
  Prototype Pattern/
  Singleton Pattern/
Behavioral Design Patterns/
  Strategy Pattern/
Structural Design Patterns/
  README.md
LLD Pattern Guide.excalidraw
README.md
```
