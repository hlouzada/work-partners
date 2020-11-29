#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "users.h"
#include "friends.h"
#include "messages.h"

// Função que recebe uma lista de usuários e libera a memória uutilizada por ela
// Se deletando, junto com suas sub-listas.
void reset_system(UserList **list){
        User *temp = (*list)->start;
        while (temp != NULL) {
                // Apagar mensagens
                if (temp->message_stack != NULL) {
                        free_message_stack(&(temp->message_stack));
                }
                // Apagar amizades
                if (temp->friend_list != NULL) {
                        delete_friendlist(&(temp->friend_list));
                }

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

// Função que aguarda o usuário confirmar que quer ir ao menu antes de mudar de tela
// Recebe nulo e devolve nulo.
void menu(){
        printf("\nPara voltar para o menu aperte enter.\n");
        getchar();
}

int main() {

        UserList *users = NULL; // lista de usuários
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
                printf("\nOla! Voce pode realizar as seguintes acoes:\n");
                printf("1- Cadastrar usuario.\n");
                printf("2- Listar usuarios.\n");
                printf("3- Enviar pedido de parceria.\n");
                printf("4- Avaliar pedidos de parceria.\n");
                printf("5- Enviar mensagem para um parceiro.\n");
                printf("6- Visualizar suas mensagens.\n");
                printf("7- Sugerir parcerias!\n");
                printf("8- Encerrar uma parceria.\n");
                printf("9- Reinicializar sistema.\n");

                printf("1337- Encerra a sessao.\n\n");
                printf("O que quer fazer?\n");

                scanf("%d", &ordem);
                getchar(); // Bug do read_string com scanf de pegar mais uma linha, não sei o pq

                // checar se o usuário colocou um valor válido
                if ((ordem > 9) || (ordem < 1)) {
                        if ((ordem!= 1337) || (ordem%1 != 0)) {
                                printf("Isso nao e um comando valido. Favor inserir um valor valido.\n");
                        }
                }

                if (ordem == 1) { //Cadastrar usuário
                        printf("Diga seu nome:\n");
                        char *nome = read_string();

                        if (nome != NULL) {
                                printf("Como gostaria de ser chamado?\n");
                                char *nick = read_string(); //funcao pra ler

                                if (nick != NULL) {

                                        if (users == NULL) {
                                                user = new_user(nome, nick);
                                                users = new_user_list(user);
                                        } else {
                                                while( get_user(users, nick ) != NULL) {
                                                        free(nick); // apaga o ponteiro com o mesmo
                                                        printf("Esse apelido ja esta sendo usado. Escolha outro apelido:\n");
                                                        nick = read_string();
                                                }
                                                user = new_user(nome, nick);
                                                users = push_user(users, user);
                                        }

                                        printf("\nSeja bem-vindo, %s! Esse sera o nome que deve usar nos comandos. \n", nick);
                                        menu();
                                } else {
                                        free(nome);
                                }
                        }
                }

                else if ((ordem == 2) && (users != NULL)) { //lista usuarios
                        printf("Aqui esta a lista de todos os usuarios e seus parceiros: \n");
                        // Cria um ponteiro temporário para iterar pelos usuários
                        temp = users->start;
                        while (temp != NULL) {
                                printf("%s (%s) com os parceiros: ", temp->name, temp->nick);
                                if( temp->friend_list != NULL) {
                                        temp_friend = temp->friend_list->start;
                                        while(temp_friend != NULL) {
                                                if(is_friend(temp_friend)) {
                                                        if (temp_friend->friend_request->from == temp) {
                                                                printf("%s, ", temp_friend->friend_request->to->nick);
                                                        } else {
                                                                printf("%s, ", temp_friend->friend_request->from->nick);
                                                        }
                                                }
                                                temp_friend = temp_friend->next;
                                        }
                                }

                                printf("\n");
                                temp = temp->next;
                        }
                        menu();
                }

                else if ((ordem == 3) && (users != NULL)) { //pedido amigo
                        printf("Entre com o seu apelido: \n");
                        char *nick = read_string();
                        if (nick != NULL) {
                                //funcao que checa e salva o nome se ja foi cadastrado
                                user = get_user(users, nick);
                                if (user == NULL) {
                                        printf("\nEsse usuario nao existe. Tente novamente!\n");
                                } else {
                                        printf("\nQuem voce gostaria de adicionar, %s ? Coloque o apelido. \n", nick);
                                        char *amigo = read_string();
                                        if (amigo != NULL) {
                                                //funcao que checa se o amigo existe e salva o nome
                                                user_amigo = get_user(users, amigo);
                                                free(amigo);
                                                if (user_amigo == NULL) {
                                                        printf("\nEsse usuarui nao existe. Tente novamente!\n");
                                                } else {
                                                        if (sent_request(user,user_amigo, false)) { //verificar se foi enviado pedido de amisade (false = nao verificar se o pedido foi aceito)
                                                                printf("\nVoce ja mandou pedido de amizade para esse usuario!\n");
                                                        } else {
                                                                add_friend_request(user, user_amigo);
                                                        }
                                                }
                                        }
                                }
                                free(nick);
                                menu();
                        }
                }

                else if ((ordem == 4) && (users != NULL)) { //avaliar pedido amigo
                        printf("\nEntre com o seu apelido: \n");
                        char *nick = read_string();
                        if (nick != NULL) {
                                //funcao que checa e salva o nome se ja foi cadastrado
                                user = get_user(users, nick);
                                free(nick);
                                if (user == NULL) {
                                        printf("\nEsse usuário não existe.\n");
                                } else {
                                        printf("\nEsses são seus pedidos de Parceiro: \n");
                                        printf("Digite A para Aceitar, N para Negar ou D pra Deixar pra mais tarde. \n");

                                        if (user->friend_list == NULL) {
                                                printf("\nVocê não tem pedidos de parceria\n");
                                        } else {
                                                char resposta;
                                                // Função que lista os pedidos de amigo
                                                temp_friend = user->friend_list->start;
                                                while(temp_friend != NULL) {
                                                        // Se eles já não forem amigos
                                                        if ((!is_friend(temp_friend)) && (user == temp_friend->friend_request->from)) {
                                                                printf("%s quer ser seu parceiro, você aceita?\n", temp_friend->friend_request->from->nick);
                                                                scanf("%c", &resposta);
                                                                if(resposta == 'A') { // Aceita o pedido
                                                                        accept_friend(temp_friend);
                                                                        printf("\nVoce e %s agora sao Parceiros!\n", temp_friend->friend_request->from->nick);
                                                                }
                                                                else if(resposta == 'N') { //nega o pedido
                                                                        decline_friend(user, temp_friend);
                                                                        printf("\nVoce recusou a Parceria de %s.\n", temp_friend->friend_request->from->nick);
                                                                }

                                                        }
                                                        temp_friend = temp_friend->next;
                                                }
                                                if(temp_friend == NULL) {
                                                        printf("\nVoce nao tem pedidos de parceria\n");
                                                }
                                        }
                                }
                                menu();
                        }
                }

                else if ((ordem == 5) && (users != NULL)) { //enviar mensagem

                        printf("Entre com o seu apelido: \n");
                        char* nick = read_string();
                        if (nick != NULL) {
                                //funcao que checa e salva o nome se ja foi cadastrado
                                user = get_user(users, nick);
                                free(nick);
                                if (user == NULL) {
                                        printf("\nEsse usuario nao existe. Tente novamente!\n");
                                } else{
                                        if (user->friend_list == NULL) {
                                                printf("\nVoce nao tem parceiros!\n");
                                        } else {
                                                printf("\nPara quem gostaria de enviar sua mensagem? >:?\n");
                                                char* amigo = read_string();
                                                if (amigo != NULL) {
                                                        user_amigo = get_user(users, amigo);
                                                        free(amigo);
                                                        if (user_amigo == NULL) {
                                                                printf("Esse usuario nao existe. Tente novamente!\n");
                                                        } else{
                                                                if (sent_request(user,user_amigo, true)) {//verificar se foi enviado pedido de amisade (true = verificar se o pedido foi aceito)
                                                                        printf("Voce soh pode enviar mensagens para seus parceiros.\n");
                                                                } else {
                                                                        printf("Escreva sua mensagem!\n");
                                                                        char *mensagem = read_string();
                                                                        send_message(user, user_amigo, mensagem);
                                                                }
                                                        }
                                                }
                                        }
                                }
                                menu();
                        }

                }

                else if ((ordem == 6) && (users != NULL)) { //ler mensagem
                        printf("Entre com o seu apelido: \n");
                        char *nick = read_string();
                        if (nick != NULL) {
                                //funcao que checa e salva o nome se ja foi cadastrado
                                user = get_user(users, nick);
                                free(nick);
                                if (user == NULL) {
                                        printf("Esse usuario nao existe. Tente novamente!\n");
                                } else {
                                        printf("Aqui estao suas mensagens\n");
                                        //funcao que mostra mensagens
                                        if(user->message_stack != NULL) {
                                                get_messages(user->message_stack);
                                        } else {
                                                printf("\nNao ha nenhuma mensagem\n");
                                        }
                                        menu();
                                }
                        }
                }

                else if ((ordem == 7) && (users != NULL)) { //sugerir amigo
                        printf("Entre com o seu apelido: \n");
                        char *nick = read_string();
                        if (nick != NULL) {
                                //funcao que checa e salva o nome se ja foi cadastrado
                                user = get_user(users, nick);
                                if (user == NULL) {
                                        printf("Esse usuario nao existe. Tente novamente!\n");
                                } else {
                                        printf("Sugerimos os seguintes usuarios para parceria:\n");
                                        temp = users->start;
                                        // vemos quais usuarios ainda não são amigos
                                        while(temp != NULL) {
                                                // check para ver se não estamos no usuário
                                                if(strcmp(temp->nick, nick) != 0) {
                                                        if (!sent_request(user, temp, false)) {
                                                                if (friends_in_common(temp->friend_list, user->friend_list)) {
                                                                        printf("\n Sugerimos o parceiro %s.\n", temp->nick);
                                                                }
                                                        }
                                                }
                                                temp = temp->next;

                                        }
                                }
                                free(nick);
                        }

                        menu();

                }

                else if ((ordem == 8) && (users != NULL)) { //desfazer amigo
                        printf("Entre com o seu nome: \n");
                        char *nick = read_string();
                        if (nick != NULL) {
                                user = get_user(users, nick);
                                free(nick);
                                if (user == NULL) {
                                        printf("Esse usuário não existe.\n");
                                }else if (user->friend_list == NULL) {
                                        printf("\nVoce nao tem parceiros!\n");
                                } else {
                                        printf("Qual parceiro voce gostaria de desfazer a parceria?\n");
                                        char *amigo = read_string();
                                        if (amigo != NULL) {
                                                user_amigo = get_user(users, amigo);
                                                free(amigo);
                                                if (user_amigo == NULL) {
                                                        printf("Esse usuário não existe.\n");
                                                } else if (user->friend_list != NULL) {
                                                        // Checar se são amigos primeiro
                                                        if (sent_request(user,user_amigo, true)) {
                                                                decline_friend(user, temp_friend);
                                                                printf("Sua Parceria foi desfeita com sucesso!\n");
                                                        } else {
                                                                printf("Você só pode desfazer parceria com seus parceiros.\n");
                                                        }

                                                }
                                        }
                                }
                        }
                        menu();
                }


                else if ((ordem == 9) && (users != NULL)) { //Resetar sistema
                        char choice;
                        printf("Você está prestes a apagar todos os dados da lista de usuários, tem certeza? (Y/N)\n");
                        scanf("%c", &choice);

                        if (choice == 'Y') {
                                reset_system(&users);
                        }

                        menu();

                }
                else if (ordem == 1337) { //Encerra sessao
                        char choice;
                        printf("Deseja encerrar o programa? (Y/N)\n");
                        scanf("%c", &choice);
                        if (choice == 'Y') {
                                if (users != NULL) {
                                        reset_system(&users);
                                }
                                printf("Até a próxima!\n");
                                break;
                        }
                        else {
                                ordem = 0;
                                menu();
                        }

                } else {
                        printf("\nNao ha usuarios cadastrados!\n");
                        menu();
                }
        }

        return 0;

}
