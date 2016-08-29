# Introdução

O Jogo Frets On Fire tem o objetivo de simular que
o jogador seja um astro do rock. A intenção é que
ele possa tocar músicas simulando instrumentos como
guitarra, baixo e bateria.

Esse jogo usa o Teclado do computador como entrada
das notas musicais. A bateria utiliza 5 comandos do
teclado.

Sendo assim é possível criar uma plataforma de entrada
de dados usando um microcontrolador e piezos elétricos
para captar as batidas do usuário e enviá-las para o jogo,
ou seja, transformar sinais elétricos em comandos do teclado.

# Material Necessário

* 5 Piezos Elétricos
* 1 Arduino
* 5 Resistores <!-- TODO: incidar valor da resitência -->
* Fios
* 1 Breadboard
* 1 par de Baquetas
* 7 folhas de EVA (2 pretas, 1 vermelha, 1 amarela, 1 azul, 1 verde)
* Pistola e bastões de cola quente

# Objetivos

O objetivo desse projeto é captar as batidas do usuário através dos
piezos, enviar um sinal como se fosse o teclado relacionando o piezo
a uma tecla.

O jogo pode ser configurado para receber qualquer tecla. Com isso é posível
até rodar o jogo em modo _multiplayer_, sem que haja conflito de teclas.
O jogador que irá simular a guitarra ou o baixo pode utilizar as teclas:

* `1` (Nota Verde),
* `2` (Nota Vermelha),
* `3` (Nota Amarela),
* `4` (Nota Azul),
* `5` (Nota Laranja),
* `/` (Palheta 1),
* `*` (Palheta 2),
* `-` (_Star Power_)
* e `8` (Alavanca);

enquanto o jogador da bateria pode utilizar as teclas:

* `a` (Nota Vermelha),
* `e` (Nota Amarela),
* `h` (Nota Azul),
* `j` (Nota Verde),
* `<espaço>` (Pedal),

por exemplo.

# Cronograma

-------------------------------------------------------------------------------
Tarefas                              Semana 1   Semana 2   Semana 3   Semana 4
-----------------------------------  ---------  ---------  ---------  ---------
Aquisição do Material                    X

Protótipo Inicial                        X

Montagem do circuito                                X

Programação                                         X          X

Testes                                                         X

Relatório                                X                                X
-------------------------------------------------------------------------------

Table: Cronograma

# Referências

<!-- TODO -->
* Frets On Fire
* FoFiX
* Arduino
* Arduino IDE