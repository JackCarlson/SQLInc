/*
*
*	Table used in this example program:
*
*	DESCRIBE test_table;
*	+--------------+--------------+------+-----+---------+----------------+
*	| Field        | Type         | Null | Key | Default | Extra          |
*	+--------------+--------------+------+-----+---------+----------------+
*	| id           | int(11)      | NO   | PRI | NULL    | auto_increment |
*	| string_field | varchar(255) | YES  |     | NULL    |                |
*	+--------------+--------------+------+-----+---------+----------------+
*/

#include <iostream>
#include <string>
#include <fstream>
// include the mySQL object
#include "../sqlinc.h"

using namespace std;

int main(int argc, char *argv[])
{
	string query;
	sqlinc mysql_obj("SERVER", "USERNAME", "PASSWORD", "DATABASE");



	// insert a new row into the test table
	string insert_value = mysql_obj.escape_string("New Value of Insertion String");
	query = "INSERT INTO test_table (string_field) VALUES (\"" + insert_value + "\");";
	cout << "Running:\n" << query << "\n..." << endl;
	mysql_obj.query(query);



	// print out all the rows in the test table
	query = "SELECT * FROM test_table;";
	mysql_obj.query(query);
	
	// if an error occurs, display the error and quit the program
	mysql_obj.check_error();
	
	while (mysql_obj.fetch_row())
	{
		cout << "\nid: " << mysql_obj.getRow()[0];
		cout << "\nstring_field: " << mysql_obj.getRow()[1] << endl;
	}



	// done
	cout << "\nfin" << endl;
	return 0;
}