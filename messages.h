#ifndef messages_h_
#define messages_h_

typedef struct Message * message;

typedef struct MessageStack * message_stack;

// Creates and returns a pointer to a new empty dynamic message stack
message_stack *create(void);

// Adds messages to the stack
void push(message_stack *p, message *m);

// Removes and returns the last message added to the stack
message pop(message_stack *p);

// Frees the memory occupied by the message stack
void free_menssage_stack(message_stack *p);

#endif