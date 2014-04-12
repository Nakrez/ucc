int main(void)
{
    int c = 0;

    typedef union a b;

    union a
    {
        int a;
    };

    b a;

    return 0;
}
