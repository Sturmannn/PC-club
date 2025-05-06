# PC-club

## 📦 Клонирование репозитория

Для корректной работы необходимо склонировать репозиторий **вместе с сабмодулями**:

```bash
git clone --recurse-submodules https://github.com/Sturmannn/PC-club.git
```

Если репозиторий уже был клонирован **без сабмодулей**, выполните:

```bash
git submodule update --init --recursive
```

---

## ⚙️ Сборка проектов

В репозитории находятся два C++ проекта:

- 🧩 **Sample** — основной проект с примером из документации.
- 🧪 **Tests** — модульный тест, написанный с использованием GoogleTest.

Сборка осуществляется с помощью **CMake** и **Ninja**. Необходим компилятор с поддержкой **C++20**.

### 🔧 Пример команд для сборки

1. Создайте отдельную директорию для сборки:

```bash
mkdir build
cd build
```

2. Сгенерируйте проект с помощью CMake и Ninja:

```bash
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
```

3. Соберите проект:

```bash
ninja -j4
cd ..
```

---

## ▶️ Запуск

📌 Запуск основного примера из корневой директории:

```bash
./bin/Sample <путь_к_входному_текстовому_файлу>
```
Например:
```bash
./bin/Sample /home/user/PC-club/test_file.txt
```

🧪 Запуск модульного теста из корневой директории:

```bash
./bin/Tests
```

---

## ✅ Требования

- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)
- Компилятор с поддержкой **C++20**
- [GoogleTest](https://github.com/google/googletest) (подключается как сабмодуль)
