#include <stdlib.h>
#include <string.h>

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
UserList * push_user(UserList *list, User *user){
  // Checar se a lista existe
  if (list == NULL){
    // Se não existe criar nova lista
    list = new_user_list(user);
  }
  else{
  user->next = list->start;
  list->start = user;
  }

  return list;
}

// Função que retorna um usuário na lista
User * get_user(UserList *list, char* nick){
  // Cria um ponteiro temporário para iterar
  User *temp = list->start;
  // Enquanto o apelido do temporário não for igual ao dado
  // Ou até chegarmos no final da lista
  while ((strcmp(temp->nick, nick) != 0) && (temp->next != NULL)){
    temp = temp->next;
  }
  // Caso estejamos no último elemento e ainda não seja igua;
  if (strcmp(temp->nick, nick) != 0){
    //Se o usuário não existe retornamos um usuário nulo
    return NULL;
  }
  else{
    return temp;
  }
}

// Função que deleta um único usuário
// Favor não esquecer de deletar a lista de amigos e de mensagens do usuário primeiro
void delete_user(UserList **list, char* nick){
  // Encontrar o usuário que vem antes do que queremos deletar
  // Para isso criamos um temporário para iterar:
  User *temp = (*list)->start;
  // Enquanto o apelido do temporário não for igual ao dado
  // Ou até chegarmos no final da lista
  while ((strcmp(temp->nick, nick) != 0) && (temp->next != NULL)){
    temp = temp->next;
  }
  // Caso estejamos no último elemento e ainda não seja igua;
  if (strcmp(temp->nick, nick) != 0) {
    //Se o usuário não existe retornamos um usuário nulo
    exit(1);
  }
  else{
    User *previous = temp;
    // Achamos o ponteiro que queremos deletar
    User *user = previous->next;
    previous->next = user->next;
    free(user->name); // Apaga o ponteiro do nome
    user->name = NULL;
    free(user->nick); // Apaga o pointeiro do nick
    user->nick = NULL;
    free(user);
  }
}

// Função que apaga toda a lista
// Favor não esquecer de apagar as listas de amizades e mensagens dos usuários primeiro
void free_user_list(UserList **list){
  // Criar um ponteiro temporário para guardar o próximo
  User *head = (*list)->start;
  User *temp;
  // Enquanto o começo não for nulo
  while (head != NULL){
    // Colocar o próximo valor da pilha no temporário
    temp = head;
    head = head->next;
    // Apagar o valor do topo
    free(temp->name);
    temp->name = NULL;
    free(temp->nick);
    temp->nick = NULL;
    free(temp);
  }
  free(*list);
  *list = NULL;
}
