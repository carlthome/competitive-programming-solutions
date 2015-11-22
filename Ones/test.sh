cat ./ones.in | ./ones > temp; diff temp ones.ans -y; rm ./temp;
