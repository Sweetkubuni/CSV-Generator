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
#include <string>
#include <memory>

struct Item
{
public:
	Item() { }

	virtual void write( std::ostream & out )=0;
};

class row
{
private:
	std::list<std::unique_ptr<Item>> Items;
public:
	row() { /*empty */ }
	void append( Item * item ) ;
	std::list<std::unique_ptr<Item>>::iterator Begin();
	std::list<std::unique_ptr<Item>>::iterator End();
	unsigned int	NoItems();
};

template<typename d>
struct Specific_Item : public Item
{

	d data;
	Specific_Item( d ndata ):data(ndata) {  }

	void write( std::ostream & out ) { out << ndata; }
};

typedef Specific_Item<int> int_Item;
typedef Specific_Item<double> double_Item;
typedef Specific_Item<std::string> string_Item;

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
