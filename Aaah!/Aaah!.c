#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h> 
 
size_t
strlen2(str) const char *str; {
  size_t result = 0;
  uint64_t *i = (uint64_t *)str;

  for (;;) {
    if (!(*i & 0x00000000000000ff)) return result;
    if (!(*i & 0x000000000000ff00)) return result + 1;
    if (!(*i & 0x0000000000ff0000)) return result + 2;
    if (!(*i & 0x00000000ff000000)) return result + 3;
    if (!(*i & 0x000000ff00000000)) return result + 4;
    if (!(*i & 0x0000ff0000000000)) return result + 5;
    if (!(*i & 0x00ff000000000000)) return result + 6;
    if (!(*i & 0xff00000000000000)) return result + 7;
    result += 8;
    i++;
  }
}

main()
{
	char s1[1000];
	char s2[1000];
	scanf("%1000s", s1);
	scanf("%1000s", s2);
	
	int l = strlen2(s2);
	
	if (s1[l-1] == 'a' || s1[l-1] == 'h') {
		printf("go");
	} else {
		printf("no");
	}
}