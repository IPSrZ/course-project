# Таблица владения (ЛР 2 → умные указатели)

| Где был указатель | На что указывает | Кто владеет | Заменяется на | Почему |
| --- | --- | --- | --- | --- |
| `Session::m_computer` (`Computer*`) | `Computer` | не Session: компьютер создаётся снаружи и переживает сеанс | `std::weak_ptr<Computer>` | чистая агрегация: сеанс наблюдает, не продлевает жизнь; `lock()` безопаснее висячего указателя из ЛР 2 |
| `main`: `Computer* shared = new Computer(...)` | `Computer` | код в `main` (один владелец) | `std::shared_ptr<Computer>` | из него делают `weak_ptr` для Session; нужен общий владелец, пока сеанс может обратиться к ПК |
| `main`: `Computer* row = new Computer[n]` | массив `Computer` | `main` | `std::unique_ptr<Computer[]>` **или** массив `unique_ptr<Computer>` через `make_unique` | один владелец массива; `delete[]` не нужен. В demo — массив `unique_ptr<Computer>`, т.к. у `Computer` удалён copy и нет удобного default-массива с аргументами |
| `main`: `Computer** seats` + `new Computer` на элемент | отдельные `Computer` | `main` | `std::unique_ptr<std::unique_ptr<Computer>[]>` + `make_unique<Computer>(...)` | каждый элемент — единственный владелец своего ПК; без `new`/`delete` |
| `main`: `Computer& ref` / `Computer* ptr` на стековый объект | `Computer` на стеке | стек / enclosing scope | не заменяется умным указателем | не владеющие параметры/алиасы; для кучи в demo используются smart pointers |
| поле `Computer::m_hardware` | `Hardware` | `Computer` | **не менять** — поле по значению | композиция: часть живёт и умирает с целым; указатель не нужен |

## Как выбраны три вида указателей в demo

- **`unique_ptr`** — единственный владелец `PC-02`; владение передаётся через `std::move`, исходный указатель пуст; объект уничтожается при выходе из блока.
- **`shared_ptr`** — `PC-03` / `PC-01`: несколько потенциальных владельцев и источник для `weak_ptr`; видно `use_count()`.
- **`weak_ptr`** — поле Session: агрегация с проверкой `lock()` до и после `reset()` последнего владельца.
