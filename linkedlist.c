#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int buffer_size = 20;

typedef struct _node
{
    struct _node *next;
    struct _node *prev;
    char data[buffer_size];
} Node;

#define NODE void *

NODE ll_create(char *data)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    memset(node->data, buffer_size, 0);
    strcpy(node->data, data);
    return node;
}

/* There are 6 pointers to consider
   CurrentNode -> Next must point to new node
   CurrentNode -> Prev is unchanged
   NewNode -> Next must point to originalNextNode
   NewNode -> Prev points to CurrentNode
   OriginalNextNode -> Next is unchanged
   OriginalNextNode -> Prev points to NewNode
*/
void ll_insert(NODE current_node, char *data)
{
    Node * newNode = (Node *)ll_create(data);
    
    Node * original_next_node = ((Node *)current_node)->next;
    ((Node *)current_node)->next = newNode;
    
    if(original_next_node != NULL)
        original_next_node->prev = newNode;
    
    newNode->prev = current_node;
    newNode->next = original_next_node;
}

/* There are 6 pointers to consider
   CurrentNode -> Next must point to new node
   CurrentNode -> Prev is unchanged
   NewNode -> Next is unchanged
   NewNode -> Prev points to CurrentNode
   OriginalNextNode -> Next is unchanged
   OriginalNextNode -> Prev points to NewNode
*/
NODE ll_remove(NODE current_node)
{
    NODE returnvalue = NULL;
    Node *theNode = (Node *)current_node;
    if(theNode->prev) theNode->prev->next = theNode->next;
    if(theNode->next) theNode->next->prev = theNode->prev;

    if(theNode->next) returnvalue = theNode->next;
    else if(theNode->prev) returnvalue = theNode->prev;

    free(theNode);

    return returnvalue;
}

NODE ll_next(NODE current)
{
    if(current) {
        return ((Node *)current)->next;
    }
    else
        return NULL;
}

NODE ll_prev(NODE current)
{
    if(current)
        return ((Node *)current)->prev;   
    else
        return NULL;
}

void ll_data(NODE current, char *buffer, int length)
{
    memset(buffer, length, 0);
    if(current) {
        strcpy(buffer, ((Node *)current)->data);
    }
}

void ll_set_data(NODE current, char *data)
{
    if(current) {
        Node *node = (Node *)current;
        memset(node->data, buffer_size, 0);
        strcpy(node->data, data); 
    }
}
    
void instructions()
{
    printf("display <enter> - displays contents of list\n");
    printf("insert x <enter> - inserts 'x' after the current node. If list is empty, creates list.\n");
    printf("remove <enter> - removes current node.\n");
    printf("set x <enter> - sets contents of current node to 'x'.\n");
    printf("read <enter> - reads contents of current node.\n");
    printf("next <enter> - moves to the next node in the list.\n");
    printf("prev <enter> - moves to the previous node in the list.\n");
    printf("quit <enter> - quits program.\n\n");
    printf("Be kind - can only handle small input.\n\n");
}

int main()
{
    instructions();
    int done = 0;

    NODE head = NULL;
    NODE current = NULL;
    NODE iterator = NULL;

    /* caution, unsafe code. */
    char buffer[buffer_size];
    char input[buffer_size];
    char data[buffer_size];
    while(!done) {
        memset(buffer, buffer_size, 0);
        printf("> ");
        scanf("%s", buffer);
        
        if(strncmp(buffer, "display", strlen("display")) == 0) {
            if(head) {
                iterator = head;
                while(iterator) {
                    ll_data(iterator, data, buffer_size);
                    printf("%s ", data); 
                    iterator = ll_next(iterator);
                }
                printf("\n");
            }
        }
        else if(strncmp(buffer, "insert", strlen("insert")) == 0) {
            scanf("%s", input);
            if(current) 
                ll_insert(current, input);
            else {
                head = ll_create(input);
                current = head;
            }
        }
        else if(strncmp(buffer, "remove", strlen("remove")) == 0) {
            if(current) {
                current = ll_remove(current);
            }
        }
        else if(strncmp(buffer, "set", strlen("set")) == 0) {
            scanf("%s", input);
            if(current) {
                ll_set_data(current, input);
            }
        }
        else if(strncmp(buffer, "read", strlen("read")) == 0) {
            if(current) {
                ll_data(current, data, buffer_size);
                printf("%s\n", data);
            }
        }
        else if(strncmp(buffer, "next", strlen("next")) == 0) {
            if(current) {
                NODE next = ll_next(current);
                if(next)
                    current = next;
                else
                    printf("at end.\n");
            }
        }
        else if(strncmp(buffer, "prev", strlen("prev")) == 0) {
            if(current) {
                NODE prev = ll_prev(current);
                if(prev) 
                    current = prev;
                else
                    printf("at beginning.\n");
            }
        }
        else if(strncmp(buffer, "quit", strlen("quit")) == 0) {
            done = 1;
        }
    }
    
    return 0;
}