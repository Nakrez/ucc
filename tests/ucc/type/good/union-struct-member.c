struct a
{
    int b;
};

union b
{
    int a;
};

int main(void)
{
    struct a *a;
    union b *b;

    a->b = 0;
    b->a = 0;

    return 0;
}
