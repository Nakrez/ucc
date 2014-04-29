typedef int *(*fun_type)(int *);

int *b(int *a)
{
    return a;
}

int main(void)
{
    fun_type f;
    int a = 0;

    f = &b;

    return *(*f)(&a);
}
