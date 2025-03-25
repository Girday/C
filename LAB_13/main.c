#include <stdio.h>
#include <stdint.h>

#include "codes.h"

int counter(uint64_t word) {

    int counter = 0;

    while (word) {

        if (word % 2 == 1)
            counter++;
        
        word /= 2;

    }

    return counter;

}

int issep(int chr) {

    return chr == ' ' || chr == ',' || chr == '\t' || chr == '\n' || chr == EOF;

}

int unicode(int chr) {

    if (chr != EOF && chr < 128)
        return chr;
    
    if ((chr & 0b11100000) == 0b11000000)
        return (chr & 0b00011111) << 6 | (getchar() & 0b00111111); 

    if ((chr & 0b11110000) == 0b11100000)
	return (chr & 0b00001111) << 12 | (getchar() & 0b00111111) << 6 | (getchar() & 0b00111111);

    if ((chr & 0b11111000) == 0b11110000)
	return (chr & 0b00000111) << 18 | (getchar() & 0b00111111) << 12 | (getchar() & 0b00111111) << 6 | (getchar() & 0b00111111);

    return -1;

}


int index_in_mask(int chr) {

    if ('a' <= chr && chr <= 'z')
        return chr - 'a' + 34;
    
    if ('A' <= chr && chr <= 'Z')
        return chr - 'A' + 34;

    if (sma_a <= chr && chr <= sma_ya)
        return chr - sma_a > 6 ? chr - sma_a : (chr - sma_a) + 1; 

    if (big_a <= chr && chr <= big_ya)
        return chr - big_a > 6 ? chr - big_a : (chr - big_a) + 1; 
    
    if (chr == sma_ee || chr == big_ee)
        return 6;
    
    return -1;

}

#define set_bit(set, chr) ((set) |= (1ull << index_in_mask(chr)))

uint64_t mask() {

    uint64_t set = 0;

    set_bit(set, big_a);
    set_bit(set, big_e);
    set_bit(set, big_yo);
    set_bit(set, big_o);
    set_bit(set, big_i);
    set_bit(set, big_u);
    set_bit(set, big_ii);
    set_bit(set, big_ee);
    set_bit(set, big_yu);
    set_bit(set, big_ya);

    set_bit(set, 'A');
    set_bit(set, 'E');
    set_bit(set, 'Y');
    set_bit(set, 'U');
    set_bit(set, 'I');
    set_bit(set, 'O');

    return set;

}

enum state {

    IN_WORD,
    OUT_WORD
    
};

enum again {

    ZERO,
    ONE,
    MANY

};

int main() {

    uint64_t vowels = mask();
    uint64_t vowels_in_word = 0;

    enum state state = OUT_WORD; 
    enum again again = ZERO;
    
    int final = 0;
    int chr;

    while ((chr = unicode(getchar())) != EOF) {

        if (state == OUT_WORD)
            if (!issep(chr)) 
                state = IN_WORD;

        if (state == IN_WORD) {

            if (issep(chr)) {

                state = OUT_WORD;
                
                if (again == ONE)
                    final = 1;

                vowels_in_word = 0;
                again = ZERO;

            }

            else {

                uint64_t new_one = 1ull << index_in_mask(chr);
                uint64_t vowels_in_word_plus_new = vowels_in_word | new_one;

                if ((vowels_in_word_plus_new == vowels_in_word) && (new_one & vowels)) {

                    if (again == ONE)
                        again = MANY;
                
                }

                else if ((vowels_in_word_plus_new & vowels) == vowels_in_word_plus_new) {

                    int count_ones = counter(vowels_in_word_plus_new);

                    if (count_ones > 1)
                        again = MANY; 
                    else if (count_ones < 1)
                        again = ZERO;
                    else
                        again = ONE;

                    vowels_in_word = vowels_in_word_plus_new;
             
                }
            }
        }
    } 

    
    if (final == 1)
        printf("Yes!\n");
    else
        printf("No\n");

}
