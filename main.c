#include "users.h"


int main(int argc, char *argv[]) {

    // Interface de usuário
    // Lista-se as possíveis atividades e recebe ordem do usuário.
    int ordem;

    while(ordem != 1337){
        printf("Olah! >:DD voce pode realizar as seguintes ações:");
        printf("1- Cadastrar usuário. \n");
        printf("2- Listar usuários. \n");
        printf("3- Enviar pedido de amigo. \n");
        printf("4- Avaliar pedidos de amigo. \n");
        printf("5- Enviar mensagem para um amigo. \n");
        printf("6- Visualizar suas mensagens. \n");
        printf("7- Sugerir amizades! \n");
        printf("8- Encerrar uma amizade. \n");
        printf("9- Reinicializar sistema. \n");

        printf("1337- Encerra a sessão. \n \n");
        printf("O que quer fazer? >:? \n");

        scanf("%d", ordem);
        printf("\n");
        // checar se o usuário colocou um valor válido
        if ((ordem > 9) || (ordem < 1)){
          if ((ordem!= 1337) || (ordem%1 != 0)){
            printf("Favor inserir um valor válido.\n")
          }
        }

        if(ordem == 1){ //Cadastrar usuário
            char nick;
            string nome;
            printf("Diga seu nome! >:DD \n");
            scanf("%s", nome);

            printf("Como gostaria de ser chamado? >:? \n");
            scanf("%c", nick); //funcao pra ler

            get_user(nick);

            new_user(nome, nick);

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
            (); //funcao que lista os pedidos de amigo

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
            str mensagem;

            printf("Entre com o seu nome: \n");
            scanf("%c", nick);
            (); //funcao que checa e salva o nome se ja foi cadastrado
            printf("Para quem gostaria de enviar sua mensagem? >:?");
            scanf("%c", amigo)
            ();

            printf("Escreva sua mensagem! >:DD");
            scanf("%s", mensagem);
            ();
        }

        else if(ordem == 6){ //ler mensagem
            char nick;
            printf("Entre com o seu nome: \n");
            scanf("%c", nick);
            (); //funcao que checa e salva o nome se ja foi cadastrado

            printf("Aqui estao suas mensagens >:DD mais antigas primeiro");
            (); //funcao que mostra mensagens
        }

        else if(ordem == 7){ //sugerir amigo
            char amigo1; //???
            char amigo2; //???
            printf("Entre com o seu nome: \n");
        }

        else if(ordem == 8){ //desfazer amigo
            char nick;
            char amigo;
            printf("Entre com o seu nome: \n");
            scanf("%c", nick);
            ();

            printf("Com quem gostaria de terminar a Parceria?");
            scanf("%c", amigo);
            ();

            (); //funcao que exclui amigo
            printf("Sua Parceria foi desfeita com sucesso!");

        }

        else if(ordem == 1337){ //Encerra sessao

        }
    }


    printf("Ateh a proxima! >:DD");
}
