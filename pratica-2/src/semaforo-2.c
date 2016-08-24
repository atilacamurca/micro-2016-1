#include "SanUSB48X.h"
void interrupt interrupcao() {}

#define verde_carro pin_b7
#define amarelo_carro pin_b6
#define vermelho_carro pin_b5

#define vermelho_pedestre pin_b3
#define verde_pedestre pin_b1

int flag_pedestre = 0, i;

void tempo(int tempo) {
    for (i = 0; i < tempo; i += 100) {
        tempo_ms(100);
        if (! entrada_pin_e3) {
            flag_pedestre = 1;
        }
    }
}

void main(void) {
    clock_int_48MHz();
        while (1) {
        nivel_alto(vermelho_pedestre);
        nivel_baixo(vermelho_carro);

        nivel_alto(verde_carro);
        tempo(10000);
        nivel_baixo(verde_carro);

        if (flag_pedestre) {
            nivel_alto(amarelo_carro);
            tempo_ms(1000);
            nivel_baixo(amarelo_carro);

            nivel_alto(vermelho_carro);
            nivel_baixo(vermelho_pedestre);

            nivel_alto(verde_pedestre);
            tempo_ms(5000);
            nivel_baixo(verde_pedestre);
            flag_pedestre = 0;
        }
    }
}
