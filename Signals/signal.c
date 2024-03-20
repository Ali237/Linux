#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int i;

void quit(int code)
{
   fprintf(stderr, "\nlnterrupt(code=%d,i=%d)\n", code, i);
}

int main(void)
{

   signal(SIGQUIT, quit);

   for (i = 0; i < 9e7; i++)
   {

      if (i % 10000 == 0)
      {
         putc('.', stdout);
         putc('\n', stdout);
         sleep(1);
      }
   }
   return (0);
}
