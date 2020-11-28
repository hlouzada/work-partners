#ifndef friends_h_
#define friends_h_

#include <stdbool.h>

typedef struct User User;

// Estrutura onde ficarão os pedidos de amizade entre dois usuários
// Essa estrutura é compartilhada entre quem recebeu e quem enviou o pedido
typedef struct FriendRequest {
    User *from; // usuário que enviou a mensagem
    User *to; // usuário que recebe a mensagem
    bool isfriend; // se a pedido de amizade foi aceito
} FriendRequest;

// Estrutura que aponta para os pedidos recebidos
typedef struct Friend
{
    FriendRequest *friend_request;
    struct Friend *next;
} Friend;

// Lista de pedidos recebidos
typedef struct FriendList {
    Friend *start;
    Friend *end;
} FriendList;

// Função que cria novo pedido de amizade
void add_friend_request(User *from, User *to);

// Função que deleta lista toda
void delete_friendlist(FriendList **friendlist);

// Função para confirmar pedido de amizade
void accept_friend(Friend *friendnode);

// Função para declinar pedido de amizade
void decline_friend(User *user, Friend *friendnode);

// Função que verifica se ainda são amigos
bool is_friend(Friend *friendnode);

// Função que vai checkar se tem amigos em commum
bool friends_in_common(FriendList *friendlist1, FriendList *friendlist2);

#endif
