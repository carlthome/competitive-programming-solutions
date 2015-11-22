cat ./fenwick1.in | ./fenwick > temp; diff temp fenwick1.ans -y; rm ./temp;
cat ./fenwick2.in | ./fenwick > temp; diff temp fenwick2.ans -y; rm ./temp;
cat ./fenwick3.in | ./fenwick > temp; diff temp fenwick3.ans -y; rm ./temp;
