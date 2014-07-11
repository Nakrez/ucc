struct test
{
    int a;
    int b;
};

int main(void)
{
    struct test a[2];

    a[1].a = 3;

    return a[0].b;
}
