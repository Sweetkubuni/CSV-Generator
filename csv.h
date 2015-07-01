/*
*
*
*	@file: csv.h
*
*	@author: Justin B
*
*	@purpose: The purpose of this code is to generate or manage CSV files.
*/

#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <list>
#include <string>

class node
{
private:
	std::vector<node *> childern;
protected:
	node () { }
public:
	void add( node * n ) { childern.push_back( n ); }
	std::vector<node *>::iterator & begin() { return childen.begin(); }
	std::vector<node *>::iterator & end() { return childern.end(); }
	virtual ~node() { }
};

template< typename type>
class typenode : public node
{
private:
	type data;
public:
	typenode( type t ) { data = t; }

	type & get() { return data; }
};



typedef typenode<std::string> strnode;
typedef typenode<int> intnode;
typedef typenode<double> doublenode;


enum what_type
{
    is_str,
    is_int,
    is_double
};

class row_t
{
     std::vector<what_type> types;
     public:
         void append(strnode * n ) { types.push_back(is_str); add(n); }
         void append(intnode * n ) { types.push_back(is_int); add(n); }
         void append(doublenode * n ) { types.push_back(is_double); add(n); }
        std::vector<what_type>::iterator & get_types() { return types.begin(); }
};

typedef typenode<row_t> row;

class CSV
{
	std::vector<row *> table;
	bool can_write;
	unsigned int which_row;
public:

    CSV() { which_row = 0; can_write = false; }

	void write(std::ostream & out )
	{
	    for(std::vector<row *>::iterator it = table.begin(); it != table.end(); it++)
        {
            for ( std::vector<node *>::iterator jt = it->begin(), std::vector<what_type>::iterator types = jt->get_types(); jt != it->end(); jt++ , types++ )
            {
                switch(*types)
                {
                case is_str:
                    out << dynamic_cast<strnode>(*jt).get();
                break;
                case is_int:
                    out << dynamic_cast<intnode>(*jt).get();
                break;
                case is_double:
                    out << dynamic_cast<doublenode>(*jt).get();
                break;
                }
                out << ',';
            }
            out<< '\n';
        }
	}

	//void read(std::istream & in); will work on later



    bool set_row(unsigned int r)
    {
        which_row = r;

        if( r < table.size() )
        {
            can_write = true;
        }
        else
        {
            can_write = false;
        }
    }

    void create_row()
    {
        table.push_back( new row );
    }
	bool append( const std::string & s )
	{
        if(can_write)
        {
            table[ which_row ]->append( new strnode(s));
        }
	}
	bool append( int i )
	{
        if(can_write)
        {
            table[ which_row ]->append( new intnode(i));
        }
	}
	bool append( double d )
	{
        if(can_write)
        {
            table[ which_row ]->append( new doublenode(d));
        }
	}

	unsigned int NoRows()
	{
        return table.size();
    }
};

#endif // CSV_H
