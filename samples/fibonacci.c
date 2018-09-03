int fib(int n)
{
  if(n < 2)
    return 1;

  return fib(n - 1) + fib(n - 2);
} 

int main()
{
  int a, b, c;

  a = 5;
  b = fib(a); // 8
  c = fib(1); // 1

  return b + c + a; // 5 + 8 + 1 = 14
}