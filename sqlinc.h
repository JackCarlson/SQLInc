#ifndef SQL_INC_H
#define SQL_INC_H

#include <iostream>
#include <string>

// include mySQL
#include "/sw/include/mysql/mysql.h"
using namespace std;


/*
*
*	SQL Connection Object
*
*/
class sqlinc
{
public:
	sqlinc(string in_host, string in_user, string in_pass, string in_db);

	~sqlinc();

	string escape_string(string in_string);

	string query(string in_string);

	bool fetch_row();

	unsigned long long num_rows();

	string error();

	unsigned errno();

	void check_error();

	MYSQL_ROW getRow() {return row;}
	
private:

	void free_result();
	
	void use_result();

	MYSQL * mysql;
	MYSQL_RES * result;
	MYSQL_ROW row;
};

#endif