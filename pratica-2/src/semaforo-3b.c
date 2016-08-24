void main(void) {
    clock_int_48MHz();
    TRISB = 0b00000000;
    TRISA = 0b000000;
    TRISC = 0b000;
    nivel_baixo(amarelo_carro);
    nivel_baixo(verde_carro);
    nivel_baixo(verde_pedestre);

    while (1) {
        nivel_alto(vermelho_pedestre);
        nivel_baixo(vermelho_carro);
        nivel_alto(verde_carro);
        tempo(5000);
        nivel_baixo(verde_carro);

        if (flag_pedestre) {
            nivel_alto(amarelo_carro);
            tempo_ms(1000);
            nivel_baixo(amarelo_carro);
            nivel_alto(vermelho_carro);
            nivel_baixo(vermelho_pedestre);
            nivel_alto(verde_pedestre);

            for (i = 20; i >= 0; i--) {
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
            nivel_baixo(verde_pedestre);
            PORTB = apagado;
            flag_pedestre = 0;
        }
    }
}
