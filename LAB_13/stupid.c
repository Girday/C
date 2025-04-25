// #include <stdio.h>
// #include <stdbool.h>
// #include <locale.h>
// #include <wchar.h>

// // Структура для проверки символа на гласную
// const unsigned int vowels[] = {
//     // Гласные для латиницы (малые и заглавные)
//     0x0000001, 0x0000002, 0x0000004, 0x0000008, 0x0000010, 0x0000020, // a, e, i, o, u, y
//     0x00000040, 0x00000080, 0x00000100, 0x00000200, // A, E, I, O, U, Y
    
//     // Добавь сюда другие гласные символы для кириллицы или других языков
//     // Пример для кириллицы:
//     0x00000400, 0x00000800, 0x00001000, 0x00002000, // а, э, и, о, у
//     0x00004000, 0x00008000  // ё, ю
// };

// // Проверка на гласную
// int is_vowel(wchar_t chr) {
//     for (int i = 0; i < sizeof(vowels) / sizeof(vowels[0]); i++) {
//         if (chr == vowels[i]) {
//             return 1; // символ является гласной
//         }
//     }
//     return 0; // символ не является гласной
// }

// // Функция для извлечения символа из UTF-8
// int get_utf8_char(FILE *f) {
//     unsigned char c = fgetc(f);
    
//     if (c == EOF) return EOF;

//     if (c < 0x80) return c; // Однобайтовый символ (ASCII)
    
//     unsigned char buffer[4];
//     buffer[0] = c;
    
//     // Многобайтовые символы
//     if (c >= 0xC0 && c <= 0xDF) {
//         // 2 байта
//         buffer[1] = fgetc(f);
//         return (buffer[0] & 0x1F) << 6 | (buffer[1] & 0x3F);
//     }
    
//     if (c >= 0xE0 && c <= 0xEF) {
//         // 3 байта
//         buffer[1] = fgetc(f);
//         buffer[2] = fgetc(f);
//         return (buffer[0] & 0x0F) << 12 | (buffer[1] & 0x3F) << 6 | (buffer[2] & 0x3F);
//     }
    
//     if (c >= 0xF0 && c <= 0xF7) {
//         // 4 байта
//         buffer[1] = fgetc(f);
//         buffer[2] = fgetc(f);
//         buffer[3] = fgetc(f);
//         return (buffer[0] & 0x07) << 18 | (buffer[1] & 0x3F) << 12 | (buffer[2] & 0x3F) << 6 | (buffer[3] & 0x3F);
//     }

//     return EOF;
// }

// int main() {
//     // Устанавливаем локаль для поддержки UTF-8
//     setlocale(LC_CTYPE, "");

//     int chr;
//     bool isvowel = true;
//     int count = 0;
//     int final = 0;

//     unsigned int word = 0;
//     unsigned int vowels_in_word = 0;
//     unsigned int letter = 0;

//     while ((chr = get_utf8_char(stdin)) != EOF) {
        
//         if (chr == ' ' || chr == '\t' || chr == '\n' || chr == EOF) {
//             // Разделитель слов
//             if (count == 1) {
//                 final++;
//             }

//             // Сброс текущих данных для нового слова
//             word = 0;
//             isvowel = true;
//             count = 0;
//             vowels_in_word = 0;
//         } else {
//             // Если это не разделитель
//             if (is_vowel(chr)) {
//                 // Если символ - гласная
//                 letter = 1u << (chr - 'a'); // Пример маски (переделать для универсальности)

//                 if ((vowels_in_word & letter) == 0) {
//                     word |= letter;
//                     vowels_in_word = word & vowels;
//                     count++;
//                 } else {
//                     isvowel = false;
//                     count = 0;
//                 }
//             } else {
//                 word |= letter;
//             }
//         }
//     }

//     // Результат
//     if (final != 0) {
//         printf("Yes! There're %d of them!\n", final);
//     } else {
//         printf("No\n");
//     }

//     return 0;
// }
