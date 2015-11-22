cat ./test1.indata | ./cheergame > temp; diff temp test1.utdata -y; rm ./temp;
cat ./test2.indata | ./cheergame > temp; diff temp test2.utdata -y; rm ./temp;
