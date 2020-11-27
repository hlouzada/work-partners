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


// Removes a friend node from the friend list
// checks if the friend node is in the start, middle or end
// to delete so the list dosen't break
// and frees the occupied friend node's memory 
FriendList * remove_friend_from_list(FriendList *friendlist, Friend *friendnode) {
    if (friendlist -> start == friendnode) {
        friendlist -> start = friendnode -> next;
    } else {
        Friend *prev_temp = NULL;
        Friend *temp = friendlist -> start;
        while (temp != friendnode) {
            prev_temp = temp;
            temp = temp -> next;
        }
        if (friendlist -> end == friendnode) {
            prev_temp -> next = NULL;
            friendlist -> end = prev_temp;
        } else {
            prev_temp -> next = friendnode -> next;
        }
    }

    free(friendnode);

    return friendlist;
}


// Returns the Friend node containg the FriendRequest from the list
Friend * get_friend_from_request(FriendList *friendlist, FriendRequest *request) {
    Friend *temp = friendlist -> start;
    while (temp -> friend_request != request) {
        temp = temp -> next;
    }

    return temp;
}


// Decline the friend request
// by removing the friend node from the "from" and "to" users
// and removing it's shared request
void decline_friend(User *user, Friend *friendnode) {
    FriendRequest *request = friendnode -> friend_request;
    
    user -> friend_list = remove_friend_from_list(user -> friend_list, friendnode);

    User *other_user = NULL;
    if (user == request -> from) {
       other_user = request -> to;
    } else {
       other_user = request -> from;
    }

    Friend * other_friendnode = get_friend_from_request(other_user -> friend_list, request);

    //removing from the other user
    other_user -> friend_list = remove_friend_from_list(other_user -> friend_list, other_friendnode);

    free(request);
}


// Checks if it's a friend or a request
bool is_friend(Friend *friendnode) {
    return friendnode -> friend_request -> isfriend;
}