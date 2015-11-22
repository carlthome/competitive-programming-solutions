rm player2server server2player
mkfifo player2server server2player
javac *.java
java Main server < player2server | java Main verbose > player2server
rm player2server server2player
