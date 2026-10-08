#include <iostream>
#include <memory>
#include <string>
#include <utility>

// Prototype interface: clients clone through this common contract.
class CharacterPrototype {
public:
    virtual ~CharacterPrototype() = default;
    virtual std::unique_ptr<CharacterPrototype> clone() const = 0;
    virtual void setName(std::string name) = 0;
    virtual void setLevel(int level) = 0;
    virtual void setAttackPower(int attackPower) = 0;
    virtual void describe() const = 0;
};

// Concrete prototype: its copy constructor copies the character's current state.
class GameCharacter final : public CharacterPrototype {
public:
    GameCharacter(std::string name, int health, int attackPower, int level)
        : name_(std::move(name)),
          health_(health),
          attackPower_(attackPower),
          level_(level) {}

    std::unique_ptr<CharacterPrototype> clone() const override {
        return std::make_unique<GameCharacter>(*this);
    }

    void setName(std::string name) override {
        name_ = std::move(name);
    }

    void setLevel(int level) override {
        level_ = level;
    }

    void setAttackPower(int attackPower) override {
        attackPower_ = attackPower;
    }

    void describe() const override {
        std::cout << "Character: name=" << name_
                  << ", health=" << health_
                  << ", attack=" << attackPower_
                  << ", level=" << level_ << '\n';
    }

private:
    std::string name_;
    int health_;
    int attackPower_;
    int level_;
};

int main() {
    // This configured character is the prototype (template) to copy.
    const GameCharacter warriorTemplate{"Default Warrior", 100, 50, 1};

    // Copy the template, then change only the fields that differ.
    std::unique_ptr<CharacterPrototype> warrior = warriorTemplate.clone();
    warrior->setName("Warrior");

    std::unique_ptr<CharacterPrototype> veteran = warriorTemplate.clone();
    veteran->setName("Veteran");
    veteran->setLevel(5);
    veteran->setAttackPower(80);

    std::cout << "Original template (unchanged):\n";
    warriorTemplate.describe();
    std::cout << "Clones customized independently:\n";
    warrior->describe();
    veteran->describe();
}
