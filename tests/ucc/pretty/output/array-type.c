typedef int b[2];
typedef int * c[];
typedef int *const *restrict * d[10];
int fn(void)
{
    int a[2];
    return a[0];
}
int main(void)
{
    return 0;
}
