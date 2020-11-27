#include <stdlib.h>
#include "users.h"

// Função que gera um novo usuário
User * new_user(char*name, char* nick){
  // Aloca espaço para o novo usuário
  User *user = malloc(sizeof(User));
  // Verificar se a alocação funcionou:
  if(!user){
    exit(1);
  }
  else{
    user->name = name;
    user->nick = nick;
    user->next = NULL;

    // Será que precisa declarar a friendlist e a messagestack como null
    //ou deixa para serem inicializadas quando forem usadas?

    return user;
  }
}

/*User * new_user(char *name, char *nick) {
    User *user = NULL;
    user = (User *) malloc(sizeof(User));
    user -> name = name;
    user -> nick = nick;
    user -> friend_list = NULL;
    user -> message_stack = NULL;

    return user;
   }*/


/*UserNode * new_user_list(User *u) {
        UserNode *head = NULL;
        head = (UserNode *) malloc(sizeof(UserNode));
        head->user = u;
        head->next = NULL;

        return head;
}*/


/*void push_user(UserNode **head, User *u) {
        UserNode * new_usernode;
        new_usernode = (UserNode *) malloc(sizeof(UserNode));

        new_usernode->user = u;
        new_usernode->next = *head;
        *head = new_usernode;
}*/
