typedef int (*fun_type)(int, int);

int b(int a)
{
    return 0;
}

int main(void)
{
    fun_type f;

    f = &b;

    return (*f)(0, 0);
}
