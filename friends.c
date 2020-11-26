#include <stdlib.h>

#include "friends.h"
#include "users.h"

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

void add_user_request(User *user, FriendRequest *newrequest) {
    if (user -> friend_list == NULL) {
        Friend *newfriend = new_friend(newrequest);
        FriendList* newfriendlist = new_friendlist(newfriend);

        user -> friend_list = newfriendlist;
    } else {
        Friend *newfriend = new_friend(newrequest);

        user -> friend_list -> start -> next = newfriend;
        user -> friend_list -> end = newfriend;
    }
}


void add_friend_request(User *from, User *to) {
    FriendRequest* newrequest = new_friendrequest(from, to);

    add_user_request(from, newrequest);

    add_user_request(to, newrequest);
}

void add_friend(Friend *friendnode) {
    friendnode -> friend_request -> isfriend = true;
}

bool is_friend(Friend *friendnode) {
    return friendnode -> friend_request -> isfriend;
}