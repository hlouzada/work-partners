#ifndef users_h_
#define users_h_

#include "messages.h"
#include "friends.h"

typedef struct User {
    char* name;
    char* nick;
    FriendNode **friend_node;
    MessageNode **message_node;
} User;


typedef struct UserNode {
    User *user;
    struct UserNode *next;
} UserNode;


User * new_user(char* name, char* nick);

UserNode * new_user_list(User *u);

void push_user(UserNode **head, User *u);

User * get_user_nick(char* nick);

#endif