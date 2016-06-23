#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include "myset.h"

class WebPage
{
public:
    WebPage();

    WebPage(std::string filename);

    ~WebPage();

    std::string texter();

    /**
     * Sets the filename/URL of this webpage
     */
    void filename(std::string fname);

    double rank;


    /**
     * Returns the filename/URL of this webpage
     */
    std::string filename() const;

    /**
     * Updates the set containing all unique words in the text
     *  with the contents of the input parameter words
     */
    void all_words(const MySet<std::string>& words);

    void all_out(const MySet<std::string>& links);

    /**
     * Returns all the unique, tokenized words in this webpage
     */
    MySet<std::string> all_words() const;

    /**
     * Adds a webpage that links to this page
     */
    void add_incoming_link(WebPage* wp);

    /**
     * Returns all webpages that link to this page
     */
    MySet<WebPage*> incoming_links() const;

    /**
     * Adds a webpage that this page links to
     */
    void add_outgoing_link(WebPage* wp);

    void add_rank(double r);

    /**
     * Returns all webpages this page links to
     */
    MySet<WebPage*> outgoing_links() const;

    /**
     * Displays the webpage text to the screen
     */
    friend std::ostream & operator<< (std::ostream & os, const WebPage & page);

    /**** Add other desired member functions here *****/
    MySet<std::string> stringer;
    MySet<std::string> linker;
    MySet<WebPage*> webber_in;
    MySet<WebPage*> webber_out;
    std::string name_;
private:

    /**** Add other desired data members here *****/


};
#endif
