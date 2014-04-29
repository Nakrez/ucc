typedef struct a
{
    int a;
} my_struct;

typedef my_struct struct_a;
typedef struct a struct_a_alias;

int main(void)
{
    struct_a b;
    struct_a_alias c;

    c = b;

    return 0;
}
