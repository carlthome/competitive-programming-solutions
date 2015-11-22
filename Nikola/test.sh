cat ./nikola-1.in | ./nikola > temp; diff temp nikola-1.ans -y; rm ./temp;
cat ./nikola-2.in | ./nikola > temp; diff temp nikola-2.ans -y; rm ./temp;
