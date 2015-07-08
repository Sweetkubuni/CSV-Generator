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
	
	void write( std::ostream & out );
	
	void read( std::string & var   );
};

class row
{
private:
	std::list<std::unique_ptr<Item>> Items;
public:
	row();
	std::list<std::unique_ptr<Item>>::iterator Begin();
	std::list<std::unique_ptr<Item>>::iterator End();
	void append(Item * item);
	unsigned int	NoItems();
};

template<typename d>
struct Specific_Item : public Item
{

	d data;
	Specific_Item( d ndata ):data(ndata) {  }
};

typedef Specific_Item<int> int_Item;
typedef Specific_Item<double> double_Item;
typedef Specific_Item<std::string> string_Item;

class CSV
{
private:
	std::vector< row > rows;
public:
	CVS();
	void	write( std::ostream & out );
	void	read(  std::istream & in );
	bool	append(unsigned int row, int);
	bool	append(unsigned int row, double);
	bool	append(unsigned int row, std::string);
};
#endif // CSV_H
