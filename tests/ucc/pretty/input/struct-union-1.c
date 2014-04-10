int main(void)
{
    struct bar
    {
        int a : 8;
        char b;
    };

    union foo
    {
        char **test;
        int a;
    };

    struct bar a;
    union foo b;

    a.b = 0;
    a.a = 4;

    b.test = &a;

    return b.a;
}
