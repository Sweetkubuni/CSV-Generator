
#include "csv.h"

std::list<std::unique_ptr<Item>>::iterator row::Begin()
{
    return Items.begin();
}

std::list<std::unique_ptr<Item>>::iterator row::End()
{
    return Items.end();
}

unsigned int row::NoItems()
{
    return Items.size();
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
    for( auto & row : rows)
    {
        auto row_ptr = row.Begin();
        auto row_end = row.End();
        while( row_ptr != row_end )
        {
            row_ptr->write(out);
            out << ',';
            ++row_ptr;
        }
        out << '\n';
    }
}
