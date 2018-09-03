
int main()
{
  int a, b, i;
  int c[3] = { 10, 11, 12 };
  a = 197;

  if(a < 100)
    b = 134;
  else
    b = 26; 

  for(i = 0; i < 3; i++)
    c[i] = a + b; // DEVE SER 197 + 26 = 223

  a = c[2] + 18; // DEVE SER 223 + 18 = 241
  return b;
}