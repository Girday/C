#include <stdio.h>


enum state {
    IN_WORD_LIMBO,
    IN_WORD_NOT_NUM,
    IN_WORD_SIGN,
    IN_WORD_DIGITS,
    OUT_WORD
};


int is_separator(char chr) {
    return chr == ' ' || chr == '\t' || chr == '\n' || chr == EOF;
}


int which_digit(char digit) {
    return digit - '0';
}


int main() {
    enum state state = OUT_WORD; 

    int chr, pred_fin_sum = 0, fin_sum = 0, cur_sum = 0;

    do {
                
        if (state == OUT_WORD) {

            if (!is_separator(chr)) {
                state = IN_WORD_LIMBO;

                if (chr == '+' || chr == '-') {
                    state = IN_WORD_SIGN;
                }

                else if ('0' <= chr && chr <= '9') {
                    state = IN_WORD_DIGITS;
                    cur_sum += which_digit(chr);
                }

                else {
                    state = IN_WORD_NOT_NUM;
                }
                
            }
        }

        else if (state == IN_WORD_SIGN) {
            
            if (is_separator(chr)) {
                state = OUT_WORD;
            }
            
            else if ('0' <= chr && chr <= '9') {
                state = IN_WORD_DIGITS;
                cur_sum += which_digit(chr);
            }

            else {
                state = IN_WORD_NOT_NUM;
            }

        }

        else if (state == IN_WORD_DIGITS) {

            if (is_separator(chr)) {
                state = OUT_WORD;

                pred_fin_sum = fin_sum;
                fin_sum = cur_sum;
                cur_sum = 0;
            }
            
            else if ('0' <= chr && chr <= '9') {
                cur_sum += which_digit(chr);
            }

            else {
                state = IN_WORD_NOT_NUM;
            }

        }

        else if (state == IN_WORD_NOT_NUM) {

            if (is_separator(chr)) {
                state = OUT_WORD;
            }

        }
        
    } while ((chr = getchar()) != EOF);

    printf("Answer: %d\n", pred_fin_sum);
}
