

typedef struct
{
    int a;
    int b : 9;
    
} typea;


typedef union
{
    typea b;
    typea c;
    
} typeu;
int main(void)
{
    typea a;
    typeu b;
    a.b = 0;
    a.a = 4;
    b.b = a;
    return b.b.a;
}
