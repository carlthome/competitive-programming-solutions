cat ./unionfind1.in | ./unionfind > temp; diff temp unionfind1.ans -y; rm ./temp;
cat ./unionfind2.in | ./unionfind > temp; diff temp unionfind2.ans -y; rm ./temp;
