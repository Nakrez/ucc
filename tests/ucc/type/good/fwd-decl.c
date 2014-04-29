struct a;

struct b
{
    struct a* b;
};

struct a
{
    int a;
};

int main(void)
{
    struct b a;
    int b = 0;

    a.b->a = b;
    return a.b->a;
}
