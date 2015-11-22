cat ./rafting.in | ./rafting > temp; diff temp rafting.ans -y; rm ./temp;
