# Introdução

O aplicativo Wireless Monitor tem o objetivo de permitir que um
desenvolvedor de sistemas embarcados possam enviar para a nuvem
os dados obtidos por seu equipamento IOT e visualizá-los no navegador.

# Objetivos

A ideia principal é criar uma _api_ leve e simples, visto que
equipamentos IOT são limitados. Tendo isso em vista, vejamos os
passos para criar um projeto.

## Cadastro do desenvolvedor

O desenvolvedor inicialmente deve fazer um cadastro simples na ferramenta.
Esse cadastro irá criar para ele uma `api_key`, ou seja, uma chave
única no formato UUIDv4.

## Criar um _Monitor_

Um _Monitor_ é um componente interno do sistema criado pelo desenvolvedor
de acordo com sua necessidade, é o instrumento que caracteriza os dados
coletados e os apresenta na interface web.

Imagine que o desenvolvedor queira medir a temperatura de um ambiente
e acompanhar suas variações. Para isso ele deve criar um _Monitor_ de
Temperatura, que apenas recebe um valor a um certo intervalo de tempo.
Dessa forma o desenvolvedor pode acompanhar as variações ou ainda
ver em forma de gráfico um conjunto de variações de um período de tempo
anterior.

Da mesma forma que uma chave UUID é criada para o desenvolvedor, uma
chave é criada para o Monitor - `monitor_key`.

## Autenticação do equipamento

Para autenticar e identificar o desenvolvedor e seu _monitor_ é preciso
enviar a `api_key` e a `monitor_key` via método _POST_ para o _endpoint_
`/api/authenticate`. Em caso positivo o sistema irá retornar um _token_.
Esse _token_ servirá para qualquer troca de informações futuras entre
o equipamento IOT e o sistema. Esse método de autenticação é chamado de
JWT ou _JSON Web Token_, um padrão internacional _RFC 7519_ para intercâmbio
de dados entre entidades.

Após ter o _token_ o desenvolvedor deve passá-lo através da _Header HTTP_
denominada _Authorization_ usando _schema Bearer_. Algo do tipo:

~~~
Authorization: Bearer <token>
~~~

Um _token_ é formado pelas seguintes informações:

* _Header_
* _Payload_
* _Signature_

Essa é uma forma segura e com pouco custo de memória. Além de ser
uma forma de autenticação _stateless_, em que não são usadas sessões
e nem mesmo _cookies_.

## Envio dos dados

Além do cabeçalho contendo o _token_ o usuário deve passar os valores
coletados pelo equipamento e enviar para o sistema. Para isso ele
deve enviar uma requisição _POST_ para o _endpoint_ `/api/send`,
com o atributo `data` contendo um JSON com os dados.

No exemplo do _Monitor_ de temperatura é necessário enviar apenas
o valor, algo do tipo:

~~~
{
	"value": 23.89
}
~~~

Sumarizando o código final seria algo como:

~~~
HTTPClient http;
http.begin("https://wireless-monitor.site/api/send");
http.addHeader("Content-Type", "application/json");
http.addHeader("Authorization", "Bearer <token>");
http.POST("data={value:23.89}");
http.writeToStream(&Serial);
http.end();
~~~

## Visualização dos dados

Após captar e enviar dados do IOT para a nuvem é possível acompanhar
os resultados pelo sistema. A forma de visualização será como mostra a
Figura \ref{fig:view-monitor}

\begin{figure}[h]
	\includegraphics[scale=0.5]{img/wm-monitor-temperature.png}
	\caption{Visualização dos dados na web} \label{fig:view-monitor}
\end{figure}

# Cronograma

-------------------------------------------------------------------------------
Tarefas                              Semana 1   Semana 2   Semana 3   Semana 4
-----------------------------------  ---------  ---------  ---------  ---------
Protótipo Inicial                        X

Programação                              X          X          X

Testes                                                         X          X

Relatório                                X                                X
-------------------------------------------------------------------------------

Table: Cronograma