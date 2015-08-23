
#include "csv.h"
#include <utility>
#include <string>

template<typename d>
struct Specific_Item : public Item
{

	d data;
	Specific_Item( d ndata ): data(ndata) {  }

	void write( std::stringstream & out ) { out << data; }
};

typedef Specific_Item<int> int_Item;
typedef Specific_Item<double> double_Item;
typedef Specific_Item<std::string> string_Item;


void row::write( std::ostream & out )
{
    std::stringstream ss;
    for(auto && item : Items)
    {
        item->write(ss);
        ss << ',';
    }
    ss <<'\n';
    out << ss.str();
}

void row::append( Item * item )
{
    std::unique_ptr<Item> item_ptr(item);
    Items.push_back( std::move(item_ptr) );
}

void CSV::create_row()
{
    rows.push_back( row() );
}

bool CSV::append(unsigned int sel, int data)
{
    if( sel < rows.size() )
    {
        rows[sel].append(new int_Item(data));
        return true;
    }
    return false;
}

bool CSV::append(unsigned int sel, double data)
{
    if( sel < rows.size() )
    {
        rows[sel].append(new double_Item(data));
        return true;
    }
    return false;
}

bool CSV::append(unsigned int sel, std::string data)
{
    if( sel < rows.size() )
    {
        rows[sel].append(new string_Item(data));
        return true;
    }
    return false;
}

void CSV::write( std::ostream & out )
{
  for( auto & r : rows)
  {
    r.write(out);
  }
}
