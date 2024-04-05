# SuperHSE
Если нажать на кнопку:
- `L` (levels) переход на карту уровней
-  `1` (находясь на карте уровней): то произойдет переход в окно прохождения 1го уровня
- `M` (Main menu): переход в главное меню

## Зависимости 

- SFML - команда для установки:
```
sudo apt-get install libsfml-dev
```

- SQLite3 - команда для установки:
```
sudo apt-get install sqlite3 libsqlite3-dev
```

- LDtkLoader
    - скачать репозиторий: https://github.com/Madour/LDtkLoader
    - установить на wsl с помощью:

    ##### Build
    ```
    mkdir build && cd build
    cmake ../
    cmake --build . 
    ```

    ##### Install

    ```
    cmake ../
    cmake --install . 
    ```

    - Для подключения в проект в Cmake файл необходимо добавить:
    ```
    find_package(LDtkLoader 1.5)
    target_link_libraries(YourTarget PRIVATE LDtkLoader)
    ```

    **Для того, чтобы VSCode не ругался, нужно установить всё как на Windows, так и на Linux


## Запуск игры

```
mkdir build && cd build

cmake ../ && make

./super_hse
```

**Перед запуском прогоните папку files через dos2unix с помощью команды 
`find ./assets/files -type f -exec dos2unix {} \;`
