#ifndef friends_h_
#define friends_h_

#include <stdbool.h> 

typedef struct User User;

typedef struct FriendNode {
    User *from;
    User *to;
    bool isfriend;
    struct FriendNode *next;
} FriendNode;


void add_friend(FriendNode *friendnode);

FriendNode * send_friend_request(User *from, User *to);

#endif