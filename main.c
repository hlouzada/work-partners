#include "users.h"


int main(int argc, char *argv[]) {

    int ordem;

    while(ordem != 1337){
        printf("Olah! >:DD voce pode realizar as seguintes acoes:");
        printf("1- Cadastrar usuario. \n");
        printf("2- Listar usuarios. \n");
        printf("3- Enviar pedido de amigo. \n");
        printf("4- Avaliar pedidos de amigo. \n");
        printf("5- Enviar mensagem para um amigo. \n");
        printf("6- Visualizar suas mensagens. \n");
        printf("7- Sugerir amizades! \n");
        printf("8- Encerrar uma amizade. \n");

        printf("1337- Encerra a sessao. \n \n");
        printf("O que quer fazer? >:? \n");

        scanf("%d", ordem);
        printf("\n");

        if(ordem == 1){ //Cadastrar usuario

            printf("Diga seu nome! >:DD \n");
            () //funcao pra ler e salvar nome completo com espaco

            printf("Como gostaria de ser chamado? >:? \n");
            scanf("%c", nick); //funcao pra ler e salvar nick
            ()
            printf("Seja bem-vindo, %c >:DD esse sera o nome que deve usar nos comandos. \n", nick);
        }

        else if(ordem == 2){ //lista usuarios
            printf("Aqui estah a lista de todos os usuarios: \n");
        ()
        }

        else if(ordem == 3){ //pedido amigo
            char nick;
            char amigo;

            printf("Entre com o seu nome: \n");
            scanf("%c", nick);
            () //funcao que checa e salva o nome se ja foi cadastrado

            printf("Quem voce gostaria de adicionar, %c ? >:? Coloque o apelido. \n", nick)
            scanf("%", amigo)
            () //funcao que checa se o amigo existe e salva o nome

        }

        else if(ordem == 4){ //avaliar pedido amigo
            char resposta;
            printf("Esses sao seus pedidos de Parceiro: \n");
            () //funcao que lista os pedidos de amigo

            printf("Avalie o pedido mais antigo! >:DD \n Digite A para Aceitar, N para Negar ou D pra Deixar pra mais tarde");
            scanf("%c", resposta);

            if(resposta == "A"){ //aceita o pedido

            }

            else if(resposta == "N"){ //nega o pedido

            }

            else{

            }
        }

        else if(ordem == 5){ //enviar mensagem
            char nick;
            char amigo;

            printf("Entre com o seu nome: \n");
            scanf("%c", nick);
            (); //funcao que checa e salva o nome se ja foi cadastrado
            printf("Para quem gostaria de enviar sua mensagem? >:?");
            scanf("%c", amigo)
            ();
        }

        else if(ordem == 6){ //ler mensagem
            char nick;
            printf("Entre com o seu nome: \n");
            scanf("%c", nick);
            () //funcao que checa e salva o nome se ja foi cadastrado

            printf("Aqui estao suas mensagens >:DD mais antigas primeiro");
        }

        else if(ordem == 7){ //sugerir amigo
            char nick;
            printf("Entre com o seu nome: \n");
        }

        else if(ordem == 8){ //desfazer amigo
            char nick;
            printf("Entre com o seu nome: \n");
        }

        else if(ordem == 1337){ //Encerra sessao

        }
    }


    printf("Ateh a proxima! >:DD");
}
