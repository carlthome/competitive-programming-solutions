cat ./moneymatters.1.in | ./moneymatters > temp; diff temp moneymatters.1.ans -y; rm ./temp;
cat ./moneymatters.2.in | ./moneymatters > temp; diff temp moneymatters.2.ans -y; rm ./temp;
cat ./moneymatters.3.in | ./moneymatters > temp; diff temp moneymatters.3.ans -y; rm ./temp;
