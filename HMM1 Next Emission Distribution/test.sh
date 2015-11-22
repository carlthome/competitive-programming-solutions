cat ./hmm1.in | ./hmm1 > temp; diff temp hmm1.ans -y; rm ./temp;
