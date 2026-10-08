#include <iostream>

// A single shared logger is accessed through this class, not constructed by clients.
class Logger final {
public:
    static Logger& instance() {
        // Since C++11, initialization of a function-local static is thread-safe.
        static Logger logger;
        return logger;
    }

    // One shared instance also means copying it must not create another logger.
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    void log(const char* message) const {
        std::cout << "Log: " << message << '\n';
    }

private:
    Logger() {
        std::cout << "Logger created once.\n";
    }
};

// These clients do not construct Logger; both request the shared instance.
class Application {
public:
    void run() const {
        Logger::instance().log("Application started.");
    }
};

class UserService {
public:
    void login(const char* username) const {
        Logger::instance().log(username);
    }
};

int main() {
    Application application;
    UserService userService;

    application.run();
    userService.login("User logged in.");

    // Both references point to the same object.
    Logger& firstReference = Logger::instance();
    Logger& secondReference = Logger::instance();
    std::cout << "Same logger instance: "
              << std::boolalpha
              << (&firstReference == &secondReference)
              << '\n';
}
