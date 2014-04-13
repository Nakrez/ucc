typedef struct a
{
    int a;
    int b : 9;
} type;

typedef union b
{
    struct a b;
    struct a c;
} typeu;

int main(void)
{
    type a;
    typeu b;

    a.b = 0;
    a.a = 4;

    b.b = a;

    return b.b.a;
}
