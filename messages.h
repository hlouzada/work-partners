#ifndef messages_h_
#define messages_h_

typedef struct User User;

typedef struct Message
{
    char* message;
    struct Message *next;
} Message;


typedef struct MessageStack {
    Message *start;
} MessageStack;



// Adds messages to the stack
void push_message(MessageStack *p, Message *m);

// returns the message added to the stack
Message get_message(MessageStack *p);

#endif
