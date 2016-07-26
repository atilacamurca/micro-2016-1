# Introdução

Para a Prática 1 será necessário montar e soldar um circuito numa placa
SanUSB com os seguintes componentes:

* 1 Micro controlador PIC18F2550
* 1 LED
* 1 Cristal
* 1 Botão de _reset_
* 1 resistor $2.2K \Omega$
* 1 resistor $390 \Omega$
* 2 Capacitores $22pF$
* 2 Capacitores $1 \mu F$
* 1 Conector USB
* 1 Cabo USB
* 1 Diodo
* Bournes

# Objetivos

Fazer com que ao ser alimentado por cabo USB o microcontrolador acione
um LED de modo que ele permaneça piscando.

\begin{figure}[h]
	\includegraphics[scale=0.15]{img/placa-1.jpg}
	\caption{Placa montada}
\end{figure}

# Conclusão

A montagem é bem didática por que a placa vem a indicação exata de cada
componente. Além disso a gravação do programa fonte também é facilitada
graças a um programa que envia os dados pela porta USB e reseta o circuito.

A utilização de porta USB auxilia tanto na gravação quanto na alimentação
do circuito, visto que é um componente barato e que toda máquina moderna
possui por padrão.
