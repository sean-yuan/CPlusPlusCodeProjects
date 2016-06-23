#include <iostream>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QInputDialog>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
#include <QString>
#include "multiwin.h"
#include "searcheng.h"
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "md.h"

using namespace std;


int main(int argc, char* argv[])
{
    if(argc < 2) {
    std::string word = "config.txt";
    QApplication app(argc, argv);
    Multiwin *Mo = new Multiwin(word);
    Mo->show();

    return app.exec();
    return 0;
        
    }
    else{

    /****************   Add code to ***************************/
    /* Initialize your search engine and parse all the pages */
    std::string word = argv[1];
    QApplication app(argc, argv);
    Multiwin *Mo = new Multiwin(word);
    Mo->show();

    return app.exec();
    return 0;
    }
}
