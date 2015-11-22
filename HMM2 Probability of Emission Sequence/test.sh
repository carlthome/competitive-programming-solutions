cat ./hmm2.in | ./hmm2 > temp; diff temp hmm2.ans -y; rm ./temp;
