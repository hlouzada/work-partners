#ifndef messages_h_
#define messages_h_

typedef struct User User;

// Tipo onde serão guardadas as mensagens individuais
typedef struct Message
{
        char* text; // Texto da mensagem
        User *to; // Apelido de quem enviou
        User *from; // Apelido de quem vai receber
        struct Message *next;
} Message;

// Listas de mensagem de cada usuário.
typedef struct MessageStack {
        Message *start;
} MessageStack;

// Envia uma nova mensagem
void send_message(User *from, User *to, char* text);

// Retorna e imprime as mensagens da pilha
void get_messages(MessageStack *stack);

// Apaga a pilha de mensagens
void free_message_stack(MessageStack *stack);

#endif
