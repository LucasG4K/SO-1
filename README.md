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
</section>
<section>
    <h2>🎞 Processamento</h2>
    <p>
        Durante o deselvovimento do algoritimo apresentado nesse repositório, foi-se utilizado de três principais tecnologias: Visual Studio Code e WSL:Ubunto.
    </p>
    <ul>
        <li>    
            <p>
                O Visual Studio Code é um editor de texto multiplataforma disponibilizado pela Microsoft para o desenvolvimento de aplicações, Conhecer essa ferramenta é importante para os desenvolvedores que pretendem trabalhar em ambientes multiplataforma, por exemplo,  podendo operar o desenvolvimento em ambiente Mac e Linux, ao mesmo tempo em que mantém o projeto compatível com Windows. Segue em anexo o link para o site da plataforma — <a href="https://code.visualstudio.com/" target="_blank">Visual Studio Code</a>.
            </p>
        </li>
        <li>
            <p>
                O WSL é um método para se executar o Sistema Operaciona Linux dentro do Windows de forma muito facil. Essa platoforma se torna essencial para o desenvovimento em ambiente GNU Linux, evitando tarefas como a intalação de maquinas vituais, criação de dual booting no computador pessoal e entre outras coisas. Além disso, existem diversas vantagens como rodar programas em conjunto e compartihamento de localhost. Segue em anexo um  tutorial de download do WSL2 — <a href="https://youtu.be/hd6lxt5iVsg" target="_blank">Tutorial WSL2</a>.
            </p>
        </li>
    </ul>
    <p>
        O programa ainda possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:
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

## 🎞 Instruções Definidas para o Simulador

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
- **Descrição**: Se os valores de \<reg1\> e \<reg2\> são iguais, o programa salta para a instrução de número <label>.
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


