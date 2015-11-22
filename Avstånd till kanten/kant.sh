cat ./kant.1.in | ./kant > temp; diff temp kant.1.ans -y; rm ./temp;
cat ./kant.2.in | ./kant > temp; diff temp kant.2.ans -y; rm ./temp;
