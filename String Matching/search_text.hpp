// Author: Carl Thomé

#ifndef SEARCH_TEXT_H
#define SEARCH_TEXT_H
#include <vector>
#include <string>

std::vector<size_t> search_text(std::string needle, std::string haystack) {
  using namespace std;

  vector<long> T(needle.size() + 1, -1);
	vector<size_t> positions;

  if(needle.size() == 0) 
    return {};

	for(size_t i = 1; i <= needle.size(); ++i)	{
		long position = T[i-1];
		while(position != -1 && needle[position] != needle[i-1])
      position = T[position];
		T[i] = ++position;
	}
 
	long sp = 0, kp = 0;
	while(sp < haystack.size()) {
  
		while(kp != -1 && (kp == needle.size() || needle[kp] != haystack[sp])) 
      kp = T[kp];

		++kp;
		++sp;
    
		if(kp == needle.size())
      positions.push_back(sp - needle.size());
	}
 
	return positions;
}

#endif /* SEARCH_TEXT_H */
