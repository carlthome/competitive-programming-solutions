cat ./modulararithmetic.in | ./modulararithmetic > temp; diff temp modulararithmetic.ans -y; rm ./temp;
