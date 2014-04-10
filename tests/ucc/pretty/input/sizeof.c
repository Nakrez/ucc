int main(void)
{
    int a = sizeof (int) + sizeof 0x10 + sizeof '\0';
    return a;
}
