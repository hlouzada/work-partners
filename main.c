#include <stdio.h>
#include <stdlib.h>

#include "users.h"
#include "friends.h"
#include "messages.h"

// Função que recebe uma lista de usuários e libera a memória uutilizada por ela
// Se deletando, junto com suas sub-listas.
void reset_system(UserList *list){
        User *temp = list->start;
        while (temp != NULL) {
                // Apagar mensagens
                free_message_stack(temp->message_stack);
                // Apagar amizades
                delete_friendlist(temp->friend_list);
                temp = temp->next;
        }
        // Apagar usuários
        free_user_list(list);
}

char * read_string() {
    char *str = NULL;
    int ch;
    size_t size = 0, len = 0;

    while ((ch=getchar()) != EOF && ch != '\n') {
        if (len + 1 >= size) {
            size = size * 2 + 1;
            str = realloc(str, sizeof(char)*size);
        }
        str[len++] = ch;
    }
    
    if (str != NULL) {
        str[len] = '\0';
    }

    return str;
}

int main(int argc, char *argv[]) {

        UserList *users = NULL; // lista de usuários
        char* nick; // apelido do usuário logado
        char* nome; // nome do usuário
        char* amigo; // nome do amigo
        char* mensagem; // texto da mensagem
        char choice;
        User *user = NULL;
        User *user_amigo = NULL;
        User *temp = NULL;
        Friend *temp_friend = NULL;

        // Interface de usuário
        // Lista-se as possíveis atividades e recebe ordem do usuário.
        int ordem = 0;

        while(ordem != 1337) {
                user = NULL;
                user_amigo = NULL;
                temp = NULL;
                temp_friend = NULL;
                printf("Olá! >:DD você pode realizar as seguintes ações:");
                printf("1- Cadastrar usuário. \n");
                printf("2- Listar usuários. \n");
                printf("3- Enviar pedido de parceria. \n");
                printf("4- Avaliar pedidos de parceria. \n");
                printf("5- Enviar mensagem para um parceiro. \n");
                printf("6- Visualizar suas mensagens. \n");
                printf("7- Sugerir parcerias! \n");
                printf("8- Encerrar uma parceria. \n");
                printf("9- Reinicializar sistema. \n");

                printf("1337- Encerra a sessão. \n \n");
                printf("O que quer fazer? >:? \n");

                scanf("%d", &ordem);
                printf("\n");
                // checar se o usuário colocou um valor válido
                if ((ordem > 9) || (ordem < 1)) {
                        if ((ordem!= 1337) || (ordem%1 != 0)) {
                                printf("Favor inserir um valor válido.\n");
                        }
                }

                if(ordem == 1) { //Cadastrar usuário
                        printf("Diga seu nome! >:DD \n");
                        nome = read_string();

                        printf("Como gostaria de ser chamado? >:? \n");
                        nick = read_string(); //funcao pra ler


                        if (users == NULL) {
                                user = new_user(nome, nick);
                                users = new_user_list(user);
                        } else {
                                while( get_user(users, nick ) != NULL) {
                                        free(nick); // apaga o ponteiro com o mesmo 
                                        printf("Esse apelido já está sendo usado, escolha outro apelido:\n");
                                        nick = read_string();
                                }
                                user = new_user(nome, nick);
                                users = push_user(users, user);
                        }

                        printf("Seja bem-vindo, %s >:DD esse será o nome que deve usar nos comandos. \n", nick);
                }

                else if(ordem == 2) { //lista usuarios
                        printf("Aqui está a lista de todos os usuários e seus parceiros: \n");
                        // Cria um ponteiro temporário para iterar pelos usuários
                        temp = users->start;
                        while (temp != NULL) {
                                printf("%s com os parceiros: ", temp->nick);
                                temp_friend = temp->friend_list->start;
                                while(temp_friend != NULL) {
                                        if(is_friend(temp_friend)) {
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

                else if(ordem == 3) { //pedido amigo
                        printf("Entre com o seu apelido: \n");
                        nick = read_string();
                        //funcao que checa e salva o nome se ja foi cadastrado
                        user = get_user(users, nick);
                        if (user == NULL) {
                                printf("Esse usuário não existe.");
                        } else {
                                printf("Quem você gostaria de adicionar, %s ? >:? Coloque o apelido. \n", nick);
                                amigo = read_string();
                                //funcao que checa se o amigo existe e salva o nome
                                user_amigo = get_user(users, amigo);
                                if (user_amigo == NULL) {
                                        printf("Esse usuário não existe.");
                                } else {
                                        add_friend_request(user, user_amigo);
                                }
                        }
                        free(nick);
                        free(amigo);
                }

                else if(ordem == 4) { //avaliar pedido amigo
                        printf("Entre com o seu apelido: \n");
                        nick = read_string();
                        //funcao que checa e salva o nome se ja foi cadastrado
                        user = get_user(users, nick);
                        free(nick);
                        if (user == NULL) {
                                printf("Esse usuário não existe.");
                        } else {

                                char resposta;
                                printf("Esses são seus pedidos de Parceiro: \n");
                                printf("Digite A para Aceitar, N para Negar ou D pra Deixar pra mais tarde. \n");

                                // Função que lista os pedidos de amigo
                                temp_friend = user->friend_list->start;
                                while(temp_friend != NULL) {
                                        // Se eles já não forem amigos
                                        if (!is_friend(temp_friend)) {
                                                printf("%s quer ser seu parceiro, você aceita?", temp_friend->friend_request->from->nick);
                                                scanf("%c", &resposta);
                                                if(resposta == 'A') { // Aceita o pedido
                                                        accept_friend(temp_friend);
                                                        printf("Voce e %s agora sao Parceiros!", temp_friend->friend_request->from->nick);
                                                }
                                                else if(resposta == 'N') { //nega o pedido
                                                        decline_friend(user, temp_friend);
                                                        printf("Voce recusou a Parceria de %s.", temp_friend->friend_request->from->nick);
                                                }
                                                printf("\n");
                                        }
                                        temp_friend = temp_friend->next;
                                }
                                if(temp_friend == NULL){
                                    printf("Voce nao tem pedidos de amigos >:[ ");
                                }
                        }

                }

                else if(ordem == 5) { //enviar mensagem

                        printf("Entre com o seu apelido: \n");
                        nick = read_string();
                        //funcao que checa e salva o nome se ja foi cadastrado
                        user = get_user(users, nick);
                        free(nick);
                        if (user == NULL) {
                                printf("Esse usuário não existe.");
                        } else{
                                printf("Para quem gostaria de enviar sua mensagem? >:?");
                                amigo = read_string();
                                user_amigo = get_user(users, amigo);
                                free(amigo);
                                if (user_amigo == NULL) {
                                        printf("Esse usuário não existe.");
                                } else {
                                        // Checar se são amigos primeiro
                                        temp_friend = user->friend_list->start;
                                        while(((temp_friend->friend_request->from != user_amigo) || (temp_friend->friend_request->to != user_amigo)) || (temp_friend != NULL) ) {
                                                if(is_friend(temp_friend)) {
                                                        printf("Escreva sua mensagem! >:DD");
                                                        mensagem = read_string();
                                                        send_message(user, user_amigo, mensagem);
                                                        printf("\n");
                                                } else { printf("Você só pode enviar mensagens para seus amigos.\n");}
                                                temp_friend = temp_friend->next;
                                        }

                                }
                        }
                }

                else if(ordem == 6) { //ler mensagem
                        printf("Entre com o seu apelido: \n");
                        nick = read_string();
                        //funcao que checa e salva o nome se ja foi cadastrado
                        user = get_user(users, nick);
                        free(nick);
                        if (user == NULL) {
                                printf("Esse usuário não existe.");
                        } else{
                                printf("Aqui estão suas mensagens >:DD");
                                //funcao que mostra mensagens
                                get_messages(user->message_stack);
                        }
                }

                else if(ordem == 7) { //sugerir amigo
                        printf("Entre com o seu nome: \n");
                }

                else if(ordem == 8) { //desfazer amigo
                        printf("Entre com o seu nome: \n");
                        nick = read_string();


                        printf("Com quem gostaria de terminar a Parceria?");
                        amigo = read_string();


                        //funcao que exclui amigo
                        printf("Sua Parceria foi desfeita com sucesso!");

                        free(nick);
                        free(amigo);

                }

                else if(ordem == 9) { //Resetar sistema
                        printf("Você está prestes a apagar todos os dados da lista de usuários, tem certeza? (Y/N)\n");
                        scanf("%c", &choice);

                        if (choice == 'Y') {reset_system(users);}

                }
                else if(ordem == 1337) { //Encerra sessao
                        printf("Deseja encerrar o programa? (Y/N)\n");
                        scanf("%c", &choice);
                        if (choice == 'Y') {
                                reset_system(users);
                                free(user);
                                free(user_amigo);
                                free(temp);
                                free(temp_friend);
                                free(users);
                                printf("Até a próxima! >:DD");
                                break;
                        }

                }
        }

        return 0;

}
