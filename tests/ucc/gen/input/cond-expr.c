int g(void)
{
    return 2;
}

int f(void)
{
    return 1;
}

int main(void)
{
    int a = 0;

    a = (a ? f() + 4 : g() + 3);

    return !a;
}
