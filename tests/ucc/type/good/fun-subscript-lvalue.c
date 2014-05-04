void *malloc(unsigned long t);
int *f(int a)
{
    int *b = malloc(a * 4);

    return b;
}

int main(void)
{
    f(3)[2] = 1;

    return 0;
}
