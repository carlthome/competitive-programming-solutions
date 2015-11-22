cat ./phone.in | ./phonelist > temp; diff temp phone.ans -y; rm ./temp;
