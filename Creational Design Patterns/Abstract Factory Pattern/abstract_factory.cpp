#include <iostream>
#include <memory>

// Product interfaces: every brand supplies these related vehicle types.
class Car {
public:
    virtual ~Car() = default;
    virtual void start() const = 0;
};

class Truck {
public:
    virtual ~Truck() = default;
    virtual void haul() const = 0;
};

// Concrete products: each belongs to one brand family.
class HondaCar final : public Car {
public:
    void start() const override {
        std::cout << "Honda car is starting.\n";
    }
};

class HondaTruck final : public Truck {
public:
    void haul() const override {
        std::cout << "Honda truck is hauling a load.\n";
    }
};

class ToyotaCar final : public Car {
public:
    void start() const override {
        std::cout << "Toyota car is starting.\n";
    }
};

class ToyotaTruck final : public Truck {
public:
    void haul() const override {
        std::cout << "Toyota truck is hauling a load.\n";
    }
};

// Abstract Factory: creates a compatible family of related products.
class VehicleFactory {
public:
    virtual ~VehicleFactory() = default;
    virtual std::unique_ptr<Car> createCar() const = 0;
    virtual std::unique_ptr<Truck> createTruck() const = 0;
};

// Each concrete factory creates products from its own brand family.
class HondaFactory final : public VehicleFactory {
public:
    std::unique_ptr<Car> createCar() const override {
        return std::make_unique<HondaCar>();
    }

    std::unique_ptr<Truck> createTruck() const override {
        return std::make_unique<HondaTruck>();
    }
};

class ToyotaFactory final : public VehicleFactory {
public:
    std::unique_ptr<Car> createCar() const override {
        return std::make_unique<ToyotaCar>();
    }

    std::unique_ptr<Truck> createTruck() const override {
        return std::make_unique<ToyotaTruck>();
    }
};

// Client uses the factory and product interfaces, not brand-specific classes.
void showVehicles(const VehicleFactory& factory) {
    const std::unique_ptr<Car> car = factory.createCar();
    const std::unique_ptr<Truck> truck = factory.createTruck();

    car->start();
    truck->haul();
}

int main() {
    std::cout << "Honda family:\n";
    const HondaFactory hondaFactory;
    showVehicles(hondaFactory);

    std::cout << "\nToyota family:\n";
    const ToyotaFactory toyotaFactory;
    showVehicles(toyotaFactory);
}
