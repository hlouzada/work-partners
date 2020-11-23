#ifndef users_h_
#define users_h_

#include "messages.h"


typedef struct User {
    char* name;
    char* nick;
    MessageNode *first_message;
} User;


typedef struct UserNode {
    User *user;
    struct UserNode *next;
} UserNode;


User new_user(char* name, char* nick);

void push(UserNode *p, User *u);


#endif