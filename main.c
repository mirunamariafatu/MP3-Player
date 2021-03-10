// "Copyright 2020 Fatu Miruna"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "./tema1.h"

int main(int argc , char *argv[]) {
  if (argc != 3) {
		printf("Nu e ok\n");
		return -1;
	}
  struct Node *suport = NULL;
  char v[100] = {0};
  int n , i;
  char *comanda = NULL;
  char *nume = NULL;
  char input_filename[20];
  char output_filename[20];
  char *rest;
  int lg1 = strlen(argv[1]);
  int lg2 = strlen(argv[2]);
  snprintf(input_filename , lg1+1 , "%s" , argv[1]);
  snprintf(output_filename , lg2+1 , "%s\n" , argv[2]);
  struct doubleList *list;
  list = malloc(sizeof(struct doubleList));
  init_list(list);
  FILE *in;
  if ((in = fopen(input_filename, "rb")) == NULL) {
        fprintf(stderr , "Can't open %s" , input_filename);
        return -1;
    }
  FILE *out;
  if ((out = fopen(output_filename, "wt")) == NULL) {
        fprintf(stderr , "Can't open %s" , output_filename);
        return -1;
    }
  fscanf(in , "%d" , &n);
  for (i = 0; i < n + 1; i++) {
  fgets(v , 99 , in);
  rest = NULL;
  v[strlen(v) - 1] = 0;
  comanda = strtok_r(v , " ", &rest);
  nume = strtok_r(NULL , "\n", &rest);
  if (comanda != NULL) {
    if (!strcmp("ADD_FIRST" , comanda)) {
      suport = createNode(nume);
      check(list , nume , out);
      addFirst(list , suport);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("ADD_LAST" , comanda)) {
      suport = createNode(nume);
      check(list , nume , out);
      addLast(list , suport);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("ADD_AFTER", comanda)) {
      suport = createNode(nume);
      if (list->size == 0){
        free(suport);
      } else if (strcmp(list->cursor->title , suport->title) == 0) {
        free(suport);
      } else {
     check(list , nume , out);
     addAfter(list , list->cursor , suport);
       }
      }
    }
  if (comanda != NULL) {
    if (!strcmp("DEL_FIRST", comanda)) {
      delFirst(list , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("DEL_LAST" , comanda)) {
      delLast(list , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("DEL_SONG" , comanda)) {
      delSong(list , nume , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("DEL_CURR" , comanda)) {
     delCurr(list , list->cursor , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("MOVE_NEXT" , comanda)) {
      moveNext(list , list->cursor , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("MOVE_PREV" , comanda)) {
      movePrev(list , list->cursor , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("SHOW_FIRST" , comanda)) {
      showFirst(list->head , list , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("SHOW_LAST" , comanda)) {
      showLast(list->tail , list , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("SHOW_CURR" , comanda)) {
      showCurr(list->cursor , list , out);
      }
    }
  if (comanda != NULL) {
    if (!strcmp("SHOW_PLAYLIST" , comanda)) {
      showPlaylist(list , out);
      }
    }
  }
    fclose(in);
    fclose(out);
    freeList(&list);
    return 0;
}
