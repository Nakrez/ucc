int main(void)
{
    int a = 0;
    int *b;

    b = &a;
    *b = a;
    *b = *b + a;

    return 0;
}
