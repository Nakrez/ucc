struct a
{
    int a;
    char b;
};

struct b
{
    struct a a;
    int b;
};

int main(void)
{
    struct b *a;

    a->a.a = 0;

    return a->a.a;
}
