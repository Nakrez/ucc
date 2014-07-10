struct a
{
    int a;
    char b;
};

int main(void)
{
    struct a b;

    b.a = 0;
    b.b = 0;

    return b.b + b.a;
}
