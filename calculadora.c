#include <stdio.h> // Biblioteca para funções de entrada e saída (printf, scanf)
#include <stdlib.h> // Biblioteca para a função system("cls") ou system("clear")

int main() {
    // Passo 2: Declaração de variáveis
    double n1, n2, resultado;
    char operacao, op_continuar = 'n';
    int i;

    // Passo 3: Loop principal (faca...enquanto -> do...while)
    do {
        // Passo 5: Limpando a tela (uma alternativa ao loop 'for')
        system("cls"); // Para Windows. Comente ou remova se estiver no Linux/macOS
       // system("clear"); // Para Linux/macOS. Comente ou remova se estiver no Windows

        // Menu da calculadora usando printf (Passo 4)
        printf("--------------------------------\n");
        printf("          CALCULADORA\n");
        printf("--------------------------------\n");
        printf("Escolha a operacao:\n");
        printf("[ + ] Adicao\n");
        printf("[ - ] Subtracao\n");
        printf("[ * ] Multiplicacao\n");
        printf("[ / ] Divisao\n");
        printf("Digite 's' para encerrar.\n");
        printf("--------------------------------\n");
        printf("Operacao: ");
        
        // Leitura da operação com o truque do espaço para limpar o buffer
        scanf(" %c", &operacao);
        printf("--------------------------------\n\n");

        // Passo 6: Estrutura condicional (se -> if)
        if (operacao != 's') {

            // Pede novos números apenas se o usuário não escolheu 'm'
            if (op_continuar != 'm') {
                printf("Digite o primeiro numero: ");
                scanf("%lf", &n1);

                printf("Digite o segundo numero: ");
                scanf("%lf", &n2);
                printf("\n");
            }

            // Passo 7: Estrutura de escolha (escolha -> switch)
            switch (operacao) {
                case '+':
                    resultado = n1 + n2;
                    // %.2f formata o número para ter apenas 2 casas decimais
                    printf("Resultado: %.2f + %.2f = %.2f\n\n", n1, n2, resultado);
                    break; // 'pare' vira 'break'

                case '-':
                    resultado = n1 - n2;
                    printf("Resultado: %.2f - %.2f = %.2f\n\n", n1, n2, resultado);
                    break;

                case '*':
                    resultado = n1 * n2;
                    printf("Resultado: %.2f * %.2f = %.2f\n\n", n1, n2, resultado);
                    break;

                case '/':
                    if (n2 == 0) {
                        printf("Erro! Nao e possivel dividir por zero.\n\n");
                    } else {
                        resultado = n1 / n2;
                        printf("Resultado: %.2f / %.2f = %.2f\n\n", n1, n2, resultado);
                    }
                    break;
                
                default: // 'caso contrario' vira 'default'
                    printf("Operacao invalida! Tente novamente.\n\n");
                    op_continuar = 'n'; // Reseta a opção para pedir novos números
            }

            // Menu para continuar
            printf("Deseja continuar?\n");
            printf("Digite 'm' para usar os mesmos numeros e escolher outra operacao.\n");
            printf("Digite 'n' para digitar novos numeros.\n");
            printf("Digite 's' para encerrar.\n");
            printf("Opcao: ");
            scanf(" %c", &op_continuar);
            printf("\n");

            // Se o usuário escolher 's' aqui, forçamos a variável 'operacao' para 's'
            // para que o loop principal termine.
            if (op_continuar == 's') {
                operacao = 's';
            }
        }
    } while (operacao != 's'); // Condição do loop principal

    printf("Calculadora encerrada. Ate a proxima!\n");

    return 0; // Fim do programa
}