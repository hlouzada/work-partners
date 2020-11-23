#ifndef friends_h_
#define friends_h_

#include "users.h"


typedef struct FriendNode {
    User *user;
    struct FriendNode *next;
} FriendNode;


void add_friend(FriendNode *p, User *u);

#endif