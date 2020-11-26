#ifndef friends_h_
#define friends_h_

#include <stdbool.h> 

typedef struct User User;

typedef struct FriendRequest {
    User *from;
    User *to;
    bool isfriend;
} FriendRequest;


typedef struct Friend
{
    FriendRequest *friend_request;
    struct Friend *next;
} Friend;


typedef struct FriendList {
    Friend *start;
    Friend *end;
} FriendList;

void add_friend_request(User *from, User *to);

void free_friend_node(FriendList *friendnode);

void add_friend(Friend *friendnode);

void decline_friend(Friend *friendnode);

bool is_friend(Friend *friendnode);

#endif