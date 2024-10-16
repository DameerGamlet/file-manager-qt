##!/bin/bash

# Получаем текущую директорию
PROJECT_DIR=$(pwd)

# Директория для сборки (можно использовать отдельную папку "build")
BUILD_DIR="$PROJECT_DIR/build"

# Шаблон для поиска исполняемых файлов (имя проекта — имя директории проекта по умолчанию)
TARGET_NAME=$(basename "$PROJECT_DIR")

# Создаем папку для сборки, если она еще не существует
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Переходим в папку сборки
cd "$BUILD_DIR" || exit

# Запускаем cmake, чтобы сгенерировать Makefile
cmake .. || { echo "CMake configuration failed."; exit 1; }

# Запускаем make для сборки проекта
make || { echo "Make failed."; exit 1; }

# Находим исполняемый файл
EXECUTABLE=$(find . -maxdepth 1 -type f -executable -name "$TARGET_NAME*")

# Если исполняемый файл найден, запускаем его
if [[ -x "$EXECUTABLE" ]]; then
    echo "Running $EXECUTABLE"
    "$EXECUTABLE"
else
    echo "Executable not found!"
    exit 1
fi
!#!/bin/bash

# Получаем текущую директорию
PROJECT_DIR=$(pwd)

# Директория для сборки (можно использовать отдельную папку "build")
BUILD_DIR="$PROJECT_DIR/build"

# Шаблон для поиска исполняемых файлов (имя проекта — имя директории проекта по умолчанию)
TARGET_NAME=$(basename "$PROJECT_DIR")

# Создаем папку для сборки, если она еще не существует
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Переходим в папку сборки
cd "$BUILD_DIR" || exit

# Запускаем cmake, чтобы сгенерировать Makefile
cmake .. || { echo "CMake configuration failed."; exit 1; }

# Запускаем make для сборки проекта
make || { echo "Make failed."; exit 1; }

# Находим исполняемый файл
EXECUTABLE=$(find . -maxdepth 1 -type f -executable -name "$TARGET_NAME*")

# Если исполняемый файл найден, запускаем его
if [[ -x "$EXECUTABLE" ]]; then
    echo "Running $EXECUTABLE"
    "$EXECUTABLE"
else
    echo "Executable not found!"
    exit 1
fi
/bin/bash

# Получаем текущую директорию
PROJECT_DIR=$(pwd)

# Директория для сборки (можно использовать отдельную папку "build")
BUILD_DIR="$PROJECT_DIR/build"

# Шаблон для поиска исполняемых файлов (имя проекта — имя директории проекта по умолчанию)
TARGET_NAME=$(basename "$PROJECT_DIR")

# Создаем папку для сборки, если она еще не существует
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Переходим в папку сборки
cd "$BUILD_DIR" || exit

# Запускаем cmake, чтобы сгенерировать Makefile
cmake .. || { echo "CMake configuration failed."; exit 1; }

# Запускаем make для сборки проекта
make || { echo "Make failed."; exit 1; }

# Находим исполняемый файл
EXECUTABLE=$(find . -maxdepth 1 -type f -executable -name "$TARGET_NAME*")

# Если исполняемый файл найден, запускаем его
if [[ -x "$EXECUTABLE" ]]; then
    echo "Running $EXECUTABLE"
    "$EXECUTABLE"
else
    echo "Executable not found!"
    exit 1
fi

