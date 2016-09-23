# Introdução

Com a crescente adoção de equipamentos IOT, como por exemplo o Raspberry Pi que
em quase 5 anos vendeu 10 milhões de unidades pelo mundo \cite{raspberry-pi-blog:2016},
para monitoramento de sensores e acionamento de cargas, cresce também a necessidade
de ambientes de acompanhamentos de tais
medições. Para isso uma das melhores formas é usar a nuvem para fazer o
armazenamento, já que uma das caracteristicas dos equipamentos IOT é o acesso
a internet. Para atender essa necessidade surge a ideia de criar um aplicativo
web e livre que possa captar informações destes dispositivos e que o acesso
possa acontecer em qualquer lugar.

# Objetivos

O objetivo principal do \wm é fornecer uma _api_ leve, simples e segura, visto que
equipamentos IOT são limitados, para enviar e receber informações da
nuvem.

Para que haja melhor intercâmbio das informações tanto partindo do equipamento
IOT quanto chegando o protocolo de comunicação escolhido foi o JSON, que segundo
Douglas Crockford é um formato leve e de linguagem independente para troca de
informações \cite{crockford-2015}.

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
	\centering
	\includegraphics[scale=0.3]{img/jwt-diagram-grey.png}
	\caption{Diagrama do processo de autenticação - Fonte: https://cdn.auth0.com/content/jwt/jwt-diagram.png}
\end{figure}

# Revisão Teórica

Muitas são as soluções de monitoramento de equipamentos IOT, desde grandes empresas
como Oracle, Amazon, Google, Microsoft; até soluções livres como
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

## Comparativo com outras ferramentas livres

----------------------------------------------------------------------
Aplicativo        Ambiente do Servidor   Suporte a plugins   SDK
-----------       --------------------   ------------------  ----------
Kaa               Java                     Sim                 Sim

macchina.io       C++/NodeJS               Sim                 Sim

SiteWhere         Java                     Sim                 Sim

ThingSpeak        Ruby                     Sim                 Sim

Wireless Monitor  PHP                      Sim                 Não
----------------------------------------------------------------------

# Arquitetura

É necessário um Servidor, um equipamento IOT, seja ESP8266 ou Raspberry Pi com Arduino;
e um navegador de internet no cliente.

A arquitetura segue o modelo da Figura \ref{fig:arquitetura}.

\begin{figure}[h]
	\centering
	\includegraphics[scale=0.45]{img/arquitetura-grey.png}
	\caption{Arquitetura} \label{fig:arquitetura}
\end{figure}

# Aplicação

Vejamos um passo a passo de como o aplicativo funciona.

## Cadastro do desenvolvedor

O desenvolvedor inicialmente deve fazer um cadastro simples na ferramenta.
Esse cadastro irá criar para ele uma `api_key`, ou seja, uma chave
única no formato UUID 4 \cite{rfc4122:2005}.

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
o equipamento IOT e o sistema.

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

## Descrição dos componentes

Neste tópico são descritos os componentes e as ferramentas utilizadas para o
desenvolvimento e uso do plugin de Temperatura.

### Sistema embarcado linux

Foi utilizado a plataforma Raspberry Pi como sistema embarcado, que irá servir
para cominucação com o Servidor e a plataforma Arduino. É um equipamento IOT
capaz de interagir com outros dispositivos e com acesso a internet.

### Microcontrolador

A plataforma Arduino foi escolhida para servir de ponte entre o componente
de medição de temperatura e o sistema embarcado.

### Sensor de temperatura

Como sendor de temperatura foi usado o LM35 da Texas Instruments.
A série LM35 é composta de dispositivos de circuito integrado para medição
de temperatura com a tensão de saída linearmente proporcional a temperatura
em graus Celcius. O sensor LM35 tem a vantagem sobre sensores
de temperatura linear calibrados em Kelvin, devido a não ser necessário
subtrair uma alta tensão constante da saída para obter uma escala
conveniente \cite{lm35:2016}.

## Ambiente de execução

Para esse exemplo o ambiente de execução escolhido foi o NodeJS, que
é um envólucro (_wrapper_) do ambiente de execução JavaScript de alta performance chamado V8
usado no navegador Google Chrome. O NodeJS permite que o V8 funcione em contextos
diferentes do browser, principalmente fornecendo APIs adicionais
que são otimizadas para casos específicos \cite{hughes-croucher:2012}.
Por exemplo no caso de equipamentos IOT é perfeito, pois se trata de um
dispositivo orientado a eventos, assim como o NodeJS.

Para auxiliar na conversação entre o NodeJS e o Arduino foi usado a ferramenta
Johnny-Five, uma plataforma livre Javascript para Robôs e IOT \cite{johnny-five:2012}.

## Princípios de execução

O NodeJS deve ser instalado no Raspberry Pi já que possui suporte a arquitetura ARM.
Um projeto NodeJS deve ser criado tendo como dependências o Johnny-Five e uma biblioteca
de resquisições HTTP, como por exemplo `request` \cite{request:2016}. Dessa forma
o Johnny-Five se encarregará de se comunicar com o Arduino requisitando a temperatura
do componente LM35. Com a resposta em mãos o NodeJS irá enviar as medições ao Servidor
através da biblioteca `request`.

O código fonte deste exemplo pode ser encontrado num repositório do GitHub \cite{alves:2016}
e a montagem do projeto pode ser vista na Figura \ref{fig:montagem}.

\begin{figure}[h]
	\centering
	\includegraphics[scale=0.4]{img/montagem-grey.jpg}
	\caption{Montagem do projeto} \label{fig:montagem}
\end{figure}

## Visualização dos dados

Após captar e enviar dados do IOT para a nuvem é possível acompanhar
os resultados pelo sistema. A forma de visualização será como mostra a
Figura \ref{fig:view-monitor}.

\begin{figure}[h]
	\centering
	\includegraphics[scale=0.35]{img/temperature-show-grey.png}
	\caption{Visualização dos dados na web} \label{fig:view-monitor}
\end{figure}

# Conclusão

A partir de ferramentas livres é possível sim criar ambientes de alta
qualidade para monitoramento de dispositivos IOT. Tanto porque grande parte
das ferramentas livres são estáveis e bem testadas, quanto a liberdade de
poder customizar para que a ferramenta atenda sua necessidade, não o contrário.

Um passo importante e que intimida um pouco é a forma de autenticação. JWT
é uma tecnologia muito recente e utiliza técnicas pouco convencionais para o
público iniciante, mas temos que levar em conta que junto com o aumento do
uso de equipamentos ligados a internet vem a necessidade de segurança na
comunicação. Uma falha de segurança que se tornou comum nessas situações
é chamada de _man-in-the-middle_, que pode ser definida como "Uma falha de
segurança em um computador em que um usuário malicioso intercepta - e possivelmente
altera - dados trafegando em uma rede" \cite{wordspy:2002}.
Esse erro pode ocorrer simplesmente porque os vínculos entre aparelhos e 
criptografias de proteção cedidas por um padrão normalmente não foram implementadas
corretamente, como por exemplo em travas eletrônicas que usam
Bluetooth Low Energy (BLE) \cite{spring:2016}.

Uma prática comum para autenticação de IOTs é a criação de tokens randômicos
para identificar o usuário e o dispositivo, entretanto essa técnica facilita
o ataque _man-in-the-middle_. Nessa linha o uso do JWT possui vantagens quando
comparado com um token randômico:

* Chaves API randômicas não dizem nada a respeito do usuário, enquanto JWTs contém
	informações e metadados que descrevem a identidade do usuário; contém também
    uma validade por um período de tempo ou domínio.
* JWT não obriga a necessidade um emissor de token centralizado ou autoridade
	de revogação de token.
* É compatível com Oauth2 \cite{oauth2:2012}.
* Dados do JWT podem ser inspecionados.
* JWTs possuem controles de expiração \cite{romero:2015}.

Por fim o passo seguinte seria permitir o envio de comandos do navegador para
o dispositivo, podendo assim controlar algumas funcionalidades remotamente como
o acionamento de cargas, disparo de relés, entre outras funções.
