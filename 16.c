#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* prev;
    int data;              
    struct Node* next;
} Node;

Node* addNodeUp(Node* head, int data, Node** tail) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        *tail = newNode;
        return newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode; 
        return head;
    }
}
Node* addNodeDown(Node* head, int data, Node** tail) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        *tail = newNode;
        return newNode;
    } else {
        newNode->prev=*tail;
        *tail = newNode; 
        return head;
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* up_list = NULL; 
    Node* down_list = NULL; 
    Node *firstTail = NULL, *secondTail = NULL;
    Node* S = NULL;
    int data, count = 0;

    printf("Введите последовательность чисел (0 для окончания ввода)\n");
    while (1) {
        scanf("%d", &data);
        if (data == 0) break;

        count++;
        if (count % 2 == 1) {
            up_list = addNodeUp(up_list, data, &firstTail);
            if (S == NULL) {S = up_list;firstTail->prev=NULL;}
        } else {
            down_list = addNodeDown(down_list, data, &secondTail);
            if (count==2) secondTail->prev=up_list;
            else firstTail->prev=secondTail;
        }
    }

    if (firstTail && secondTail) {
        firstTail->prev = secondTail;
        firstTail->next=down_list;
    }

    printf("Первый список:\n");
    printList(up_list);
    
    printf("Второй список:\n");
    printList(down_list);

    printf("Нажмите 'a'чтобы пойти влево(или вниз) или 'd' чтобы пойти вправо. Для выхода нажмите любую другую клавишу\n");
    Node *lst_ptr = up_list;
    Node* Snd_ptr = down_list;
    char c;
    getchar();
    while(1) {
        char key = 'f';

        printf("Значение: %d; предыдущее: %p следующее: %p\n", lst_ptr->data, lst_ptr->prev, lst_ptr->next);
        scanf("%c%*c", &key);
        

        printf("Выберите действие: '%c'\n", key);
        if (key == 'a') {
            if (lst_ptr->prev)
                lst_ptr = lst_ptr->prev;
            else 
                printf("Вы не можете пойти сюда, значение NULL\n");
            
        } else if(key == 'd') {
            if (lst_ptr->next)
                lst_ptr = lst_ptr->next;
            else
                printf("Вы не можете пойти сюда, значение NULL\n");

        } else {
            printf("Exiting..\n");
            break;
        }
    }

    freeList(up_list);
    freeList(down_list);

    return 0;
}