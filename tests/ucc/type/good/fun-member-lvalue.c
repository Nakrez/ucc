void *malloc(unsigned long t);

struct a
{
    int a;
};

struct a *f(void)
{
    struct a *b = malloc(100);

    return b;
}

int main(void)
{
    f()->a = 1;

    return 0;
}
