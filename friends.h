#ifndef friends_h_
#define friends_h_

#include <stdbool.h> 

typedef struct User User;

typedef struct Friend {
    User *from;
    User *to;
    bool isfriend;
} Friend;

typedef struct FriendNode {
    Friend *friends;
    struct FriendNode *next;
} FriendNode;


void add_friend(FriendNode *friendnode);

void send_friend_request(User *from, User *to);

#endif