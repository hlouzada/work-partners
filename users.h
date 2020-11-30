#ifndef users_h_
#define users_h_

#include "messages.h"
#include "friends.h"

// Tipo onde serão guardados os usuários
typedef struct User {
        char* name; // Nome do usuário
        char* nick; // Apelido do usuário
        FriendList *friend_list; // Lista de amizades
        MessageStack *message_stack; // Lista de mensagens

        struct User *next;
} User;

// Lista de todos os usuários na rede.
typedef struct UserList {
        User *start;
} UserList;

// Função que gera um novo usuário
User * new_user(char* name, char* nick);

// Função que gera uma nova lista de usuários
UserList * new_user_list( User *user);

// Função que adiciona um novo usuário
UserList * push_user(UserList *list, User *user);

// Busca e retorna um usuário na lista
User * get_user(UserList *list, char* nick);

// Função que apaga um usuário
void delete_user(UserList **list, char* nick);

// Função que apaga toda a lista
void free_user_list(UserList **list);

#endif
