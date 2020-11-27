#include <stdlib.h>

#include "friends.h"
#include "users.h"


// Creates a new FriendRequest Struct instance
// Common to each Friend node from user's friend list 
// If isfriend is true means that the users are friend
// And the request has being accepted
FriendRequest * new_friendrequest(User *from, User *to) {
    FriendRequest *newrequest = NULL;

    newrequest = (FriendRequest *) malloc(sizeof(FriendRequest));
    if (!newrequest) {
        exit(1);
    }

    newrequest -> from = from;
    newrequest -> to = to;
    newrequest -> isfriend = false;

    return newrequest;
}


// Creates a new Friend struct instance
// Each user will have it's own friend
// With it's own FriendList
Friend * new_friend(FriendRequest *friendrequest) {
    Friend *newfriend = NULL;

    newfriend = (Friend *) malloc(sizeof(Friend));
    if (!newfriend) {
        exit(1);
    }

    newfriend -> friend_request = friendrequest;
    newfriend -> next = NULL;

    return newfriend;
}


// Creates a new FriendList
// And adds a new friend to it's start and end pointers
FriendList * new_friendlist(Friend *newfriend) {
    FriendList *new_friendlist = NULL;

    new_friendlist = (FriendList *) malloc(sizeof(FriendList));
    if (!new_friendlist) {
        exit(1);
    }

    new_friendlist -> start = newfriend;
    new_friendlist -> end = newfriend;

    return new_friendlist;
}


// Adds a new friend to the end of friendlist
// or create it if the list doesn't exist
FriendList * add_friend_to_list(FriendList *friendlist, Friend *newfriend) {
    if (friendlist == NULL) {
        FriendList* newfriendlist = new_friendlist(newfriend);
        friendlist = newfriendlist;
    } else {
        friendlist -> start -> next = newfriend;
        friendlist -> end = newfriend;
    }

    return friendlist;
}


// "Sends" a friend request to a user
// By adding a new friend node with a friendrequest to it's friend list 
void add_user_request(User *user, FriendRequest *newrequest) {
    Friend *newfriend = new_friend(newrequest);

    user -> friend_list = add_friend_to_list(user -> friend_list, newfriend);
}


// Create a new friend request between two users
// With a shared friend request
void add_friend_request(User *from, User *to) {
    FriendRequest* newrequest = new_friendrequest(from, to);

    add_user_request(from, newrequest);

    add_user_request(to, newrequest);
}


// Accepts the friend request
// by changing it's boolean isfriend to true
// In the interface this can be used 
// to see if it's a proper friend or a request 
void accept_friend(Friend *friendnode) {
    friendnode -> friend_request -> isfriend = true;
}

// Checks if it's a friend or a request
bool is_friend(Friend *friendnode) {
    return friendnode -> friend_request -> isfriend;
}