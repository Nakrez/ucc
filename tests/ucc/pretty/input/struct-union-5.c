int main(void)
{
    struct
    {
        int a;
        int b;
    } a;

    a.b = 0;
    a.a = 4;

    return a.b;
}
