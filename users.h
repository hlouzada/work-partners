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
void add_user(UserList *list, User *user);

// Função que remove um usuário
void delete_user(UserList *list, char* username);

User * get_user_nick(char* nick);

#endif
