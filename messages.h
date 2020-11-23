#ifndef messages_h_
#define messages_h_


typedef struct Message {
    char* message;
    char* from;
    char* to;
} Message;


typedef struct MessageNode {
    Message *message;
    MessageNode *top;
} MessageNode;


// Adds messages to the stack
void push(MessageNode *p, Message *m);

// returns the message added to the stack
Message get(MessageNode *p);

#endif