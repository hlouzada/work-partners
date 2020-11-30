#include <stdlib.h>
#include <stdio.h>

#include "messages.h"
#include "users.h"

// Cria uma nova mensagem
Message * new_message(User *from, User *to, char* text){

        // Aloca espaço na memória para a nova mensagem
        Message *message = malloc(sizeof(Message));
        // Verifica se a alocação funcionou
        if (!message) {
                exit(1);
        } else {
                message->text = text;
                message->to = to;
                message->from = from;

                message->next = NULL;

                return message;
        }
}

// Cria nova lista de mensagens
MessageStack * new_message_stack(Message *start){
        // Aloca espaço na memória para a nova lista
        MessageStack *stack = malloc(sizeof(MessageStack));
        // Verifica se a alocação funcionou:
        if(!stack) {
                exit(1);
        } else {
                stack->start = start;
                return stack;
        }
}

// Adiciona uma nova mensagem à lista de mensagens
MessageStack * push_message(MessageStack *stack, Message *message){
        // Checar se a pilha existe:
        if (stack == NULL) {
                // Se não existe criar nova pilha
                MessageStack *newstack = new_message_stack(message);
                stack = newstack;
        } else{
                message->next = stack->start;
                stack->start = message;
        }

        return stack;
}

// Cria uma nova mensagem  e adiciona uma mensagem
// na lista de mensagens do usuário que vai receber
void send_message(User *from, User *to, char* text) {
        Message *newmessage = new_message(from, to, text);

        to->message_stack = push_message(to->message_stack, newmessage);
}


// Retorna e imprime as mensagens da pilha
void get_messages(MessageStack *stack){
        // Cria um ponteiro temporário para iterar
        Message *temp = stack->start;
        // Enquanto não chegar no fim da fila
        while (temp != NULL) {
                printf("(%s) %s\n", (temp->from)->nick, temp->text);
                temp = temp->next;
        }
}

// Apagar a pilha de mensagens
void free_message_stack(MessageStack **stack) {
        // Criar um ponteiro temporário para guardar o próximo
        Message *head = (*stack)->start;
        Message *temp;
        // Enquanto o começo não for nulo
        while (head != NULL) {
                // Colocar o próximo valor da pilha no temporário
                temp = head;
                head = head->next;
                // Apagar o valor do topo
                free(temp->text); // Apagar a mensagem salva
                temp->text = NULL;
                free(temp);
                temp = NULL;
        }
        free(*stack);
}
