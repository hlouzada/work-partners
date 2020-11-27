#include <stdlib.h>
#include <stdio.h>

#include "users.h"
#include "friends.h"
#include "messages.h"





int main(int argc, char *argv[]) {

    UserList *users = NULL;

    // Interface de usuário
    // Lista-se as possíveis atividades e recebe ordem do usuário.
    int ordem;

    while(ordem != 1337){
        printf("Olá! >:DD voce pode realizar as seguintes ações:");
        printf("1- Cadastrar usuário. \n");
        printf("2- Listar usuários. \n");
        printf("3- Enviar pedido de amizade. \n");
        printf("4- Avaliar pedidos de amizade. \n");
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
            char* nick;
            char* nome;
            printf("Diga seu nome! >:DD \n");
            scanf("%s", nome);

            printf("Como gostaria de ser chamado? >:? \n");
            scanf("%s", nick); //funcao pra ler


            if (users == NULL){
              User *user = new_user(nome, nick);
              users = new_user_list(user);
            } else {
              while( get_user(users, nick ) != NULL){
                printf("Esse apelido já está sendo usado, escolha outro apelido:\n");
                scanf("%s", nick);
              }
              User *user = new_user(nome, nick);
              users = push_user(users, user);
            }

            printf("Seja bem-vindo, %s >:DD esse sera o nome que deve usar nos comandos. \n", nick);
        }

        else if(ordem == 2){ //lista usuarios
            printf("Aqui está a lista de todos os usuários e seus amigos: \n");
            // Cria um ponteiro temporário para iterar pelos usuários
            User *temp = users->start;
            while (temp != NULL){
              printf("%s com os amigos: ", temp->nick);
              Friend *temp_friend = temp->friend_list->start;
              while(temp_friend != NULL){
                if(is_friend(temp_friend)){
                  printf("%s, ", temp_friend->friend_request->from->nick);
                  // estou com medo de a pessoa que mandou o pedido  ser a pessoa
                  // que fez o pedido. Como saber se o usuário é o to ou o from?
                }
                temp_friend = temp_friend->next;
              }
              printf("\n");
              temp = temp->next;
            }
          }

        else if(ordem == 3){ //pedido amigo
            char* nick; // precisamos declarar tantas vezes a mesma variável?
            char* amigo;

            printf("Entre com o seu apelido: \n");
            scanf("%s", nick);
           //funcao que checa e salva o nome se ja foi cadastrado
           User *user = get_user(users, nick);
           if (user == NULL){
             printf("Esse usuário não existe.");
           } else {
             printf("Quem você gostaria de adicionar, %c ? >:? Coloque o apelido. \n", nick)
             scanf("%s", amigo);
             //funcao que checa se o amigo existe e salva o nome
             User *user_amigo = get_user(users, amigo);
             if (user_amigo == NULL){
               printf("Esse usuário não existe.");
             } else {
               add_friend_request(user, user_amigo);
             }
           }
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
            char* nick;
            char* amigo;
            char* mensagem;

            printf("Entre com o seu apelido: \n");
            scanf("%s", nick);
            //funcao que checa e salva o nome se ja foi cadastrado
            User *user = get_user(users, nick);
            if (user == NULL){
              printf("Esse usuário não existe.");
            } else{
              printf("Para quem gostaria de enviar sua mensagem? >:?");
              scanf("%s", amigo)
              User *user_amigo = get_user(users, amigo);
              if (user_amigo == NULL){
                printf("Esse usuário não existe.");
              } else {
                printf("Escreva sua mensagem! >:DD");
                scanf("%s", mensagem);
                send_message(nick, amigo, mensagem);
              }
            }
        }

        else if(ordem == 6){ //ler mensagem
            char nick;
            printf("Entre com o seu apelido: \n");
            scanf("%c", nick);
            //funcao que checa e salva o nome se ja foi cadastrado
            User *user = get_user(users, nick);
            if (user == NULL){
              printf("Esse usuário não existe.");
            } else{
              printf("Aqui estão suas mensagens >:DD");
              //funcao que mostra mensagens
              get_messages(user->message_stack);
            }
        }

        else if(ordem == 7){ //sugerir amigo
            char* amigo1; //???
            char* amigo2; //???
            printf("Entre com o seu nome: \n");
        }

        else if(ordem == 8){ //desfazer amigo
            char* nick;
            char* amigo;
            printf("Entre com o seu nome: \n");
            scanf("%s", nick);
            ();

            printf("Com quem gostaria de terminar a Parceria?");
            scanf("%s", amigo);
            ();

            (); //funcao que exclui amigo
            printf("Sua Parceria foi desfeita com sucesso!");

        }

        else if(ordem == 9){ //Resetar sistema
          
        }

        else if(ordem == 1337){ //Encerra sessao

        }
    }


    printf("Ateh a proxima! >:DD");
}
