cat ./primesieve.in | ./primesieve > temp; diff temp primesieve.ans -y; rm ./temp;