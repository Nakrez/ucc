#ifndef TEST_H
# define TEST_H

# define NULL ((void *)0)

typedef unsigned long size_t;

void *malloc(size_t);
void free(void *);
int printf(const char *, ...);

typedef struct __list
{
    int elem;
    struct __list *next;
    struct __list *prev;
} int_list_t;

int_list_t *new_int_list(int elem);
int_list_t *add_int_list(int_list_t *l, int elem);
int_list_t *delete_int_list(int_list_t *l, int elem);
void destroy_int_list(int_list_t *l);
void dump_int_list(int_list_t *l);

#endif /* !TEST_H */
