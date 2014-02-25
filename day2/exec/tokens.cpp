#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main()
{
   using namespace std;
   using namespace boost;
   string s = "This is,  a test";
   
   boost::char_separator<char> sep(" ");

   tokenizer< boost::char_separator<char> > tok(s, sep);

   for(tokenizer<boost::char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
   {
       cout << *beg << "\n";
   }

   for ( auto range : tok)
   {
    cout << range << endl;
   }
}