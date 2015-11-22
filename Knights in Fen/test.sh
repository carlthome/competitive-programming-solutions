cat ./knightsfen.in | ./knightsfen > temp; diff temp knightsfen.ans -y; rm ./temp;
