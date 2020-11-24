#include <stdlib.h>
#include "users.h"


User * new_user(char *name, char *nick) {
    User *user = NULL;
    user = (User *) malloc(sizeof(User));
    user -> name = name;
    user -> nick = nick;
    user -> friend_node = NULL;
    user -> message_node = NULL;
    
    return user;
}


UserNode * new_user_list(User *u) {
    UserNode *head = NULL;
    head = (UserNode *) malloc(sizeof(UserNode));
    head -> user = u;
    head -> next = NULL;
    
    return head;
}


void push_user(UserNode **head, User *u) {
    UserNode * new_usernode;
    new_usernode = (UserNode *) malloc(sizeof(UserNode));
    
    new_usernode -> user = u;
    new_usernode -> next = *head;
    *head = new_usernode;
}