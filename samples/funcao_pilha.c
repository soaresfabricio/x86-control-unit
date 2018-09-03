int foo(int x, int y)
{
  return x + y;
}

void dobra(int *z)
{
  *z = *z * 2;
}

int main()
{
  int a, b, c;
  a = 7;
  b = 15;
  c = foo(a , 31); // 38
  dobra(&b); // 30
  
  return c; 
}