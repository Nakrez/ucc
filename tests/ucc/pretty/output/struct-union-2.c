int main(void)
{
    struct bar
    {
        int a;
        int b : 9;
        
    };
    struct bar a;
    a.b = 0;
    a.a = 4;
    return a.a;
}
