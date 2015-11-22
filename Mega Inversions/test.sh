cat ./megainversions.1.in | ./megainversions > temp; diff temp megainversions.1.ans -y; rm ./temp;
cat ./megainversions.2.in | ./megainversions > temp; diff temp megainversions.2.ans -y; rm ./temp;
