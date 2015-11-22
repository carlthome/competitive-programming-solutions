cat ./polymul1.in | ./polymul1 > temp; diff temp polymul1.ans -y; rm ./temp;
