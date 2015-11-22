cat ./rationalarithmetic.in | ./rationalarithmetic > temp; diff temp rationalarithmetic.ans -y; rm ./temp;
