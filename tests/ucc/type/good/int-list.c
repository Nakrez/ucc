#include "int-list.h"

int_list_t *new_int_list(int elem)
{
    int_list_t *l = malloc(sizeof (int_list_t));

    if (l == NULL)
        return NULL;

    l->elem = elem;
    l->next = NULL;
    l->prev = NULL;

    return l;
}

int_list_t *add_int_list(int_list_t *l, int elem)
{
    int_list_t *new = NULL;

    new = new_int_list(elem);

    if (!l)
        return new;

    if (!new)
        return NULL;

    new->elem = elem;
    new->next = l;

    l->prev = new;

    return new;
}

int_list_t *delete_int_list(int_list_t *l, int elem)
{
    int_list_t *tmp = l;
    int_list_t *next = NULL;

    while (tmp)
    {
        next = tmp->next;

        if (tmp->elem == elem)
        {
            if (tmp->prev == NULL)
                l = l->next;
            else
                tmp->prev->next = tmp->next;

            if (tmp->next != NULL)
                tmp->next->prev = tmp->prev;

            free(tmp);

            return l;
        }

        tmp = next;
    }

    return l;
}

void destroy_int_list(int_list_t *l)
{
    int_list_t *tmp;

    while (l)
    {
        tmp = l->next;

        free(l);

        l = tmp;
    }

    return;
}

void dump_int_list(int_list_t *l)
{
    int_list_t *tmp = l;

    while (tmp)
    {
        printf("%i (@: %p, prev: %p, next: %p)\n", tmp->elem, tmp,
               tmp->prev, tmp->next);

        tmp = tmp->next;
    }
}

int main(void)
{
    int_list_t *l = NULL;

    l = add_int_list(l, 4);
    l = add_int_list(l, 4);
    l = add_int_list(l, 4);
    l = add_int_list(l, 3);
    l = add_int_list(l, 2);
    l = add_int_list(l, 1);

    dump_int_list(l);

    l = delete_int_list(l, 3);
    l = delete_int_list(l, 4);
    l = delete_int_list(l, 1);

    printf("---\n");

    dump_int_list(l);

    destroy_int_list(l);
}
