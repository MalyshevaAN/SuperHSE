# SuperHSE

<p align="center">
    <img src="assets/images/super_hse.png" alt="logo" width="40%">
</p>

### Описание

Это игра-платформер со стилизацией под НИУ ВШЭ СПб в виде десктопного приложения под Linux. В игре пользователю предложено пройти несколько уровней. В процессе прохождения можно собирать виртуальную валюту – монетки ВШЭ – которая может быть использована для приобретения новых скинов и восстановления – покупки ИУП'а во время игры. Помимо этого на каждом уровне встречаются враги - их нужно либо перепрыгнуть, либо уничтожить, прыгнув сверху. 

У игры есть два режима: одиночное прохождение уровней и мультиплеер для совместного прохождения уровня вместе с другом по локальной сети.

![Game Preview](assets/images/preview.png)

![Gameplay](assets/images/gameplay.gif)

### Восстановление

![Respawn](assets/images/respawn.gif)

### Магазин уникальных скинов

![Shop](assets/images/shop.gif)

## Зависимости 

- SFML - команда для установки:
```
sudo apt-get install libsfml-dev
```

- SQLite3 - команда для установки:
```
sudo apt-get install sqlite3 libsqlite3-dev
```

- CryptoPP
    
Установить на wsl с помощью:
```
sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils
make
sudo make install
```

- LDtkLoader

Скачать репозиторий: https://github.com/Madour/LDtkLoader и установить на wsl с помощью:

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

Для подключения в проект в Cmake файл необходимо добавить:
```
find_package(LDtkLoader 1.5)
target_link_libraries(YourTarget PRIVATE LDtkLoader)
```

## Запуск игры

```
mkdir build && cd build

cmake ../ && make

./super_hse
```

Перед запуском может понадобиться прогнать папку files через dos2unix с помощью команды 
```
find ./assets/files -type f -exec dos2unix {} \;
```
