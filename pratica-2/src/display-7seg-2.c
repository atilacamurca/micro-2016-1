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
#define pin_dezena pin_c1
#define pin_unidade pin_c0

unsigned char seg[10] = {
    zero, um, dois, tres, quatro,
    cinco, seis, sete, oito, nove
};
int i, z, dezena, unidade;

void interrupt interrupcao() {}

void main(void) {
    clock_int_48MHz();
    TRISB = 0b00000000;
    TRISC = 0b000;
    while (1) {
        for (i = 0; i < 99; i++) {
            for (z = 0; z < 100; z++) {
                dezena = i / 10;
                unidade = i % 10;

                nivel_baixo(pin_dezena);
                nivel_alto(pin_unidade);

                PORTB = seg[dezena];
                tempo_ms(5);

                nivel_baixo(pin_unidade);
                nivel_alto(pin_dezena);

                PORTB = seg[unidade];
                tempo_ms(5);
            }
        }
    }
}
