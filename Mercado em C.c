#include <stdio.h>
#include <string.h>
#define MAX_PRODUTOS 50 // Defini um número máximo de produtos cadastráveis.

typedef struct {
    int codigo;   // struct para armazenar os dados de cada produto.
    float preco;
    char nome[30];
} Produto;

typedef struct {
    int produto;   // struct para armazenar os dados de cada produto.
    int quantidade;
} Carrinho;

// Função para exibir as informações de um produto.
void infoProduto(Produto prod) {
    printf("Código: %d\n", prod.codigo);
    printf("Nome: %s\n", prod.nome);
    printf("Preço: %.2f\n", prod.preco);
}

// Função para verificar se um produto já está no carrinho.
int temNoCarrinho(Carrinho carrinho[], int carrinhoCont, int codigo, Produto produtos[], Produto* produtoInfo) {
    for (int i = 0; i < carrinhoCont; i++) {
        if (produtos[carrinho[i].produto].codigo == codigo) {
            if (produtoInfo) {
                *produtoInfo = produtos[carrinho[i].produto]; // Retorna o produto
            }
            return 1; // Produto está no carrinho
        }
    }
    return 0; // Produto não está no carrinho
}

//Função para cadastrar produtos.
void cadastrarProduto(Produto produtos[], int *cont) {
    if (*cont >= MAX_PRODUTOS) { // If para evitar estourar o número máximo de produtos cadastrados
        printf("Você alcançou o número máximo de produtos cadastrados.\n");
        return; // Retorna caso o valor passe de 50 produtos.
    }

    printf("Escreva o código do produto que deseja cadastrar:\n"); 
    scanf("%d", &produtos[*cont].codigo);

    printf("Escreva o nome do produto que deseja cadastrar:\n"); // Printa as telas com as informações e recebe os valores digitados pelo cliente.
    scanf("%s", produtos[*cont].nome);

    printf("Escreva o preço do produto que deseja cadastrar:\n");
    scanf("%f", &produtos[*cont].preco);

    (*cont)++; // Incrementa mais 1 para que o contador de produtos cadastrados (cont) receba um acréscimo.
}

//Função para listar produtos.
void listarProdutos(Produto produtos[], int cont) {
    if (cont == 0) {  // verifica se o carrinho está vazio e retorna caso esteja.
        printf("Nenhum produto foi cadastrado.\n"); 
        return;
    }

    printf("Lista de produtos:\n");
    for (int i = 0; i < cont; i++) { // Looping for que percorre o array imprimindo as informações do produto.
        infoProduto(produtos[i]); // Chama a função para exibir as informações do produto.
    }
}

//Função para comprar produtos.
void comprarProduto(Produto produtos[], int cont, Carrinho carrinho[], int *carrinhoCont) { //Compra o produto.
    int codigo, quant;

    printf("Digite o código do produto que deseja comprar:\n"); //O usuário escolhe o código do produto.
    scanf("%d", &codigo);

    Produto produtoInfo;
    if (temNoCarrinho(carrinho, *carrinhoCont, codigo, produtos, &produtoInfo)) { //Caso o produto for encontrado no carrinho
        printf("Produto já está no carrinho. Digite a quantidade que deseja adicionar:\n");
        scanf("%d", &quant);
        for (int j = 0; j < *carrinhoCont; j++) {
            if (carrinho[j].produto == produtoInfo.codigo) { //Atualiza a quantidade de produtos.
                carrinho[j].quantidade += quant;
                printf("Quantidade atualizada no carrinho\n");
                return;
            }
        }
    } else { //Caso não seja encontrado no carrinho.
        for (int i = 0; i < cont; i++) { // Verifica se o código do produto corresponde ao código informado.
            if (produtos[i].codigo == codigo) { // Verifica se o código do produto corresponde ao código informado.
                printf("Digite a quantidade que deseja comprar:\n");
                scanf("%d", &quant);

                carrinho[*carrinhoCont].produto = i; 
                carrinho[*carrinhoCont].quantidade = quant;
                (*carrinhoCont)++; //Incrementa o contador de produtos no carrinho
                printf("Produto adicionado ao carrinho\n");
                return;
            }
        }
    }
    printf("Produto não encontrado.\n");
}

//Função para vizualizar o carrinho
void visualizarCarrinho(Carrinho carrinho[], int carrinhoCont, Produto produtos[]) { //Vizualiza os produtos no carrinho.
    if (carrinhoCont == 0) {
        printf("Nenhum produto foi comprado.\n"); //Caso o carrinho esteja vazio.
        return;
    }

    printf("Carrinho:\n");
    for (int i = 0; i < carrinhoCont; i++) {
        infoProduto(produtos[carrinho[i].produto]); // Exibe informações do produto.
        printf("Quantidade: %d\n", carrinho[i].quantidade);
    }
}

//Função para fechar o pedido da compra.
void fecharPedido(Carrinho carrinho[], Produto produtos[], int carrinhoCont) { //Fecha o pedido do cliente
    float total = 0;

    if (carrinhoCont == 0) {
        printf("O carrinho está vazio.\n"); //Caso o carrinho esteja vazio.
        return;
    }

    printf("Pedido fechado.\n");
    for (int i = 0; i < carrinhoCont; i++) {
        total += carrinho[i].quantidade * produtos[carrinho[i].produto].preco;
    }
    printf("Total do pedido: %.2f\n", total); //Imprime o valor total dos produtos comprados.
}

//Função que contém o menu que contém as outras funções.
void funcaoMenu(Produto produtos[], int *cont, Carrinho carrinho[], int *carrinhoCont) {
    int opcao = 0;

    while (opcao != 6) { //Looping que imprime as opções para o cliente escolher até que a opção 6 seja escolhida.
        printf("Digite a função que deseja realizar:\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Comprar Produto\n");
        printf("4 - Visualizar Carrinho\n");
        printf("5 - Fechar Pedido\n");
        printf("6 - Sair do Sistema\n");
        scanf("%d", &opcao);

        switch (opcao) { //Casos chamam a respectiva função dependendo da escolha do usuário
            case 1:
                cadastrarProduto(produtos, cont);
                printf("\n");
                break;

            case 2:
                listarProdutos(produtos, *cont);
                printf("\n");
                break;

            case 3:
                comprarProduto(produtos, *cont, carrinho, carrinhoCont);
                printf("\n");
                break;

            case 4:
                visualizarCarrinho(carrinho, *carrinhoCont, produtos);
                printf("\n");
                break;

            case 5:
                fecharPedido(carrinho, produtos, *carrinhoCont);
                printf("\n");
                break;

            case 6:
                break;

            default: //Caso nenhum dos casos seja escolhido.
                printf("Opção inválida.\n");
        }
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];  
    Carrinho carrinho[MAX_PRODUTOS];  

    int cont = 0;                     
    int carrinhoCont = 0;            

    funcaoMenu(produtos, &cont, carrinho, &carrinhoCont); //Chama a função menu.
    return 0;
}
