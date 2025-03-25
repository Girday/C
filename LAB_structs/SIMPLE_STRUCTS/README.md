## Компиляция

Для компиляции программы используйте следующую команду:

```sh
gcc main.c structs.c -o main
```

## Запуск тестов

### Все тесты (без ключей)

```sh
./main
```

### Тестирование только STATIC структур

```sh
./main -s
```

### Тестирование только DYNAMIC структур

```sh
./main -d
```

## Тестирование отдельных структур

### Статические структуры:
```sh
./main -s stack   # Тестирование static_stack
./main -s queue   # Тестирование static_queue
./main -s deque   # Тестирование static_deque
```

### Динамические структуры:
```sh
./main -d stack   # Тестирование dynamic_stack
./main -d queue   # Тестирование dynamic_queue
./main -d deque   # Тестирование dynamic_deque
```

## Исключения (ошибки)

При выполнении программы могут возникнуть следующие исключения:

| Ключ | Описание |
|------|----------|
| `-Ess` | Ошибка в `static_stack` |
| `-Esq` | Ошибка в `static_queue` |
| `-Esd` | Ошибка в `static_deque` |
| `-Eds` | Ошибка в `dynamic_stack` |
| `-Edq` | Ошибка в `dynamic_queue` |
| `-Edd` | Ошибка в `dynamic_deque` |
