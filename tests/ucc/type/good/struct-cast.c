struct a
{
    int a;
};

struct b
{
    int b;
};

int main(void)
{
    struct a a;
    struct b *b;

    a.a = 1;

    b = (struct b*)&a;

    return b->b;
}
