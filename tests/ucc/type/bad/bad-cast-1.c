struct test
{
    int a;
    int b;
};

struct test2
{
    int a;
};

int main(void)
{
    struct test2 a;
    struct test *b;

    b = (struct test*)a;

    return b->a;
}
