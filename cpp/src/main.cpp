#include "computer.hpp"
#include "session.hpp"

#include <iostream>

using namespace cyberclub;

int main() {
    std::cout << "=== 1. Composition + aggregation + rule ===\n";
    {
        Computer pc(1, "PC-01", "RTX-4060");
        pc.printStatus();

        std::cout << "-- correct: start session --\n";
        Session s(101, "Ivan", &pc);
        s.start();
        s.addTime(60);
        s.printStatus();
        pc.printStatus();

        std::cout << "-- violate: start again --\n";
        s.start();

        std::cout << "-- violate: repair while already ok, then break and fix --\n";
        pc.finishRepair();
        pc.requestRepair("GPU overheat");
        s.end();
        std::cout << "-- violate: start while broken --\n";
        s.start();
        pc.finishRepair();
        s.start();
        s.end();
        pc.powerOff();
    }

    std::cout << "\n=== 2. Lifetime: composition dies with whole ===\n";
    std::cout << "-- enter inner block --\n";
    {
        Computer nested(2, "PC-02", "i5-12400");
        nested.powerOn();
        nested.powerOff();
        std::cout << "-- leave inner block --\n";
    }
    std::cout << "-- after block: Computer and Hardware both destroyed --\n";

    std::cout << "\n=== 3. Lifetime: aggregation does not own ===\n";
    Computer* shared = new Computer(3, "PC-03", "Ryzen-5");
    {
        Session inner(201, "Anna", shared);
        inner.start();
        inner.addTime(30);
        inner.end();
        std::cout << "-- leave session block --\n";
    }
    std::cout << "-- session dead, computer still alive --\n";
    shared->printStatus();
    shared->powerOff();
    delete shared;

    std::cout << "\n=== 4. Reference and pointer ===\n";
    Computer stackPc(4, "PC-04", "GTX-1660");
    Computer& ref = stackPc;
    Computer* ptr = &stackPc;
    ref.powerOn();
    ptr->printStatus();
    Session byPtr(301, "Oleg", ptr);
    byPtr.start();
    byPtr.end();
    ref.powerOff();

    std::cout << "\n=== 5. Dynamic array of objects ===\n";
    const int n = 2;
    Computer* row = new Computer[n];
    row[0].printStatus();
    row[1].printStatus();
    delete[] row;

    std::cout << "\n=== 6. Array of dynamic objects ===\n";
    Computer** seats = new Computer*[n];
    seats[0] = new Computer(10, "PC-10", "RX-6600");
    seats[1] = new Computer(11, "PC-11", "RTX-3060");
    for (int i = 0; i < n; ++i) {
        seats[i]->powerOn();
        seats[i]->printStatus();
        seats[i]->powerOff();
    }
    for (int i = 0; i < n; ++i) {
        delete seats[i];
    }
    delete[] seats;

    std::cout << "\n=== done ===\n";
    return 0;
}
