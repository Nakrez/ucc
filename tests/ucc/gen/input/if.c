int main(void)
{
    int a = 3;
    int b = 0;

    if (a < 4)
        b = 4;
    else if (a > 4)
    {
        if (a > 10)
            b = 10;
        else if (a < 10)
            b = 5;
        else b = 3;
    }
    else
    {
        if (b == 3)
            b = 1;
    }
}
