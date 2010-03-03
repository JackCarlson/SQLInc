   mysql_insert: mysql_insert.o ../sqlinc.o
	g++ -Wall -g -o mysql_insert mysql_insert.o ../sqlinc.o -L/usr/local/mysql/lib -lmysqlclient -lz

    mysql_insert.o: mysql_insert.cpp
	g++ -Wall -g -c mysql_insert.cpp
