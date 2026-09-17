# Курсовой проект: администратор киберклуба

Консольная программа: места, клиенты, сеансы, ремонт железа.

## Языки
- C++ — папка cpp/
- Java — папка java/

## Структура
- cpp/include — заголовочные файлы
- cpp/src — исходники C++
- java/src — исходники Java
- docs — описание

## Сборка
C++:
g++ cpp/src/main.cpp -I cpp/include -o app
./app

Java:
cd java/src
javac Main.java
java Main

## Правила
Ветка main защищена. Изменения только через feature-ветку и Pull Request.
