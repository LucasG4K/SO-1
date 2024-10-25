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
    <h2>📚 Referências</h2>
    <p>
        BERTINI, Luciano. <strong>Capítulo 5 Pipeline</strong>. 2019. Disponível em: <a href="https://www.professores.uff.br/lbertini/wp-content/uploads/sites/108/2017/08/Cap-5-Pipeline.pdf">https://www.professores.uff.br/lbertini/wp-content/uploads/sites/108/2017/08/Cap-5-Pipeline.pdf</a>. Acesso em: 24 out. 2024.
    </p>
</section>