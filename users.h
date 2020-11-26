#ifndef users_h_
#define users_h_

#include "messages.h"
#include "friends.h"

typedef struct User {
    char* name;
    char* nick;
    FriendList *friend_list;
    MessageStack *message_stack;

    struct User *next;
} User;


typedef struct UserList {
    User *start;
} UserList;


User * new_user(char* name, char* nick);

UserList * new_user_list(User *u);

void push_user(UserList **head, User *u);

User * get_user_nick(char* nick);

#endif