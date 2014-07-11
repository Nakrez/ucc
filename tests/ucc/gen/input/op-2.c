int main(void)
{
    int a = 0;
    unsigned int b = 0;

    a <<= 1;
    a >>= 2;
    a |= 3;
    a &= 4;

    b >>= 1;
    b <<= 2;

    return a;
}
