# libFuzz-тестирование 

#### Простой тест используя libFuzz
#### Сделано для задания.




## Installation

Установка llvm, gcovr и clang в Linux-Debian:

```bash
sudo apt install llvm

sudo apt install gcovr

sudo apt install clang
```

    
## Running programm

Чтобы запустить программу нужно для начала перейти в директорию проекта:

```bash
cd .vs/fuzztest
```
Компиляция:
```bash
clang++ -g -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer,address fuzztest2.cpp -o fuzz
```
Запустить программу и указать на директорию куда будем записывать файлы тестирования:
```bash
./fuzz in2
```
Считываем все раны для html-отчета:
```bash
./fuzz -runs=0 in2
```
Генерируем html-отчет:
```bash
llvm-profdata merge -sparse default.profraw -o fuzztest2.profdata
llvm-cov show --format=html ./fuzz -instr-profile=fuzztest2.profdata > coverage2.html
```

## Authors

- telegram: [alyssa](https://t.me/alyssaosipova)

