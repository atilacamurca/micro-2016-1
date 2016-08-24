#include "SanUSB48X.h"

void interrupt interrupcao() {}

void main(void) {
    clock_int_48MHz();
    while (1) {
        nivel_alto(pin_b7);
        tempo_ms(3000);
        nivel_baixo(pin_b7);

        nivel_alto(pin_b6);
        tempo_ms(1000);
        nivel_baixo(pin_b6);

        nivel_alto(pin_b5);
        tempo_ms(3000);
        nivel_baixo(pin_b5);
    }
}
