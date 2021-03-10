// "Copyright 2020 Fatu Miruna"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "./tema1.h"

void init_list(struct doubleList *list){
  list->head = NULL;
  list->tail = NULL;
  list->cursor = NULL;
  list->size = 0;
}

struct Node *createNode(char *fileName){
  char input[100] = "songs/";
  snprintf(input + strlen(input) , 100- strlen(input) , "%s" , fileName);
  struct Node *new;
  char v[4];
  new = malloc(sizeof(struct Node));
  FILE *in;
  if ((in = fopen(input , "rb")) == NULL) {
        fprintf(stderr , "Can't open %s\n" , input);
        return NULL;
    }
  fseek(in , 0 , SEEK_END);
  fseek(in , -97 , SEEK_END);
  fread(v , sizeof(char) , 3 , in);
  fread(new->title , sizeof(char) , 30 , in);
  new->title[30] = '\0';
  fread(new->artist , sizeof(char) , 30 , in);
    new->artist[30] = '\0';
  fread(new->album , sizeof(char) , 30 , in);
    new->album[30] = '\0';
  fread(new->year , sizeof(char) , 4 , in);
    new->year[4] = '\0';
  fclose(in);
  return new;
}

void addFirst(struct doubleList *list, struct Node *new) {
  if (list == NULL) {
  return;
  }
  if (list->size == 0){
    new -> next = NULL;
    new -> prev = NULL;
    list -> head = new;
    list -> tail = new;
    list -> cursor = list->head;
    list -> size++;
  } else {
    new -> prev = NULL;
    new -> next = list -> head;
    list->head->prev = new;
    list -> head = new;
    list -> size++;
  }
}

void addLast(struct doubleList *list , struct Node *new) {
  if (list == NULL) {
  return;
  }
  if (list->size == 0){
    new -> next = NULL;
    new -> prev = NULL;
    list -> head = new;
    list -> tail = new;
    list -> cursor = new;
    list -> size++;
  } else {
    new -> next = NULL;
    list -> tail -> next = new;
    new -> prev = list -> tail;
    list -> tail = new;
    list -> size++;
  }
}

void addAfter(struct doubleList *list , struct Node *curr , struct Node *new) {
  if (curr->next == NULL) {
    addLast(list , new);
  } else {
    struct Node *tmp1;
    tmp1 = curr -> next;
    new -> next = tmp1;
    new -> prev = curr;
    tmp1 -> prev = new;
    curr -> next = new;
    list -> size++;
  }
}

void delFirst(struct doubleList *list , FILE *out) {
  if (list->size == 0){
    fprintf(out , "Error: delete from empty playlist\n");
  } else {
    if (list->cursor == list->head) {
      list->cursor = list->cursor->next;
    }
    if (list -> size == 1) {
    struct Node *t1;
    t1 = list -> head;
      list -> head = NULL;
      list -> size--;
     free(t1);
    } else {
    struct Node *t1;
    t1 = list -> head;
    list -> head = list -> head -> next;
    list -> head -> prev = NULL;
    list -> size--;
    free(t1);
    }
  }
}

void delLast(struct doubleList *list , FILE* out){
  if (list->size == 0) {
    fprintf(out, "Error: delete from empty playlist\n");
  } else {
    if (list->cursor == list->tail) {
      list->cursor = list->tail->prev;
    }
    if (list->size == 1) {
     struct Node *t2;
     t2 = list->head;
      list->head = NULL;
      list->size--;
      free(t2);
    } else {
    struct Node *t1;
    t1 = list->tail;
    list->tail = t1->prev;
    list->tail->next = NULL;
    list->size--;
    free(t1);
    }
  }
}

void delCurr(struct doubleList *list , struct Node *curr , FILE* out){
  if (curr == NULL || list->size == 0) {
    fprintf(out, "Error: no track playing\n");
  } else if (curr == list->head) {
    delFirst(list , out);
  } else if (curr == list->tail) {
    delLast(list , out);
  } else {
    if (curr->next != NULL) {
      list->cursor = curr->next;
     } else if (curr->prev != NULL) {
      list->cursor = curr->prev;
     }
    struct Node *tmp1 , *tmp2 , *tmp3;
    tmp3 = curr;
     tmp1 = tmp3->prev;
     tmp2 = tmp3->next;
     tmp1->next = tmp2;
     tmp2->prev = tmp1;
     free(tmp3);
     list->size--;
    }
  }

void delSong(struct doubleList *list , char* fileName , FILE* out) {
  struct Node *t1 , *t2;
  struct Node *tmp1 , *tmp2;
  t2 = createNode(fileName);
  t1 = list->head;
  while (t1 != NULL) {
    if (strcmp(t1->title , t2->title) == 0) {
     if (t1 == list->cursor) {
       if (t1->next != NULL) {
       list->cursor = list->cursor->next;
       } else if (t1->prev != NULL) {
         list->cursor = list->cursor->prev;
       }
     }
     if (t1 == list->head) {
       delFirst(list , out);
       break;
     } else if (t1 == list->tail) {
       delLast(list , out);
       break;
     } else {
     tmp1 = t1->prev;
     tmp2 = t1->next;
     tmp1->next = tmp2;
     tmp2->prev = tmp1;
     list->size--;
    free(t1);
    break;
     }
    }
    t1 = t1->next;
  }
    free(t2);
    if (t1 == NULL) {
    fprintf(out , "Error: no song found to delete\n");
     }
  }

void check(struct doubleList *list , char *fileName , FILE *out) {
  struct Node *t1 , *t2;
  t1 = createNode(fileName);
  t2 = list -> head;
  while (t2 != NULL) {
    if (strcmp(t1->title , t2->title) == 0) {
      delSong(list , fileName , out);
      break;
    }
    t2 = t2->next;
  }
      free(t1);
}

void moveNext(struct doubleList *list , struct Node *curr , FILE* out) {
  if (curr == NULL) {
    fprintf(out , "Error: no track playing\n");
  } else if (list->cursor->next != NULL) {
  list->cursor = list->cursor->next;
  }
}

void movePrev(struct doubleList *list , struct Node *curr , FILE* out) {
  if (curr == NULL) {
    fprintf(out , "Error: no track playing\n");
  } else if (curr->prev != NULL) {
  list->cursor = curr->prev;
  }
}

void showFirst(struct Node *head , struct doubleList *list , FILE* out) {
  if (list->size == 0) {
  fprintf(out , "Error: show empty playlist\n");
  } else {
  fprintf(out , "Title: %s\n" , head->title);
  fprintf(out , "Artist: %s\n" , head->artist);
  fprintf(out , "Album: %s\n" , head->album);
  fprintf(out , "Year: %.4s\n" , head->year);
  }
}

void showLast(struct Node *tail , struct doubleList *list , FILE* out) {
  if (list->size == 0) {
  fprintf(out , "Error: show empty playlist\n");
  } else {
  fprintf(out , "Title: %s\n" , tail->title);
  fprintf(out , "Artist: %s\n" , tail->artist);
  fprintf(out , "Album: %s\n" , tail->album);
  fprintf(out , "Year: %.4s\n" , tail->year);
  }
}

void showCurr(struct Node *curr , struct doubleList *list , FILE* out) {
  if (list->size == 0) {
  fprintf(out , "Error: show empty playlist\n");
  } else {
  fprintf(out , "Title: %s\n" , curr->title);
  fprintf(out , "Artist: %s\n" , curr->artist);
  fprintf(out , "Album: %s\n" , curr->album);
  fprintf(out , "Year: %.4s\n" , curr->year);
  }
}

void showPlaylist(struct doubleList *list , FILE* out) {
  struct Node *curr;
  curr = list->head;
  if (list->size == 0) {
    fprintf(out , "[]\n");
  } else {
  fprintf(out , "[");
  while (curr->next != NULL) {
  fprintf(out , "%s; " , curr->title);
  curr = curr->next;
  }
  fprintf(out , "%s" , curr->title);
  fprintf(out , "]\n");
  }
}

void freeList(struct doubleList **pp_list){
  struct doubleList *list = *pp_list;
  if (list->size == 0) {
  free(list);
  list = NULL;
  } else {
  struct Node *tmp;
  struct Node *it;
  list->head->prev = NULL;
  list->tail->next = NULL;
  it = list->head;
  while (it != NULL) {
    tmp = it;
    it = it->next;
    free(tmp);
    }
  free(list);
  list = NULL;
  }
}
