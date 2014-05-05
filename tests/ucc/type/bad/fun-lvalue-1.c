struct a
{
    int a;
};

struct a f(int a)
{
    struct a b;

    b.a = a;

    return b;
}

int main(void)
{
    f(0).a = 1;

    return 0;
}
