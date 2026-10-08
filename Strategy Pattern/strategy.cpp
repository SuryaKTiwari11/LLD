#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

// Strategy interfaces: each describes one ability that can vary independently.
class WalkBehavior {
public:
    virtual ~WalkBehavior() = default;
    virtual void walk() const = 0;
};

class TalkBehavior {
public:
    virtual ~TalkBehavior() = default;
    virtual void talk() const = 0;
};

class FlyBehavior {
public:
    virtual ~FlyBehavior() = default;
    virtual void fly() const = 0;
};

// Concrete strategies: different ways to perform each ability.
class NormalWalk final : public WalkBehavior {
public:
    void walk() const override {
        std::cout << "Walking normally...\n";
    }
};

class NoWalk final : public WalkBehavior {
public:
    void walk() const override {
        std::cout << "Cannot walk.\n";
    }
};

class NormalTalk final : public TalkBehavior {
public:
    void talk() const override {
        std::cout << "Talking normally...\n";
    }
};

class NoTalk final : public TalkBehavior {
public:
    void talk() const override {
        std::cout << "Cannot talk.\n";
    }
};

class NormalFly final : public FlyBehavior {
public:
    void fly() const override {
        std::cout << "Flying normally...\n";
    }
};

class NoFly final : public FlyBehavior {
public:
    void fly() const override {
        std::cout << "Cannot fly.\n";
    }
};

// Robot is composed of abilities. It delegates each action to its strategy.
class Robot {
public:
    Robot(std::unique_ptr<WalkBehavior> walkBehavior,
          std::unique_ptr<TalkBehavior> talkBehavior,
          std::unique_ptr<FlyBehavior> flyBehavior)
        : walkBehavior_(std::move(walkBehavior)),
          talkBehavior_(std::move(talkBehavior)),
          flyBehavior_(std::move(flyBehavior)) {
        if (!walkBehavior_ || !talkBehavior_ || !flyBehavior_) {
            throw std::invalid_argument("Robot behaviors cannot be null");
        }
    }

    virtual ~Robot() = default;

    void walk() const {
        walkBehavior_->walk();
    }

    void talk() const {
        talkBehavior_->talk();
    }

    void fly() const {
        flyBehavior_->fly();
    }

    // Swap one behavior while keeping this robot object.
    void setFlyBehavior(std::unique_ptr<FlyBehavior> flyBehavior) {
        if (!flyBehavior) {
            throw std::invalid_argument("Fly behavior cannot be null");
        }
        flyBehavior_ = std::move(flyBehavior);
    }

    virtual void projection() const = 0;

private:
    std::unique_ptr<WalkBehavior> walkBehavior_;
    std::unique_ptr<TalkBehavior> talkBehavior_;
    std::unique_ptr<FlyBehavior> flyBehavior_;
};

// Robot subclasses vary the robot's identity/display, not its abilities.
class CompanionRobot final : public Robot {
public:
    using Robot::Robot;

    void projection() const override {
        std::cout << "Displaying friendly companion features...\n";
    }
};

class WorkerRobot final : public Robot {
public:
    using Robot::Robot;

    void projection() const override {
        std::cout << "Displaying worker efficiency stats...\n";
    }
};

int main() {
    CompanionRobot companion{
        std::make_unique<NormalWalk>(),
        std::make_unique<NormalTalk>(),
        std::make_unique<NoFly>()
    };
    companion.walk();
    companion.talk();
    companion.fly();
    companion.projection();

    std::cout << "--------------------\n";

    WorkerRobot worker{
        std::make_unique<NoWalk>(),
        std::make_unique<NoTalk>(),
        std::make_unique<NormalFly>()
    };
    worker.walk();
    worker.talk();
    worker.fly();
    worker.projection();

    std::cout << "--------------------\n";
    std::cout << "Give the companion a flying ability at runtime:\n";
    companion.setFlyBehavior(std::make_unique<NormalFly>());
    companion.fly();
}
