/*
*
*
*	@file: csv.h
*
*	@author: Justin B
*
*	@purpose: The purpose of this code is to generate or manage CSV files.
*   @version: 1.0
*/

#ifndef CSV_H
#define CSV_H

#include <ostream>
#include <vector>
#include <list>
#include <memory>
#include <sstream>
struct Item
{
public:
	Item() { }

	virtual void write( std::stringstream & out )=0;
	//virtual void read(  std::istream & in )=0;
};

class row
{
private:
	std::list<std::unique_ptr<Item>> Items;
public:
	row() { /*empty */ }
	void append( Item * item ) ;
    void write( std::ostream & out );
};



class CSV
{
private:
	std::vector< row > rows;
public:
	CVS() {/*empty */ }
	void	write( std::ostream & out );
	//void	read(  std::istream & in );
	void    create_row();
	bool	append(unsigned int sel, int data);
	bool	append(unsigned int sel, double data);
	bool	append(unsigned int sel, std::string data);
};
#endif // CSV_H
