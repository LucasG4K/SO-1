<section>   
    <h1>📢 SO: Simulador da Arquitetura de Von Neumann e Pipeline MIPS</h1>   
    <p>
        Criado em Outubro de 2024, o projeto do<strong> Simulador da Arquitetura de Von Neumann e Pipeline MIPS</strong> foi desenvolvido em virtude de atender as demandas do curso de Sistemas Operacionais, ministrado pelo professor <a href="https://www.linkedin.com/in/michelpiressilva/?originalSubdomain=br" target="_blank">Michel Pires Da Silva</a> no Centro Federal de Educação Tecnológica de Minas Gerais (<a href="https://www.divinopolis.cefetmg.br/" target="_blank">CEFET-MG</a>).
    </p>
    <p>
        <a href="https://github.com/LucasG4K/SO-1/blob/main/documentation/assignment.pdf" target="_blank">Acesse o enunciado [AQUI]</a>
    </p>
    <div>
          <p>
            Feito por <a href="https://www.linkedin.com/in/emanuel-vieira-tavares-019706291/" target="_blank">Emanuel Viera Tavares</a>, <a href="https://www.linkedin.com/in/gabriel-couto-582060200/" target="_blank">Gabriel Couto Assis</a>, <a href="https://www.linkedin.com/in/luan-santos-9bb01920b/" target="_blank">Luan Gonçalves Santos</a>, <a href="https://www.linkedin.com/in/lucas-s-gontijo/" target="_blank">Lucas de Souza Gontijo</a>, e <a href="https://www.linkedin.com/in/dev-vini-pereira/" target="_blank">Vinicius Alves Pereira</a>
         </p>   
    </div>
    <p>
        Dessa forma, o projeto consiste em um simulador básico de uma Arquitetura de Von Neuman com um pipeline que processa instruções MIPS em uma sequência de fases, desenvolvido na linguagem C++.
    </p>
</section>

<section>
    <h2>📌Estrutura Geral</h2>
    <p>
        O simulador é composto por classes que representam a CPU, a memória RAM, memória Cache e um banco de registradores, além do código principal que executa as instruções a partir de um arquivo chamado codigo.txt. O simulador segue um fluxo básico de execução de instruções, semelhante ao ciclo de instruções de um processador com pipeline, com as fases de busca (fetch), decodificação (decode), execução (execute), acesso à memória (memory access), e escrita de volta (write back).
    </p>
    <h3>1. CPU</h3>
    <p>
        A classe CPU é responsável pelo controle do fluxo de instruções. Isso acontece a partir das seguintes funções:
    </p>
    <ul>
        <li><strong>InstructionFetch()</strong>: Esta função lê a próxima instrução da ROM (conjunto de instruções armazenadas no arquivo codigo.txt) e a carrega para a execução. O Program Counter (PC) é incrementado a cada instrução buscada, até que todas as instruções sejam processadas.</li>
        <li><strong>InstructionDecode()</strong>: Esta função separa a instrução ativa em partes, usando a função split(), para identificar a operação (op) e os operandos. Se o valor de um operando não for "!", o valor é armazenado no banco de registradores.</li>
        <li><strong>Execute()</strong>: Esta função simula a Unidade Lógica e Aritmética (ULA), executando operações como ADD, SUB, MUL, DIV, SLT, BNE, BEQ, e J. As operações de comparação e salto alteram o valor do Program Counter (PC).</li>
        <li><strong>MemoryAccess()</strong>: Esta função gerencia o acesso à memória, implementando as instruções LOAD, ILOAD e STORE. A memória RAM é usada para armazenar e recuperar valores.</li>
        <li><strong>WriteBack()</strong>: Esta função escreve o valor calculado de volta no banco de registradores se houver um valor para ser escrito.</li>
    </ul>
    <h3> 2. RAM </h3>
    <p>
        A classe RAM simula a memória do sistema, com um array de 32 inteiros, onde cada posição pode ser lida ou escrita por meio de funções de acesso. O estado da RAM pode ser exibido na saída padrão.
    </p>
    <h3>3. RegisterBank</h3>
    <p>
        A classe RegisterBank simula o banco de registradores do processador, armazenando 32 registradores, cada um com um valor e um flag <em>dirty</em> que indica se o registrador foi alterado. Os registradores podem ser lidos e escritos por meio de funções de acesso.
    </p>
    <h3>4. Cache</h3>
    <p>
        Na classe Cache, temos várias variáveis que desempenham papéis essenciais na gestão da memória cache. A constante <code>CACHE_SIZE</code> define o tamanho máximo da cache, limitando o número de entradas que ela pode armazenar a 32. Fora isso, a variável <code>cacheData</code> é um <code>unordered_map</code> que mapeia os endereços dos registradores (caso sejam alocados) para pares contendo o dado associado e um booleano que indica se esse dado foi modificado (ou seja, se ele deve ser escrito de volta na memória principal ao ser removido). Por fim, <code>fifoQueue</code> é uma fila que mantém a ordem dos endereços inseridos na cache, permitindo a implementação da política de substituição FIFO (First-In, First-Out), garantindo que o item mais antigo seja removido quando a cache atinge sua capacidade máxima. Visto que essa estrutura é um trabalho futuro, a classe Cache ainda não possuí nenhum metodo implementado.
    </p>
<!--     <h3>5. Funções Auxiliares</h3>
    <ul>
        <li><strong>ULA()</strong>: Simula a Unidade Lógica e Aritmética, realizando operações matemáticas básicas.</li>
        <li><strong>split()</strong>: Separa uma string de instrução em partes, preenchendo com "!" se a instrução tiver menos de 4 componentes, o que é útil para decodificar as instruções.</li>
    </ul> -->
   

</section>

<section>
    <h2>💻 Ferramentas Utilizadas</h2>
    <p>
        Durante o deselvovimento do algoritimo apresentado nesse repositório, foi-se utilizado de duas principais ferramentas de desenvolvimento: Visual Studio Code e WSL: Ubuntu.
    </p>
    <ul>
        <li>    
            <p>
                O Visual Studio Code é um editor de texto multiplataforma disponibilizado pela Microsoft para o desenvolvimento de aplicações, Conhecer essa ferramenta é importante para os desenvolvedores que pretendem trabalhar em ambientes multiplataforma, por exemplo,  podendo operar o desenvolvimento em ambiente Mac e Linux, ao mesmo tempo em que mantém o projeto compatível com Windows. Segue em anexo o link para o site da plataforma — <a href="https://code.visualstudio.com/" target="_blank">Visual Studio Code</a>.
            </p>
        </li>
        <li>
            <p>
                O WSL é um método para se executar comandos Linux dentro do Windows de forma simplificada. Essa platoforma se torna essencial para o desenvovimento, evitando tarefas como a intalação de máquinas vituais e a criação de dual booting no computador pessoal. Nesse projeto, o WSL foi utilizado para compilar e executar o programa em C++ em um ambiente Linux através do Windows. Segue em anexo um  tutorial de download do WSL2 — <a href="https://youtu.be/hd6lxt5iVsg" target="_blank">Tutorial WSL2</a>.
            </p>
        </li>
    </ul>
</section>

<section>
    <h2>⚙️Como executar </h2>
    <p>
        O projeto possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução para distribuições Linux:
    </p>
    <div align="center">
        <table>
            <thead>
                <tr>
                    <th>Comando</th>
                    <th>Função</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td><code>make clean</code></td>
                    <td>Apaga a última compilação realizada contida na pasta build</td>
                </tr>
                <tr>
                    <td><code>make</code></td>
                    <td>Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build</td>
                </tr>
                <tr>
                    <td><code>make run</code></td>
                    <td>Executa o programa da pasta build após a realização da compilação</td>
                </tr>
            </tbody>
        </table>
        <p align="center">
            <b>Tabela 1:</b> Comandos úteis para compilar e executar o programa de computador
        </p>
    </div>
</section>

<section>

## 📝 Instruções Definidas para o Simulador

### 1. ILOAD
- **Formato**: ILOAD \<dest\> \<valor\>
- **Descrição**: Carrega um valor imediato no registrador \<dest\>.
- **Exemplo**: ILOAD 16 10
  - **Explicação**: Carrega o valor 10 no registrador 16.

### 2. ADD
- **Formato**: ADD \<dest\> \<src1\> \<src2\>
- **Descrição**: Soma o valor dos registradores \<src1\> e \<src2\> e armazena o resultado em \<dest\>.
- **Exemplo**: ADD 18 16 17
  - **Explicação**: Soma o valor nos registradores 16 e 17 e armazena o resultado no registrador 18.

### 3. STORE
- **Formato**: STORE \<src\> \<endereco\>
- **Descrição**: Armazena o valor do registrador \<src\> na posição de memória \<endereco\>.
- **Exemplo**: STORE 18 16
  - **Explicação**: Armazena o valor do registrador 18 na posição de memória definida pelo valor no registrador 16.

### 4. BEQ (Branch if Equal)
- **Formato**: BEQ \<reg1\> \<reg2\> \<label\>
- **Descrição**: Se os valores de \<reg1\> e \<reg2\> são iguais, o programa salta para a instrução de número \<label\>.
- **Exemplo**: BEQ 16 17 9
  - **Explicação**: Se o valor no registrador 16 for igual ao valor no registrador 17, o programa pula para a linha 9 do código.

### 5. J (Jump)
- **Formato**: J \<label\>
- **Descrição**: Altera o fluxo de execução do código para a linha especificada por \<label\>.
- **Exemplo**: J 5
  - **Explicação**: Altera o fluxo de execução para a linha 5.

### 6. SUB
- **Formato**: SUB \<dest\> \<src1\> \<src2\>
- **Descrição**: Subtrai o valor em \<src2\> do valor em \<src1\> e armazena o resultado em \<dest\>.
- **Exemplo**: SUB 18 16 17
  - **Explicação**: Subtrai o valor no registrador 17 do valor no registrador 16 e armazena o resultado em 18.

### 7. MUL
- **Formato**: MUL \<dest\> \<src1\> \<src2\>
- **Descrição**: Multiplica o valor dos registradores \<src1\> e \<src2\> e armazena o resultado em \<dest\>.
- **Exemplo**: MUL 18 16 17
  - **Explicação**: Multiplica os valores nos registradores 16 e 17 e armazena o resultado em 18.

### 8. DIV
- **Formato**: DIV \<dest\> \<src1\> \<src2\>
- **Descrição**:Divide o valor dos registradores \<src1\> e \<src2\> e armazena o resultado em \<dest\>.
- **Exemplo**: DIV 18 16 17
  - **Explicação**: Divide os valores nos registradores 16 e 17 e armazena o resultado em 18.

### 9. BNE (Branch if Not Equal) 
- **Formato**: BNE \<reg1\> \<reg2\> \<label\>
- **Descrição**: Se os valores de \<reg1\> e \<reg2\> são diferentes, o programa salta para a instrução de número \<label\>.
- **Exemplo**: BNE 16 17 9
  - **Explicação**: Se o valor no registrador 16 for diferente do valor no registrador 17, o programa pula para a linha 9 do código.

### 10. SLT (Set if Less Than)
- **Formato**: SLT \<dest\> \<src1\> \<src2\>
- **Descrição**: Compara os valores de \<src1\> e \<src2\>. Se o valor em \<src1\> for menor que o valor em \<src2\>, armazena 1 em \<dest\>; caso contrário, armazena 0.
- **Exemplo**: SLT 18 16 17
  - **Explicação**: Se o valor no registrador 16 for menor que o valor no registrador 17, armazena 1 no registrador 18; caso contrário, armazena 0.

---

## Análise Detalhada de Código 

O arquivo codigo.txt contém o código de instruções que será executado pelo simulador.
Abaixo, segue a explicação de cada linha de um código de exemplo para detalhar a execução do programa:

````plaintext
    ILOAD 16 10
    ILOAD 17 12
    ADD 18 16 17
    STORE 18 16
    BEQ 16 17 9
    ILOAD 18 1
    ADD 16 18 16
    J 5
    SUB 18 16 17
    MUL 18 16 17
````

### Explicando o código:

1. **`ILOAD 16 10`**
   - Carrega o valor `10` no registrador `16`.

2. **`ILOAD 17 12`**
   - Carrega o valor `12` no registrador `17`.

3. **`ADD 18 16 17`**
   - Soma os valores dos registradores `16` e `17` (`10 + 12 = 22`) e armazena o resultado no registrador `18`.

4. **`STORE 18 16`**
   - Armazena o valor do registrador `18` (`22`) na posição de memória cujo endereço está armazenado no registrador `16` (`10`).

5. **`BEQ 16 17 9`**
   - Se os valores dos registradores `16` e `17` forem iguais, o fluxo de execução salta para a linha `9`. Como os valores são diferentes (`10` e `12`), o código continua na próxima linha.

6. **`ILOAD 18 1`**
   - Carrega o valor `1` no registrador `18`.

7. **`ADD 16 18 16`**
   - Soma o valor do registrador `18` (`1`) ao valor do registrador `16` (`10`), resultando em `11`, e armazena o resultado no registrador `16`.

8. **`J 5`**
   - Salta para a linha `5` do código, voltando para a instrução `BEQ 16 17 9`. Este salto cria um loop, verificando continuamente se os valores dos registradores `16` e `17` são iguais.

9. **`SUB 18 16 17`**
   - Caso o loop seja quebrado (valores iguais), esta linha executará a subtração do valor no registrador `17` (`12`) do valor no registrador `16`, com o resultado armazenado no registrador `18`.

10. **`MUL 18 16 17`**
    - Multiplica os valores dos registradores `16` e `17`

</section>

<section>
    <h2>📚 Referências</h2>
    <p>
        BERTINI, Luciano. <strong>Capítulo 5 Pipeline</strong>. 2019. Disponível em: <a href="https://www.professores.uff.br/lbertini/wp-content/uploads/sites/108/2017/08/Cap-5-Pipeline.pdf">https://www.professores.uff.br/lbertini/wp-content/uploads/sites/108/2017/08/Cap-5-Pipeline.pdf</a>. Acesso em: 24 out. 2024.
    </p>
</section>


