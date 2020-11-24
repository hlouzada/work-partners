#ifndef messages_h_
#define messages_h_

typedef struct User User;

typedef struct Message {
    char* message;
    User *from;
    User *to;
} Message;


typedef struct MessageNode {
    Message *message;
    struct MessageNode *next;
} MessageNode;


// Adds messages to the stack
void push_message(MessageNode *p, Message *m);

// returns the message added to the stack
Message get_message(MessageNode *p);

#endif