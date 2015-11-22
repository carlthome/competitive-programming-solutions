cat ./pet.1.in | ./pet > temp; diff temp pet.1.ans -y; rm ./temp;
cat ./pet.2.in | ./pet > temp; diff temp pet.2.ans -y; rm ./temp;