union a
{
    int a;
    unsigned long long b;
};

int main(void)
{
    union a b;

    b.b = 10;

    return b.a;
}
