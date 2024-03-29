

# Skyline Problem

**Número da Lista**: 4<br>
**Conteúdo da Disciplina**: Dividir para conquistar<br>

## Alunos
|Matrícula | Aluno |
| -- | -- |
| 17/0068251  |  Andre Lucas de Sousa Pinto |
| 17/0038891  |  Leonardo de Araujo Medeiros |

## Sobre
Nesta aplicação é mostrada visualmente a solução do problema conhecido como "Skyline", que consite basicamente no enunciado: Dado n construções retangulares em uma dimensão 2D, mostre a visão horizontal das construções, eliminando as linhas não visíveis. 
A solução trivial para este problema consiste em comparar todos as estruturas a custo O(n²), todavia, o problema pode ser solucionado com complexidade O(n log(n)) usando a técnica de Dividr para conquistar, como implementado neste programa.
A entrada foi gerada de maneira pseudo-randômica.

## Screenshots
![screen 1](screenshots/1.png)
![screen 2](screenshots/2.png)
![screen 3](screenshots/3.png)

## Instalação 
**Linguagem**: C++<br>
**Framework**: Nenhum<br>
Dependencias: g++ compiler.
1. Faça o clone deste projeto com o comando ```$ git clone https://github.com/projeto-de-algoritmos/D-C_SkylineProblem.git```;
2. Altere para a o diretório do projeto com o comando ```$ cd D-C_SkylineProblem/```;
3. Use o comando ```$ make``` para compilar o projeto;
4. Use a o comando ```$ make run n=NUMERO``` para executar a aplicação. NUMERO deve ser um valor numérico de 2 a 100000.

OBS: caso não seja passada speed, ou nao seja um valor numérico de 1 a 100000 o mesmo irá ter o valor de 10.

## Uso 
Veja o resultado na tela.

## Outros 
Para desenvolvimento deste projeto também é feito uso da biblioteca [SFML](https://www.sfml-dev.org/index.php), todavia esta já se encontra inclusa no repositório a fim de faciltiar a instalação da aplicação. Respeitando devidamente a [licença](https://www.sfml-dev.org/license.php) sobre o código da biblioteca utilizada.




