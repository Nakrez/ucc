int main(void)
{
    int i = 0;

    for (; i != 0;)
    {
        ++i;
    }

    for (; i != 10; ++i)
        ;

    for (; i != 3; ++i)
        i = 0;

    for (i = 0; i != 5; ++i)
        ;

    return 0;
}
