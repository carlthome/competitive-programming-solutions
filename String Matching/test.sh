cat ./stringmatching.in | ./stringmatching > temp; diff temp stringmatching.ans -y; rm ./temp;