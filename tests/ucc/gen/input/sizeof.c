struct test
{
    int a;
    int b;
};

int main(void)
{
    struct test b;
    int a = sizeof (b) + sizeof (char);
    a = a+ sizeof (int[3]);

    return a;
}
