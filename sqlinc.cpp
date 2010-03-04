#include "sqlinc.h"

/*
*
*	Implementation of class methods for the sql_connection object, a C++ wrapper for the MYSQL C API
*
*/

sqlinc::sqlinc(string in_host, string in_user, string in_pass, string in_db)
{

	result = NULL;

	if ((mysql = mysql_init(NULL)) == NULL)
	{
		cerr << "Failed to initate MySQL connection." << endl;
		exit(0);
	}

	mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "");
	
	if (!mysql_real_connect(mysql, in_host.c_str(), in_user.c_str(),
							in_pass.c_str(), in_db.c_str(), 0, NULL, 0))
	{
		cerr << "Failed to connect to MySQL: Error: " << mysql_error(mysql) << endl;
		exit(0);
	}
}

sqlinc::~sqlinc()
{
	free_result();
	mysql_close(mysql);
}

string sqlinc::escape_string(string in_string)
{
	// allocate memory to the character string
	char * _cstring = (char*)malloc(in_string.length());
	mysql_real_escape_string(mysql, _cstring, in_string.c_str(), in_string.length());
	in_string = _cstring;
	free(_cstring);
	return in_string;
}

string sqlinc::query(string in_string)
{
	int return_val;
	return_val = mysql_real_query(mysql, in_string.c_str(), (unsigned) in_string.length());

	if (return_val == 0)
	{
		use_result();
		return "All Good";
	}
//	else if (return_val == CR_COMMANDS_OUT_OF_SYNC)
//		return "Commands executed in improper order.";
	else
	{
		use_result();
		return "Unknown Query Error";
	}
}

// private
void sqlinc::free_result()
{
	if (result != NULL)
	{
		mysql_free_result(result);
		result = NULL;
	}
}

// private
void sqlinc::use_result()
{
	free_result();
	result = mysql_use_result(mysql);
}


bool sqlinc::fetch_row()
{
	if ((row = mysql_fetch_row(result)))
	{
		return true; // something in the row
	}
	else
	{
		// end of the array
		free_result();
		return false;
	}
}

unsigned long long sqlinc::num_rows()
{
	return mysql_num_rows(result);
}

string sqlinc::error()
{
	return mysql_error(mysql);
}

unsigned sqlinc::errno()
{
	return mysql_errno(mysql);
}

void sqlinc::check_error()
{
	// if an error occurs, display the error and quit the program
	if (errno())
	{
		cerr << "Error " << errno() << ": " << error() << endl;
		exit(0);
	}
}
