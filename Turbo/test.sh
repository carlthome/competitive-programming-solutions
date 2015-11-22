cat ./turbo-1.in | ./turbo > temp; diff temp turbo-1.ans -y; rm ./temp;
cat ./turbo-2.in | ./turbo > temp; diff temp turbo-2.ans -y; rm ./temp;
cat ./turbo-3.in | ./turbo > temp; diff temp turbo-3.ans -y; rm ./temp;
