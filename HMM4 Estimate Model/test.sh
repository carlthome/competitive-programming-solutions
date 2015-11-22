cat ./hmm4.in | ./hmm4 > temp; diff temp hmm4.ans -y; rm ./temp;
