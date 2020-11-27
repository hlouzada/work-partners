#include <stdlib.h>

#include "friends.h"
#include "users.h"


// Cria uma nova instância de Struct FriendRequest
// Comum a cada nódulo Friend da lista de amigos do usuário
// Se isfriend for verdade para ambos os usuários significa que eles são amigos
// E o pedido foi aceito
FriendRequest * new_friendrequest(User *from, User *to) {
    // Aloca espaço para o pedido
    FriendRequest *newrequest = malloc(sizeof(FriendRequest));
    // Verifica se o malloc funcionou
    if (!newrequest) {
        exit(1);
    }

    newrequest -> from = from;
    newrequest -> to = to;
    newrequest -> isfriend = false;

    return newrequest;
}


// Cria uma nova instancia da struct Friend
// Cada usuário terá seu próprio amigo
// Cada um com sua própria lista de amigos
Friend * new_friend(FriendRequest *friendrequest) {

    Friend *newfriend = malloc(sizeof(Friend));
    if (!newfriend) {
        exit(1);
    }

    newfriend -> friend_request = friendrequest;
    newfriend -> next = NULL;

    return newfriend;
}


// Função que cria nova lista de amigos
// E adiciona uma um novo amigo para suas posições de inicio e fim
FriendList * new_friendlist(Friend *newfriend) {

    FriendList *new_friendlist = malloc(sizeof(FriendList));
    if (!new_friendlist) {
        exit(1);
    }

    new_friendlist -> start = newfriend;
    new_friendlist -> end = newfriend;

    return new_friendlist;
}


// Adiciona um novo amigo para o fim da lista de amigos
// ou cria um se uma se a lista não existe
FriendList * add_friend_to_list(FriendList *friendlist, Friend *newfriend) {
    if (friendlist == NULL) {
        FriendList* newfriendlist = new_friendlist(newfriend);
        friendlist = newfriendlist;
    } else {
        friendlist -> start -> next = newfriend;
        friendlist -> end = newfriend;
    }

    return friendlist;
}


// Envia um pedido de amizade ao usuário
// Adicionando um novo nódulo de amigo com um pedido de amizade
// para a lista de amizades de usuário
void add_user_request(User *user, FriendRequest *newrequest) {
    Friend *newfriend = new_friend(newrequest);

    user -> friend_list = add_friend_to_list(user -> friend_list, newfriend);
}


// Cria um novo pedido de amizade entre dois usuários
void add_friend_request(User *from, User *to) {
    FriendRequest* newrequest = new_friendrequest(from, to);

    add_user_request(from, newrequest);

    add_user_request(to, newrequest);
}



// Aceita o pedido de amizade
// Ao mudar a booleana isfriend para verdadeira
// Na interface isso pode ser usado
// Para verificar se o nódulo é um amigo confirmado ou um pedido.
void accept_friend(Friend *friendnode) {
    friendnode -> friend_request -> isfriend = true;
}


// Remove um nódulo de amigo da lista de amigos
// Verifica se o nódulo de amigos está no começo meio ou fim
// Para deletar de forma que a lista não quebre
// E libera a memória ocupada pelo nódulo do amigo
FriendList * remove_friend_from_list(FriendList *friendlist, Friend *friendnode) {
    if (friendlist -> start == friendnode) {
        friendlist -> start = friendnode -> next;
    } else {
        Friend *prev_temp = NULL;
        Friend *temp = friendlist -> start;
        while (temp != friendnode) {
            prev_temp = temp;
            temp = temp -> next;
        }
        if (friendlist -> end == friendnode) {
            prev_temp -> next = NULL;
            friendlist -> end = prev_temp;
        } else {
            prev_temp -> next = friendnode -> next;
        }
    }

    free(friendnode);

    return friendlist;
}


// Remove todos os amigos da lista e se auto deleta
// Liberando sua memória ocupada.
void delete_friendlist(FriendList *friendlist) {
    Friend *temp = friendlist -> start;
    while (friendlist -> start != NULL) {
        temp = temp -> next;
        if (friendlist -> start -> friend_request) {
            free(friendlist -> start -> friend_request);
        }
        free(friendlist -> start);
        friendlist -> start = temp;
    }
}


// Retorna o nódulo do amigo contendo o pedido de amizade da lista
Friend * get_friend_from_request(FriendList *friendlist, FriendRequest *request) {
    Friend *temp = friendlist -> start;
    while (temp -> friend_request != request) {
        temp = temp -> next;
    }

    return temp;
}


// Recusa o pedido de amizade
// Removendo o nódulo do amigo dos dois usuários
// E removendo o pedido compartilhado pelos dois.
void decline_friend(User *user, Friend *friendnode) {
    FriendRequest *request = friendnode -> friend_request;

    user -> friend_list = remove_friend_from_list(user -> friend_list, friendnode);

    User *other_user = NULL;
    if (user == request -> from) {
       other_user = request -> to;
    } else {
       other_user = request -> from;
    }

    Friend * other_friendnode = get_friend_from_request(other_user -> friend_list, request);

    // Removendo do outro usuário
    other_user -> friend_list = remove_friend_from_list(other_user -> friend_list, other_friendnode);

    free(request);
}


// Verifica se é um amigo ou um pedido
bool is_friend(Friend *friendnode) {
    return friendnode -> friend_request -> isfriend;
}
