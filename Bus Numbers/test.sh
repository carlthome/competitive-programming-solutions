cat ./test.indata | ./busnumbers > temp; diff temp test.utdata -y; rm ./temp;