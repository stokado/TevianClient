# Графический интерфейс пользователя TevianClient

## WSL/Linux

---

**0. Установить WSL и Linux дистрибутив (опционально)**

* Установить [WSL](https://docs.microsoft.com/en-us/windows/wslinstall)
* Установить дистрибутив Linux (протестировано на Ubuntu 20.04 LTS)

---

**1. Обновляем базу данных с доступными пакетами и устанавливаем их**

	sudo apt update && sudo apt -y upgrade

---

**2. Устанавливаем интерфейс для WSL**

	sudo apt install xfce4      // установка интерфейса
    gdm3                        // выбираем default display manager
    nano .bashrc                // открываем файл
    
    Добавить в конец файла

    export DISPLAY=$(awk '/nameserver / {print $2; exit}' /etc/resolv.conf 2>/dev/null):0
    export LIBGL_ALWAYS_INDIRECT=1

    wsl --shutdown              // перезапускаем ОС (powershell)
    
    Открыть XLaunch

    Выбрать One large window или One window without titlebar
    Next
    Start no client
    Next
    Disable access control
    Next
    Finish    

    sudo xfce4-session          // запускаем интерфейс

---

**3. Устанавливаем пакеты и библиотеки для сборки**

	sudo apt install cmake              // Установка    CMake
	sudo apt install qt5-default        // Библиотека   Qt5
	sudo apt install libssl-dev         // Библиотека   OpenSSL
	sudo apt install build-essential    // Установка    компилятора

---

**4. Скачиваем Git репозиторий**
    
    git clone https://github.com/stokado/TevianClient

---

**5. Меняем директорию**

	* cd TevianClient/

---

**6. Собираем проект и компилируем код**

	* mkdir build/                  // папка для сконфигурированного проекта
	* cd build/                     // заходим в директорию с проектом
	* cmake ..                      // команда CMake для конфигурирования проекта в текущую папку
	* cmake --build .               // команда CMake для запуска компиляции с нативным компилятором из текущей папки
	* cd ../install/TevianClient    // заходим в директорию с установленными файлами

---

**7. Запуск программы**

    * ./TevianClient

---

## Windows

---

**1. Установливаем необходимые утилиты**

	OpenSSl
    CMake
    Qt5
    Ninja
    mingw

---

**2. Скачиваем Git репозиторий**
    
    git clone https://github.com/stokado/TevianClient

---

**3. Меняем директорию**

	* cd TevianClient/

---

**4. Собираем проект и компилируем код**

	* mkdir build/
	* cd build/
	* cmake -G Ninja ..     // используем генератор Ninja
	* cmake --build .       

---

**5. Запуск программы**

    TevianClient/install/TevianClient/TevianClient.exe

--- 

# Консольная утилита TevianClientCLI

Консольная утилита установливается в папку TevianClient/install/ClientCLI

**Запуск через командную строку**

	./TevianClientCLI path/to/image1 path/to/image2     // linux
    .\TevianClientCLI path/to/image1 path/to/image2     // windows
    
Программа принимает N аргументов, пути до изображений

Выйти из приложения можно с помощью комбинации клавиш Ctrl + C