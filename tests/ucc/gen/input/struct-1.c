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
    struct b a;

    a.a.a = 0;
    a.a.b = 2;
    a.b = 4;

    return a.a.a + a.a.b + a.b;
}
