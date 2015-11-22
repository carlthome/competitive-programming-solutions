cat ./listgame.1.in | ./listgame > temp; diff temp listgame.1.ans -y; rm ./temp;
cat ./listgame.2.in | ./listgame > temp; diff temp listgame.2.ans -y; rm ./temp;
