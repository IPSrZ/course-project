# Lab 03 — C++ smart pointers

Те же классы киберклуба, что в ЛР 2. Обычные указатели заменены на умные.
Композиция `Computer → Hardware` остаётся полем по значению.
Агрегация `Session → Computer` — `std::weak_ptr<Computer>`.

Таблица владения: [ownership.md](ownership.md).

## Сборка и запуск

```bash
g++ -std=c++17 -Wall -Wextra -I include \
  src/main.cpp src/hardware.cpp src/computer.cpp src/session.cpp \
  -o app
./app
```
