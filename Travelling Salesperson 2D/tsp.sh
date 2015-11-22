#cat ./tsp.in | ./tsp # > temp; diff temp tsp.ans -y; rm ./temp;
#cat ./tsp-perturb.in | ./tsp
cat ./tsp-large.in | ./tsp