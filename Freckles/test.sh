cat ./freckles.in | ./freckles > temp; diff temp freckles.ans -y; rm ./temp;
cat ./freckles.2.in | ./freckles > temp; diff temp freckles.2.ans -y; rm ./temp;
