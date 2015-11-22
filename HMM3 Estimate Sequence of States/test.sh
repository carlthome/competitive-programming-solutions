cat ./hmm3.in | ./hmm3 > temp; diff temp hmm3.ans -y; rm ./temp;
