cat ./setstack.in | ./setstack > temp; diff temp setstack.ans -y; rm ./temp;
