#include <iostream>
#include <memory>
#include <stdexcept>

// Product interface: all vehicles can start and stop.
class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual void start() const = 0;
    virtual void stop() const = 0;
};

// Concrete products: each vehicle supplies its own behavior.
class Car final : public Vehicle {
public:
    void start() const override {
        std::cout << "Car is starting...\n";
    }

    void stop() const override {
        std::cout << "Car is stopping...\n";
    }
};

class Truck final : public Vehicle {
public:
    void start() const override {
        std::cout << "Truck is starting...\n";
    }

    void stop() const override {
        std::cout << "Truck is stopping...\n";
    }
};

class Bike final : public Vehicle {
public:
    void start() const override {
        std::cout << "Bike is starting...\n";
    }

    void stop() const override {
        std::cout << "Bike is stopping...\n";
    }
};

// The application/user's choice of vehicle.
enum class VehicleType {
    Car,
    Truck,
    Bike
};

// Simple Factory: centralizes the choice and creation of concrete vehicles.
class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> create(VehicleType type) {
        switch (type) {
        case VehicleType::Car:
            return std::make_unique<Car>();
        case VehicleType::Truck:
            return std::make_unique<Truck>();
        case VehicleType::Bike:
            return std::make_unique<Bike>();
        }

        throw std::invalid_argument("Unknown vehicle type");
    }
};

// Client uses the Vehicle interface; it need not construct Car/Truck/Bike.
void useVehicle(VehicleType type) {
    std::unique_ptr<Vehicle> vehicle = VehicleFactory::create(type);
    vehicle->start();
    vehicle->stop();
}

int main() {
    useVehicle(VehicleType::Car);
    useVehicle(VehicleType::Truck);
    useVehicle(VehicleType::Bike);
}
