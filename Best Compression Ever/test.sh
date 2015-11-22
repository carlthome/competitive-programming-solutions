cat ./compression-1.in | ./bestcompression > temp; diff temp compression-1.ans -y; rm ./temp;
cat ./compression-2.in | ./bestcompression > temp; diff temp compression-2.ans -y; rm ./temp;
cat ./compression-3.in | ./bestcompression > temp; diff temp compression-3.ans -y; rm ./temp;