#include "SanUSB48X.h"
#define zero   0b0111111
#define um     0b0000110
#define dois   0b1011011
#define tres   0b1001111
#define quatro 0b1100110
#define cinco  0b1101101
#define seis   0b1111101
#define sete   0b0000111
#define oito   0b1111111
#define nove   0b1101111

unsigned char seg[10] = {
    zero, um, dois, tres, quatro,
    cinco, seis, sete, oito, nove
};
int i;

void interrupt interrupcao() {}

void main(void) {
    clock_int_48MHz();
    TRISB = 0b00000000;
    while (1) {
        for (index = 9; index >= 0; index--) {
            PORTB = seg[index];
            tempo_ms(1000);
        }
    }
}
