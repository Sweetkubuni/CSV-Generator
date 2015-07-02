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

#include <fstream>
#include <vector>
#include <list>
#include <string>


enum what_type
{
    is_str,
    is_int,
    is_double
};

class node
{
private:
	std::list<node *> childern;
	std::list<what_type> types;
protected:
	node () { }
public:
	void add_data( node * n )   { childern.push_back( n ); }
	void add_type(what_type wt) { types.push_back(wt); }
	std::list<node *>::iterator  begin() { std::list<node *>::iterator first = childern.begin(); return first; }
	//std::list<node *>::iterator   end() { return childern.end(); }
	std::list<what_type>::iterator  get_types() { std::list<what_type>::iterator first = types.begin(); return first; }
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



/*
    This is our rootnode
*/
class row_t
{

};

typedef typenode<row_t> row;

class CSV
{
	std::vector<row *> table;
	bool can_write;
	unsigned int which_row;
	std::list<what_type> types;
public:

    CSV() { which_row = 0; can_write = false; }

	void write(std::ofstream & out )
	{
	    for(std::vector<row *>::iterator it = table.begin(); it != table.end(); it++)
        {
            for ( std::list<node *>::iterator jt = it->begin(), std::list<what_type>::iterator types = jt->get_types(); jt != it->end(); jt++ , types++ )
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
            table[ which_row ]->add_data( new strnode(s));
            table[ which_row ]->add_type( is_str );
        }
	}
	bool append( int i )
	{
        if(can_write)
        {
            table[ which_row ]->add_data( new intnode(i));
            table[ which_row ]->add_type( is_int );
        }
	}
	bool append( double d )
	{
        if(can_write)
        {
            table[ which_row ]->add_data( new doublenode(d));
            table[ which_row ]->add_type( is_double );
        }
	}

	unsigned int NoRows()
	{
        return table.size();
    }
};

#endif // CSV_H
