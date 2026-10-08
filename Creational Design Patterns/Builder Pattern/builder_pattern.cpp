#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

// Car is the finished product. Clients create it through Car::Builder.
class Car {
public:
    class Builder {
    public:
        explicit Builder(std::string engine)
            : engine_(std::move(engine)) {
            if (engine_.empty()) {
                throw std::invalid_argument("Car engine cannot be empty");
            }
        }

        Builder& wheels(int count) {
            wheels_ = count;
            return *this;
        }

        Builder& seats(int count) {
            seats_ = count;
            return *this;
        }

        Builder& color(std::string value) {
            color_ = std::move(value);
            return *this;
        }

        Builder& sunroof(bool included = true) {
            sunroof_ = included;
            return *this;
        }

        Builder& navigation(bool included = true) {
            navigation_ = included;
            return *this;
        }

        // Build copies this builder's configuration into a separate Car value.
        Car build() const {
            if (wheels_ <= 0 || seats_ <= 0 || color_.empty()) {
                throw std::invalid_argument(
                    "Car wheels, seats, and color must be valid");
            }
            return Car(engine_, wheels_, seats_, color_, sunroof_, navigation_);
        }

    private:
        std::string engine_;
        int wheels_ = 4;
        int seats_ = 5;
        std::string color_ = "Black";
        bool sunroof_ = false;
        bool navigation_ = false;
    };

    void describe() const {
        std::cout << "Car: engine=" << engine_
                  << ", wheels=" << wheels_
                  << ", seats=" << seats_
                  << ", color=" << color_
                  << ", sunroof=" << std::boolalpha << sunroof_
                  << ", navigation=" << navigation_ << '\n';
    }

private:
    Car(std::string engine, int wheels, int seats, std::string color,
        bool sunroof, bool navigation)
        : engine_(std::move(engine)),
          wheels_(wheels),
          seats_(seats),
          color_(std::move(color)),
          sunroof_(sunroof),
          navigation_(navigation) {}

    std::string engine_;
    int wheels_;
    int seats_;
    std::string color_;
    bool sunroof_;
    bool navigation_;
};

int main() {
    // Required engine is explicit; optional choices are named and readable.
    const Car sportCar = Car::Builder("V8")
                            .color("Red")
                            .sunroof()
                            .navigation()
                            .build();
    sportCar.describe();

    // A separate builder starts with its own defaults for this configuration.
    const Car basicCar = Car::Builder("V6")
                             .seats(4)
                             .color("Blue")
                             .build();
    basicCar.describe();
}
