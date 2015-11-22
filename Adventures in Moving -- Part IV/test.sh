cat ./adventuremoving4.in | ./adventuremoving4 > temp; diff temp adventuremoving4.ans -y; rm ./temp;
