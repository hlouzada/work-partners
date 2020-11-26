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
        }
        else{
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
        }
        else{
                stack->start = start;
                return stack;
        }
}

// Adiciona uma nova mensagem à lista
void push_message(MessageStack *stack, Message *message){
  // Checar se a pilha existe:
  if (stack== NULL){
    // Se não existe criar nova pilha
    stack = new_message_stack(message);
  }

  message->next = stack->start;
  stack->start = message;

}

// Retorna e imprime as mensagens da pilha
void get_messages(MessageStack *stack){
  // Cria um ponteiro temporário para iterar
  Message *temp = stack->start;
  // Enquanto não chegar no fim da fila
  while (temp != NULL){
    printf("(%s) %s", (temp->from)->nick, temp->text);
    temp = temp->next;
  }
}

// Apagar a pilha de mensagens
void free_message_stack(MessageStack *stack){
  // Criar um ponteiro temporário para guardar o próximo
  Message *temp = NULL;
  // Enquanto o começo não for nulo
  while (stack->start != NULL){
    // Colocar o próximo valor da pilha no temporário
    temp = (stack->start)->next;
    // Apagar o valor do topo
    free(stack->start);
    // Colocar o valor do temporário como topo.
    stack->start = temp;
  }
}
