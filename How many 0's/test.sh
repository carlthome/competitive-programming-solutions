cat ./howmanyzeros.in | ./howmanyzeros > temp; diff temp howmanyzeros.ans -y; rm ./temp;
