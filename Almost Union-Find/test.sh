#cat ./almostunionfind.in | ./almostunionfind > temp; diff temp almostunionfind.ans -y; rm ./temp;
cat ./asmall.in | ./almostunionfind > temp; diff temp asmall.ans -y; rm ./temp;
