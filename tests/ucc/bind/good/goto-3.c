int f(void)
{
    return 0;
}

int main(void)
{
loop:
    f();

    goto loop;

    return 0;
}
