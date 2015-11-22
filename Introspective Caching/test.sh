cat ./caching.1.in | ./caching > temp; diff temp caching.1.ans -y; rm ./temp;
cat ./caching.2.in | ./caching > temp; diff temp caching.2.ans -y; rm ./temp;
cat ./caching.3.in | ./caching > temp; diff temp caching.3.ans -y; rm ./temp;