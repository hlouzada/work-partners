#include <stdlib.h>

#include "friends.h"
#include "users.h"

FriendNode * new_friend_node(User *from, User *to) {
    FriendNode *friendnode = NULL;
    friendnode = (FriendNode *) malloc(sizeof(FriendNode));
    friendnode -> from = from;
    friendnode -> to = to;
    friendnode -> isfriend = false;   
    friendnode -> next = NULL;
    return friendnode;
}

FriendNode * send_friend_request(User *from, User *to) {
    FriendNode *friendnode = new_friend_node(from, to);
    
    
    friendnode -> next = *(from -> friend_node);


    to -> friend_node = friendnode;

}

void add_friend(FriendNode *friendnode) {
    friendnode -> isfriend = true;
}