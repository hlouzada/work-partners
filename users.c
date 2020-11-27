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
    user->friend_list = NULL;
    user->message_stack = NULL;

    return user;
  }
}

// Função que cria nova lista
UserList * new_user_list(User *user){
  // Aloca o espaço na memória para a nova lista
  UserList *list = malloc(sizeof(UserList));
  // Verifica se a alocação funcionou
  if(!list){
    exit(1);
  }
  else{
    list->start = user;
    return list;
  }
}

// Função que adiciona um novo usuário
void push_user(UserList *list, User *user){
  // Checar se a lista existe
  if (list == NULL){
    // Se não existe criar nova lista
    list = new_user_list(user);
  }
  else{
  user->next = list->start;
  list->start = user;
  }
}
