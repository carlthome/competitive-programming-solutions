cat ./ladder.1.in | ./ladder > temp; diff temp ladder.1.ans -y; rm ./temp;
cat ./ladder.2.in | ./ladder > temp; diff temp ladder.2.ans -y; rm ./temp;