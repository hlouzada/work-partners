#include <stdlib.h>

#include "friends.h"
#include "users.h"

Friend * new_friend(User *from, User *to) {
    Friend *newfriend = NULL;
    newfriend = (Friend *) malloc(sizeof(Friend));
    newfriend -> from = from;
    newfriend -> to = to;
    newfriend -> isfriend = false;

    return newfriend;
}

void send_friend_request(User *from, User *to) {
    Friend *newfriend = new_friend(from, to);
    
    FriendNode *new_friendnode_from = NULL;
    new_friendnode_from = (FriendNode *) malloc(sizeof(FriendNode));
    new_friendnode_from -> friends = newfriend;
    new_friendnode_from -> next = *(from -> friend_node);
    *(from -> friend_node) = new_friendnode_from;

    FriendNode *new_friendnode_to = NULL;
    new_friendnode_to = (FriendNode *) malloc(sizeof(FriendNode));
    new_friendnode_to -> friends = newfriend;
    new_friendnode_to -> next = *(to -> friend_node);
    *(to -> friend_node) = new_friendnode_to;
}

void add_friend(FriendNode *friendnode) {
    friendnode -> friends -> isfriend = true;
}