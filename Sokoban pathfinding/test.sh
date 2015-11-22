cat ./00_sample.in | ./sokobanpathfinding > temp; diff temp 00_sample.ans -y; rm ./temp;
cat ./01_sample.in | ./sokobanpathfinding > temp; diff temp 01_sample.ans -y; rm ./temp;
cat ./02_sample.in | ./sokobanpathfinding > temp; diff temp 02_sample.ans -y; rm ./temp;
