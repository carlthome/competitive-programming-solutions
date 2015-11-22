cat ./equationsolver.in | ./equationsolver > temp; diff temp equationsolver.ans -y; rm ./temp;
