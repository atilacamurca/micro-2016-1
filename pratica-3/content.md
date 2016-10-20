# Introdução

Para a prática 3 será necessário montar um circuito que irá realizar
comunicação serial com equipamento externo, no caso o PIC18F4550 na
plataforma SanUSB comunicando-se com um ESP8266.

# Objetivo

Enviar um valor inteiro para o ESP8266 através de uma URL
para que o ESP8266 identifique o valor e envie através de porta
serial o valor para o PIC18F4550 fazendo com que ele interrompa e
inicie o processo de alternar LEDs para um sinal de pedestres e automóveis.

# Comunicação

Ao receber uma requisição HTTP, com uma URL do tipo `http://172.24.2.95/?val=10`,
o ESP8266 obtém o seguinte _payload_:

~~~
GET /?val=10 HTTP/1.1
Host: 172.24.2.95
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
~~~

Logo na primeira linha está o valor que desejamos enviar ao PIC.

Abaixo um trecho do codigo fonte (Linguagem Lua):

~~~lua
-- a simple http server
srv = net.createServer(net.TCP)
srv:listen(80, function(conn)
    conn:on("receive", function(sck, payload)
        if string.match(payload, "val=") then
            tempo = string.match(payload, '%d+')
            print(tempo)
        end
        
        sck:send("HTTP/1.0 200 OK\r\n"
        	.. "Content-Type: text/html\r\n\r\n<h1>"
        	.. "Iniciando semáforo com tempo de "
            .. tempo
            .. " segundos<br>Transmitido via ESP8266</h1>")
    end)
end)
~~~

A ideia é que quando o payload conter a String `val=` (linha 5), então
o tempo é obtido através do _regex_ (Regular Expression) `%d+`, indicando
que é um valor inteiro, um dígito ou mais (linha 6). Finalmente o ESP envia o valor
para a porta serial (linha 7) através de um `print`.

# Circuito

As Figuras \ref{fig:circuito1}, \ref{fig:circuito2} e \ref{fig:circuito3} mostram a evolução
do circuito.

\begin{figure}[h]
	\centering
	\includegraphics[scale=0.5]{img/vlcsnap-2016-10-20-16h24m17s640.png}
	\caption{Montagem Inicial apenas com 1 display de 7 segmentos}\label{fig:circuito1}
\end{figure}

\begin{figure}[h]
	\centering
	\includegraphics[scale=0.5]{img/vlcsnap-2016-10-20-16h24m03s183.png}
	\caption{Envio de comando apenas para ligar, ainda sem indicar valor}\label{fig:circuito2}
\end{figure}

\begin{figure}[h]
	\centering
	\includegraphics[scale=0.5]{img/IMG_20161006_103716.jpg}
	\caption{Circuito Final, com semáforo e valor passado via porta serial com 2 displays de 7 segmentos}\label{fig:circuito3}
\end{figure}

# Recepção serial

Para receber o valor pela serial foi usado a opção de verificar se houve
interrupção e ler o valor da porta serial. Abaixo um trecho do código:

~~~c
char char_byte;
char comando[2];
int pos = 0;
int valor_recebido = 0;
void interrupt interrupcao() {
    if (serial_interrompeu) {
        serial_interrompeu = 0;
        char_byte = ReadUSART();
        // recebe bytes até '\n'
        if (char_byte != '\n') {
            comando[pos] = char_byte;
            pos++;
        } else {
            valor_recebido = 1;
            pos = 0;
        }
    }
}
~~~