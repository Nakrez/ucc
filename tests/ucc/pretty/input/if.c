int main(void)
{
    int var = 0;

    if (1)
        ++var;

    if (1)
    {
        ++var;
    }

    if (1)
        ++var;
    else
        --var;

    if (1)
    {
        ++var;
    }
    else if (2)
    {
        ++var;
    }
    else
    {
        --var;
    }

    return 0;
}
