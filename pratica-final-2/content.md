# Introdução

O aplicativo \wm tem o objetivo de permitir que
desenvolvedores de sistemas embarcados possam enviar para a nuvem
os dados obtidos por seu equipamento IOT e visualizá-los no navegador.

Em equipamentos que usam microcontroladores não existe a figura de
um monitor em que se possa verificar a saída dos comandos e acompanhar
sua execução, existem apenas saídas seriais ou placas wifi embutidas.
Daí surge a necessidade de criar sistemas que possam recolher os dados
enviados por esses equipamentos e mostrá-los de forma apropriada.

# Objetivos

O objetivo principal é fornecer uma _api_ leve e simples, visto que
equipamentos IOT são limitados, para enviar e receber informações da
nuvem.

Para que haja melhor intercâmbio das informações tanto partindo do equipamento
IOT quanto chegando o protocolo de comunicação escolhido foi o JSON, que segundo
Douglas Crockford é um formato leve e de linguagem independente para troca de
informações \cite{crockford-2015}.

Tendo isso em vista, vejamos os passos para criar um projeto.

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

# Justificativa

Sendo um aplicativo de código-fonte licenciado pela GPLv3 poderá ser usado
tanto para professores e alunos de cursos superiores e técnicos para estudo
de microcontroladores, sistemas embarcados e afins, como para empresas ou
pessoas que queiram interagir com seus equipamentos pessoais.

A linguagem de programação escolhida foi o PHP, a qual é fácil de aprender,
normalmente lecionada em cursos superiores e técnicos e de hospedagem barata.

Outra característica a ser levada em conta é a forma de autenticação.
Uma autenticação convencional envolve a troca de _cookies_ entre servidor
e cliente, além de espaço em disco para guardar tais informações. Em sistemas
IOT que se supoem que possam crescer de forma rápida, ou seja, o número
de equipamentos pode aumentar, é necessário um sistema de autenticação capaz
de ser escalável mesmo em condições limitadas. Para isso foi utilizado o padrão
JWT (ou _JSON Web Tokens_), que é um padrão aberto (RFC 7519 \cite{rfc7519-2015})
que define uma maneira compacta e auto-contida
de transmitir de forma segura informações entre pares através de um objeto
JSON \cite{jwt-2016}. Esta informação pode ser verificada e confirmada pois é
assinada digitalmente. Informações JWT podem ser assinadas usando um segredo
(com o algoritmo HMAC \cite{rfc2104-1997}) ou um par de chave pública e
privada usando RSA \cite{rfc3447-2003}.

\begin{figure}[h]
	\includegraphics[scale=0.3]{img/jwt-diagram.png}
	\caption{Diagrama do processo de autenticação - Fonte: https://cdn.auth0.com/content/jwt/jwt-diagram.png}
\end{figure}

# Revisão Teórica

Muitas são as soluções de monitoramento de equipamentos IOT, grandes empresas
com Oracle, Amazon, Google, Microsoft; além de outras soluções livres como
Kaa, ThingSpeak, macchina.io, SiteWhere \cite{postscapes-iot-2016}.

O grande desafio é permitir a extensão da ferramenta para necessidades específicas.
Ferramentas com o Kaa permitem criar módulos próprios, sistemas de análises e
modelo de dados, fazendo com que a ferramenta se adapte ao que você precisa
\cite{kaa-2014}.

De forma semelhante outras ferramentas como macchina.io oferecem opções de
criar _bundles_ \cite{macchina.io-2016}, o ThingSpeak oferece opção de
criar _apps_, que podem envolver visualização em gráficos e tomada de
decisões \cite{thingspeak-2016}.

Nesse sentido a ferramenta proposta possui um sistema de plugins, que são
desenvolvidos como _Laravel Packages_ \cite{laravel-packages-2016}. Cada
nova funcionalidade é criada através da ferramenta _Laravel_ e pode
ser desenvolvida e habilitada localmente.

A proposta é ter uma tela de acompanhamento dos dados captados do equipamento
e a visualizaçãos ser específica. A documentação em português do brasil
para criar um novo plugin pode ser encontrada em
<https://sanusb-grupo.github.io/wireless-monitor/pt-br/plugin-development.html>.

<!-- TODO: referenciar: https://blog.profitbricks.com/top-49-tools-internet-of-things/ -->

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