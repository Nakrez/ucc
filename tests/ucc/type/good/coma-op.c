int main(void)
{
    int *a;
    float b;
    int c;

    a = (b = 2.0f, ++b, c = 0, &c);

    return 0;
}
