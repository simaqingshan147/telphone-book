#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAXPERSON 100
#define MAXSIZE 21
#define TELSIZE 12
struct item {
	char name[MAXSIZE];
	char telnumber[TELSIZE];
};
struct item* insert(struct item*N,int x);
struct item* init(void);
char* s_gets(char*, int);
int get(struct item*);
int delete (struct item*,int x);
void print(struct item*, int x);
int revise(struct item*, int x);
struct item* checkbyloaction(struct item*, int x);
struct item* checkname(struct item*);
struct item* checktelnum(struct item*);
void print(struct item*);
int menu(struct item*);
void checknum(int);