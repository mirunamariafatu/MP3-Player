// "Copyright 2020 Fatu Miruna"

#ifndef TEMA1_H_
#define TEMA1_H_

struct Node {
  char title[35];
  char artist[30];
  char album[35];
  char year[4];
  struct Node *next , *prev;
};

struct doubleList {
    struct Node *head;
    struct Node *tail;
    struct Node *cursor;
    int size;
};

void init_list(struct doubleList *list);

struct Node *createNode(char *fileName);

void addFirst(struct doubleList *list, struct Node *new);

void addLast(struct doubleList *list , struct Node *new);

void addAfter(struct doubleList *list , struct Node *curr , struct Node *new);

void delFirst(struct doubleList *list , FILE *out);

void delLast(struct doubleList *list , FILE* out);

void delCurr(struct doubleList *list , struct Node *curr , FILE* out);

void delSong(struct doubleList *list , char* fileName , FILE* out);

void check(struct doubleList *list , char *fileName , FILE *out);

void moveNext(struct doubleList *list , struct Node *curr , FILE* out);

void movePrev(struct doubleList *list , struct Node *curr , FILE* out);

void showFirst(struct Node *head , struct doubleList *list , FILE* out);

void showLast(struct Node *tail , struct doubleList *list , FILE* out);

void showCurr(struct Node *curr , struct doubleList *list , FILE* out);

void showPlaylist(struct doubleList *list , FILE* out);

void freeList(struct doubleList **pp_list);

#endif  //  TEMA1_H_
