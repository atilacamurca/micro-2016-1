#include "SanUSB48X.h"
#define zero        0b0111111
#define um          0b0000110
#define dois        0b1011011
#define tres        0b1001111
#define quatro      0b1100110
#define cinco       0b1101101
#define seis        0b1111101
#define sete        0b0000111
#define oito        0b1111111
#define nove        0b1101111
#define apagado     0b00000000
#define verde_carro pin_a2
#define amarelo_carro pin_a3
#define vermelho_carro pin_a4
#define vermelho_pedestre pin_a1
#define verde_pedestre pin_a0
#define pin_dezena pin_c1
#define pin_unidade pin_c0

unsigned char seg[10] = {
    zero, um, dois, tres, quatro,
    cinco, seis, sete, oito, nove
};
int i, j, z, dezena, unidade, flag_pedestre = 0;

void interrupt interrupcao() {}

void tempo(int tempo) {
    for (j = 0; j < tempo; j += 100) {
        tempo_ms(100);
        if (!entrada_pin_e3) {
            flag_pedestre = 1;
        }
    }
}
