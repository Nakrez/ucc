int main(void)
{
    int a = 0;
    unsigned int b = 0;

    a = a << 1;
    a = a >> 2;
    a = a | 3;
    a = a & 4;

    b = b >> 1;
    b = b << 2;

    return a;
}
