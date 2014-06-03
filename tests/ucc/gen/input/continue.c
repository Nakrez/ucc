int main(void)
{
    int a = 0;

    while (a < 10)
    {
        if (a == 5)
            a = 6;
        else if (a == 7)
            a = 8;
        else if (a == 9)
            continue;

        a = a + 1;
    }
}
