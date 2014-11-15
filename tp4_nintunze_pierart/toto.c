int main()
{
  int suppr=1;
  char c;
  while (c=getchar())
    {
      if (c=='\n'){
	suppr = !suppr;
	if (suppr)
	  continue;
      }
      putchar(c);
    }
}
