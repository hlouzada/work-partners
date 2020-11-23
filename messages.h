#ifndef messages_h_
#define messages_h_


typedef struct Message {
    char* message;
    char* from;
    char* to;
} Message;


typedef struct MessageNode {
    Message *message;
    struct MessageNode *top;
} MessageNode;


// Adds messages to the stack
void push_message(MessageNode *p, Message *m);

// returns the message added to the stack
Message get_message(MessageNode *p);

#endif