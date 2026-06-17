#include <stdio.h>
#include <string.h>

// Definição da estrutura personalizada fora da main (permitido pelas regras)
struct Produto {
    int id;
    char nome[50];
    float preco;
};

int main() {
    // Vetor de estruturas com 10 posições e controle de quantidade
    struct Produto estoque[10];
    int qtd_atual = 0;
    int opcao;

    // Variáveis auxiliares para as operações do CRUD
    int i, j;
    int id_busca, id_duplicado, encontrado, indice_remover;
    int id_aux;
    char nome_aux[50];
    float preco_aux;

    // Loop do Menu Principal (O programa roda até a opção 6 ser escolhida)
    do {
        printf("\n===================================\n");
        printf("    SISTEMA DE GESTAO DE ESTOQUE   \n");
        printf("===================================\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Buscar Produto por ID\n");
        printf("4. Atualizar Produto\n");
        printf("5. Remover Produto\n");
        printf("6. Sair\n");
        printf("===================================\n");
        printf("Escolha uma opcao: ");
        
        // Validação da entrada do menu
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n");
            while (getchar() != '\n'); // Limpa o buffer
            opcao = 0; // Força o retorno ao menu
            continue;
        }

        switch (opcao) {
            
            // === CADASTRAR REGISTRO ===
            case 1:
                if (qtd_atual >= 10) {
                    printf("\n[ERRO] O estoque esta cheio! (Limite: 10 produtos)\n");
                    break;
                }

                printf("\n--- Cadastrar Novo Produto ---\n");
                printf("Digite o ID do produto (apenas numeros positivos): ");
                if (scanf("%d", &id_aux) != 1 || id_aux <= 0) {
                    printf("[ERRO] ID invalido!\n");
                    while (getchar() != '\n');
                    break;
                }

                // Validação de ID duplicado
                id_duplicado = 0;
                for (i = 0; i < qtd_atual; i++) {
                    if (estoque[i].id == id_aux) {
                        id_duplicado = 1;
                        break;
                    }
                }

                if (id_duplicado) {
                    printf("[ERRO] Ja existe um produto cadastrado com este ID!\n");
                    break;
                }

                // Leitura dos demais dados com validação simples
                printf("Digite o nome do produto: ");
                getchar(); // Limpa o buffer do teclado
                fgets(nome_aux, 50, stdin);
                nome_aux[strcspn(nome_aux, "\n")] = 0; // Remove o '\n' do final

                printf("Digite o preco do produto: ");
                if (scanf("%f", &preco_aux) != 1 || preco_aux < 0) {
                    printf("[ERRO] Preco invalido!\n");
                    while (getchar() != '\n');
                    break;
                }

                // Salva no vetor após todas as validações passarem
                estoque[qtd_atual].id = id_aux;
                strcpy(estoque[qtd_atual].nome, nome_aux);
                estoque[qtd_atual].preco = preco_aux;
                qtd_atual++;

                printf("\n[SUCESSO] Produto cadastrado com sucesso!\n");
                break;

            // === LISTAR REGISTROS ===
            case 2:
                if (qtd_atual == 0) {
                    printf("\n[AVISO] Nao ha produtos cadastrados no sistema.\n");
                    break;
                }

                printf("\n--- Lista de Produtos Cadastrados ---\n");
                printf("%-5s | %-25s | %-10s\n", "ID", "Nome do Produto", "Preco (R$)");
                printf("---------------------------------------------\n");
                for (i = 0; i < qtd_atual; i++) {
                    printf("%-5d | %-25s | R$ %-9.2f\n", estoque[i].id, estoque[i].nome, estoque[i].preco);
                }
                break;

            // === BUSCAR REGISTRO POR ID ===
            case 3:
                if (qtd_atual == 0) {
                    printf("\n[AVISO] Nao ha produtos cadastrados para buscar.\n");
                    break;
                }

                printf("\nDigite o ID do produto que deseja buscar: ");
                scanf("%d", &id_busca);

                encontrado = 0;
                for (i = 0; i < qtd_atual; i++) {
                    if (estoque[i].id == id_busca) {
                        printf("\n--- Produto Encontrado ---\n");
                        printf("ID: %d\n", estoque[i].id);
                        printf("Nome: %s\n", estoque[i].nome);
                        printf("Preco: R$ %.2f\n", estoque[i].preco);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("\n[ERRO] Produto com o ID %d nao foi encontrado.\n", id_busca);
                }
                break;

            // === ATUALIZAR REGISTRO ===
            case 4:
                if (qtd_atual == 0) {
                    printf("\n[AVISO] Nao ha produtos cadastrados para atualizar.\n");
                    break;
                }

                printf("\nDigite o ID do produto que deseja atualizar: ");
                scanf("%d", &id_busca);

                encontrado = 0;
                for (i = 0; i < qtd_atual; i++) {
                    if (estoque[i].id == id_busca) {
                        encontrado = 1;
                        
                        printf("\n--- Editando Produto: %s (ID: %d) ---\n", estoque[i].nome, estoque[i].id);
                        printf("Digite o novo nome: ");
                        getchar();
                        fgets(nome_aux, 50, stdin);
                        nome_aux[strcspn(nome_aux, "\n")] = 0;

                        printf("Digite o novo preco: ");
                        if (scanf("%f", &preco_aux) != 1 || preco_aux < 0) {
                            printf("[ERRO] Preco invalido! Alteracao cancelada.\n");
                            while (getchar() != '\n');
                            break;
                        }

                        // Aplica as alterações
                        strcpy(estoque[i].nome, nome_aux);
                        estoque[i].preco = preco_aux;
                        printf("\n[SUCESSO] Produto atualizado com sucesso!\n");
                        break;
                    }
                }

                if (!encontrado) {
                    printf("\n[ERRO] Produto com o ID %d nao encontrado.\n", id_busca);
                }
                break;

            // === REMOVER REGISTRO ===
            case 5:
                if (qtd_atual == 0) {
                    printf("\n[AVISO] Nao ha produtos cadastrados para remover.\n");
                    break;
                }

                printf("\nDigite o ID do produto que deseja remover: ");
                scanf("%d", &id_busca);

                encontrado = 0;
                indice_remover = -1;

                // Localiza o índice do item a ser removido
                for (i = 0; i < qtd_atual; i++) {
                    if (estoque[i].id == id_busca) {
                        indice_remover = i;
                        encontrado = 1;
                        break;
                    }
                }

                if (encontrado) {
                    // Mantém a consistência do vetor puxando os elementos seguintes uma posição para trás
                    for (j = indice_remover; j < qtd_atual - 1; j++) {
                        estoque[j] = estoque[j + 1];
                    }
                    qtd_atual--; // Decrementa a quantidade total de registros
                    printf("\n[SUCESSO] Produto removido com sucesso!\n");
                } else {
                    printf("\n[ERRO] Produto com o ID %d nao encontrado.\n", id_busca);
                }
                break;

            case 6:
                printf("\nEncerrando o programa. Ate logo!\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Escolha uma opcao entre 1 e 6.\n");
                break;
        }

    } while (opcao != 6);

    return 0;
}