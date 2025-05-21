import os
import sys
import random

def shuffle_and_split(input_file):
    route = "LabKP9_Grigorev_6_3/tests/"

    # Создаём директории keys и values, если их нет
    os.makedirs(f"{route}keys", exist_ok=True)
    os.makedirs(f"{route}values", exist_ok=True)
    
    # Получаем базовое имя файла (без пути)
    base_name = os.path.basename(input_file)
    
    # Формируем пути для выходных файлов
    key_file = os.path.join(f"{route}keys", base_name)
    value_file = os.path.join(f"{route}values", base_name)
    
    # Читаем все строки из входного файла
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"Ошибка: файл {input_file} не найден.")
        return
    except Exception as e:
        print(f"Ошибка при чтении файла {input_file}: {e}")
        return
    
    # Перемешиваем строки случайным образом
    random.shuffle(lines)
    
    # Открываем файлы для записи ключей и значений
    try:
        with open(key_file, 'w', encoding='utf-8') as kf, \
             open(value_file, 'w', encoding='utf-8') as vf:
            for line in lines:
                # Удаляем пробелы и символ новой строки
                line = line.strip()
                if not line:
                    continue  # Пропускаем пустые строки
                
                # Разделяем строку на ключ и значение
                try:
                    key, value = line.split(' ', 1)
                except ValueError:
                    print(f"Ошибка: строка '{line}' не соответствует формату 'ключ значение'.")
                    continue
                
                # Записываем ключ и значение в соответствующие файлы
                kf.write(key + '\n')
                vf.write(value + '\n')
                
        print(f"Файлы успешно созданы: {key_file} и {value_file}")
    except Exception as e:
        print(f"Ошибка при записи файлов: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Использование: python shuffle_split.py <входной_файл>")
        sys.exit(1)
    
    input_file = sys.argv[1]
    shuffle_and_split(input_file)