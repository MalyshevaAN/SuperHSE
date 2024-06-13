# SuperHSE

<p align="center">
    <img src="assets/images/super_hse.png" alt="logo" width="40%">
</p>

### Описание


Super-HSE – это игра-платформер со стилизацией под НИУ ВШЭ СПб в виде десктопного приложения под Linux. В игре пользователю предложено пройти несколько уровней; в процессе прохождения можно собирать виртуальную валюту – монетки ВШЭ – которая используется для приобретения дополнительных "жизней" (или доступа к различным скинам). Помимо этого на каждом уровне встречаются враги - их нужно либо обойти, либо уничтожить, прыгнув сверху. У игры есть два режима – singleplayer, в котором игрок полностью самостоятельно проходит все уровни, и multiplayer, где два игрока могут проходить уровень вместе: очищать друг другу путь от врагов и собирать монетки, которые начисляются обоим игрокам.

___

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

## Запуск игры

#### Для запуска singleplayer
```
mkdir build && cd build

cmake ../ && make

./super_hse
```

#### Для запуска multiplayer

Один из двух игроков должен запустить у себя сервер, после чего каждый из двух игроков запускает обычное приложение super-hse

**Запуск сервера**
```
mkdir build && cd build

cmake ../ && make

./server
```
После чего появится окно, на котором высветится ip-адрес, по которому игрокам нужно подключаться в режиме multiplayer.

---

Перед запуском может понадобиться прогнать папку files через dos2unix с помощью команды 
```
find ./assets/files -type f -exec dos2unix {} \;
```
