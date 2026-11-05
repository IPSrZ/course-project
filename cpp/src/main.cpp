#include "computer.hpp"
#include "session.hpp"

#include <iostream>
#include <memory>
#include <utility>

int main() {
    using cyberclub::Computer;
    using cyberclub::Session;

    std::cout << "=== 1. Composition + aggregation + rule ===\n";
    {
        // shared_ptr: Session needs weak_ptr from shared ownership
        std::shared_ptr<Computer> pc = std::make_shared<Computer>(1, "PC-01", "RTX-4060");
        pc->printStatus();

        std::cout << "-- correct: start session --\n";
        Session s(101, "Ivan", pc);  // weak_ptr from shared_ptr
        s.start();
        s.addTime(60);
        s.printStatus();
        pc->printStatus();

        std::cout << "-- violate: start again --\n";
        s.start();

        std::cout << "-- violate: repair while already ok, then break and fix --\n";
        pc->finishRepair();
        pc->requestRepair("GPU overheat");
        s.end();

        std::cout << "-- violate: start while broken --\n";
        s.start();
        pc->finishRepair();
        s.start();
        s.end();
        pc->powerOff();
    }  // Session dtor, then last shared_ptr -> Computer + Hardware dtors

    std::cout << "\n=== 2. unique_ptr: single owner + move ===\n";
    {
        std::unique_ptr<Computer> alone = std::make_unique<Computer>(2, "PC-02", "i5-12400");
        alone->powerOn();
        alone->printStatus();

        std::unique_ptr<Computer> moved = std::move(alone);
        std::cout << "after move: alone empty? " << (alone == nullptr ? "yes" : "no") << "\n";
        std::cout << "moved still owns PC-02:\n";
        moved->powerOff();
        std::cout << "-- leave unique_ptr block: Computer destroyed without delete --\n";
    }

    std::cout << "\n=== 3. shared_ptr: use_count + last owner destroys ===\n";
    std::shared_ptr<Computer> first = std::make_shared<Computer>(3, "PC-03", "Ryzen-5");
    std::cout << "use_count after create: " << first.use_count() << "\n";
    {
        std::shared_ptr<Computer> second = first;
        std::cout << "use_count after copy: " << first.use_count() << "\n";
        second->powerOn();
        first->printStatus();
        second->powerOff();
        std::cout << "-- leave inner shared_ptr block --\n";
    }
    std::cout << "use_count after second destroyed: " << first.use_count() << "\n";
    std::cout << "-- first still alive; object destroyed with last owner below --\n";

    std::cout << "\n=== 4. weak_ptr: lock while alive, empty after reset ===\n";
    Session watcher(201, "Anna", first);  // stores weak_ptr
    watcher.printStatus();
    first->powerOn();
    watcher.start();
    watcher.addTime(30);
    watcher.end();
    first->powerOff();

    std::cout << "-- reset last shared_ptr owner --\n";
    first.reset();
    std::cout << "use_count after reset: " << first.use_count() << "\n";
    std::cout << "-- Session still exists; lock() must fail gracefully --\n";
    watcher.printStatus();
    watcher.start();  // rule: computer already destroyed

    std::cout << "\n=== 5. Arrays via make_unique (no new/delete) ===\n";
    {
        // Array of unique_ptr elements (objects with args — no default ctor needed for values)
        std::unique_ptr<std::unique_ptr<Computer>[]> seats =
            std::make_unique<std::unique_ptr<Computer>[]>(2);
        seats[0] = std::make_unique<Computer>(10, "PC-10", "RX-6600");
        seats[1] = std::make_unique<Computer>(11, "PC-11", "RTX-3060");
        for (int i = 0; i < 2; ++i) {
            seats[i]->powerOn();
            seats[i]->printStatus();
            seats[i]->powerOff();
        }
        std::cout << "-- leave array block: both Computers destroyed automatically --\n";
    }

    std::cout << "\n=== done ===\n";
    return 0;
}
