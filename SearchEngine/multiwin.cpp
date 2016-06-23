#include <iostream>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QInputDialog>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QButtonGroup>
#include <QCheckBox>
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
#include "mergesort.h"
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "md.h"
#include "ranker.h"
#include "crawler.h"
struct outComp {
    bool operator()(WebPage* lhs, WebPage* rhs) {
        return lhs->linker.size() < rhs->linker.size();
    }
};

struct prComp {
    bool operator()(WebPage* lhs, WebPage* rhs) {
        return lhs->rank < rhs->rank;
    }
};

std::string Multiwin::parse_space(std::string s) {
    std::string newStr;
    for(unsigned int i = 0 ; i < s.length(); i++) {
        if(s[i] != ' ') {
            newStr += s[i];
        }
    }
    return newStr;
}

std::map<std::string, std::string> Multiwin::configer(std::string file1){
    std::ifstream file (file1.c_str());
    if ( !file.is_open() ) {
        std::cout<<"Could not open file\n";
        throw std::exception();
    }
    std::map<std::string, std::string> baggy;
    std::string line;
    std::vector <std::string> storage;
    while ( getline (file,line) ) {
        if (line.find('=') != std::string::npos){
            int i=0;
            while(line[i] != '#'){
                i++;
            }
            line = line.substr(0, i);
            line = parse_space(line);
            int r=0;
            while(line[r] != '='){
                r++;
            }
            std::string key = line.substr(0, r);
            std::string value = line.substr(r+1,line.length());
            baggy.insert (std::pair<std::string, std::string>(key, value) );
        }
    }
    return baggy;
}



Multiwin::Multiwin(string word) : QWidget(NULL) {
    pager = new MD;
    config = word;
    Crawler g;
    g.crawler(word);
    std::map<std::string, std::string> keys = configer(word);
    std::string index = keys.find("OUTPUT_FILE")->second;
    searcher.add_parse_from_index_file(index, pager);
    mainLayout = new QVBoxLayout;
    mainButton = new QPushButton("&Search");
    radio1 = new QCheckBox("AND");
    radio2 = new QCheckBox("OR");
    QPushButton *button1 = new QPushButton("Quit");
    QObject::connect(button1, SIGNAL(clicked()), this, SLOT(close()));

    line = new QLineEdit();
    QButtonGroup * group = new QButtonGroup();
    group->addButton(radio1);
    group->addButton(radio2);
    mainLayout->addWidget(radio1);
    mainLayout->addWidget(radio2);
    radio1->toggle();



    mainLayout->addWidget(line);
    mainLayout->addWidget(mainButton);
    mainLayout->addWidget(button1);
    setLayout(mainLayout);

    and_=1;
    or_=-1;
    file_=-1;
    out_=-1;
    pr_=1;

    otherLayout = new QVBoxLayout;
    otherWin = new QWidget;
    otherButton = new QPushButton("                                             &Close                                             ");
    thirdButton = new QPushButton("blank");
    otherButton->setMinimumWidth(50);
    otherLayout->addWidget(otherButton);
    otherWin->setLayout(otherLayout);

    check22 = new QCheckBox("by Page Rank");
    check1 = new QCheckBox("by Filename");
    check2 = new QCheckBox("by outgoing links");
    check3 = new QCheckBox("by incoming links");
    QButtonGroup * group2 = new QButtonGroup();
    group2->addButton(check22);
    group2->addButton(check1);
    group2->addButton(check2);
    group2->addButton(check3);
    otherLayout->addWidget(check22);
    otherLayout->addWidget(check1);
    otherLayout->addWidget(check2);
    otherLayout->addWidget(check3);
    check22->toggle();
    QObject::connect(check1, SIGNAL(stateChanged(int)), this, SLOT(sortfile()));
    QObject::connect(check2, SIGNAL(stateChanged(int)), this, SLOT(sortout()));
    QObject::connect(check22, SIGNAL(stateChanged(int)), this, SLOT(sortpr()));

    QObject::connect(mainButton, SIGNAL(clicked()), this, SLOT(mainButtonClicked()));
    QObject::connect(mainButton, SIGNAL(clicked()), line, SLOT(clear()));

    QObject::connect(otherButton, SIGNAL(clicked()), this, SLOT(otherButtonClicked()));
    QObject::connect(otherButton, SIGNAL(clicked()), line, SLOT(clear()));

    QObject::connect(line, SIGNAL(returnPressed()), this, SLOT(mainButtonClicked()));

    QObject::connect(radio1, SIGNAL(stateChanged(int)), this, SLOT(ander()));
    QObject::connect(radio2, SIGNAL(stateChanged(int)), this, SLOT(order()));


    thirdLayout = new QVBoxLayout;
    thirdWin = new QWidget;
    text = new QPlainTextEdit;

    thirdWin->setLayout(thirdLayout);
    listWidgetout = new QListWidget(thirdWin);
    listWidget = new QListWidget(thirdWin);
    webButton = new QPushButton("&Close");
    thirdLayout->addWidget(webButton);
    QObject::connect(webButton, SIGNAL(clicked()), this, SLOT(webButtonClicked()));





    check4 = new QCheckBox("Website links by outgoing");
    check5 = new QCheckBox("Website links by incoming");
    QButtonGroup * group3 = new QButtonGroup();
    group3->addButton(check4);
    group3->addButton(check5);
    thirdLayout->addWidget(check4);
    thirdLayout->addWidget(check5);
    check4->toggle();


}
void Multiwin::ander() {
    if(radio1->isChecked()) {
        and_ = 1;
        or_ = 0;
    }
    else {
        and_=0;
        or_=1;
    }
}

void Multiwin::order() {
    if(radio2->isChecked()) {
        and_ = 0;
        or_ = 1;
    }
    else {
        and_=1;
        or_=0;
    }
}

void Multiwin::sortfile() {
    if(check1->isChecked()) {
        file_ = 1;
        out_ = 0;
        delete listWidget;
        listWidget = new QListWidget(this);

        AlphaStrComp comp1;
        std::vector<string> * sorter = new std::vector<string>;
        for(set<WebPage*>::iterator it = rr.begin(); it != rr.end(); ++it) {
            string rome = (*it)->filename();
            sorter->push_back(rome);
        }
        MergeSort<string,  AlphaStrComp> g;
        g.mergeSort(sorter,comp1);
        std::vector<string> co = *sorter;
        for (unsigned int g = 0; g < co.size(); g++) {
            for(unsigned int i = 0; i < (searcher.allweb).size(); i++) {
                if(co[g] == (searcher.allweb)[i]->filename() ) {
                    web = (searcher.allweb)[i];
                }
            }
            QListWidgetItem *newItem = new QListWidgetItem;
            stringstream ss;
            ss << web->linker.size();
            string out_going_link =  ss.str();
            QString outlink = QString::fromStdString("[outgoing links: " + out_going_link + "]");
            QString qstr = QString::fromStdString(co[g]);

            newItem->setText(qstr + outlink);
            listWidget->addItem(newItem);
        }
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemClicked(QListWidgetItem *)));
        otherLayout->addWidget(listWidget);
    }
    else {
        file_=0;
        out_=1;
    }
}

void Multiwin::sortout() {
    if(check2->isChecked()) {
        file_ = 0;
        out_ = 1;
        delete listWidget;
        listWidget = new QListWidget(this);

        outComp comp1;
        std::vector<WebPage*> *sorter = new std::vector<WebPage*>;
        for(set<WebPage*>::iterator it = rr.begin(); it != rr.end(); ++it) {
            test = *it;
            sorter->push_back(test);
        }
        MergeSort<WebPage*,  outComp> g;
        g.mergeSort(sorter,comp1);
        std::vector<WebPage*> co = *sorter;
        for (unsigned int g = 0; g < co.size(); g++) {
            for(unsigned int i = 0; i < (searcher.allweb).size(); i++) {
                if(co[g]->filename() == (searcher.allweb)[i]->filename() ) {
                    web = (searcher.allweb)[i];
                }
            }
            QListWidgetItem *newItem = new QListWidgetItem;
            stringstream ss;
            ss << web->linker.size();
            string out_going_link =  ss.str();
            QString outlink = QString::fromStdString("[outgoing links: " + out_going_link + "]");
            QString qstr = QString::fromStdString(co[g]->filename());

            newItem->setText(qstr + outlink);
            listWidget->addItem(newItem);
        }
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemClicked(QListWidgetItem *)));
        otherLayout->addWidget(listWidget);
    }
    else {
        file_=1;
        out_=0;
    }
}

void Multiwin::sortpr() {
    if(check22->isChecked()) {
        file_ = 0;
        out_ = 0;
        pr_ = 1;
        delete listWidget;
        listWidget = new QListWidget(this);
        prComp comp1;
        std::vector<WebPage*> *sorter = new std::vector<WebPage*>;
        for(set<WebPage*>::iterator it = rr.begin(); it != rr.end(); ++it) {
            test = *it;
            sorter->push_back(test);
        }
        MergeSort<WebPage*,  prComp> g;
        g.mergeSort(sorter,comp1);
        std::vector<WebPage*> co = *sorter;
        for (unsigned int g = 0; g < co.size(); g++) {
            for(unsigned int i = 0; i < (searcher.allweb).size(); i++) {
                if(co[g]->filename() == (searcher.allweb)[i]->filename() ) {
                    web = (searcher.allweb)[i];
                }
            }
            QListWidgetItem *newItem = new QListWidgetItem;
            stringstream ss;
            ss << web->linker.size();
            string out_going_link =  ss.str();
            QString outlink = QString::fromStdString("[outgoing links: " + out_going_link + "]");
            QString qstr = QString::fromStdString(co[g]->filename());

            newItem->setText(qstr + outlink);
            listWidget->addItem(newItem);
        }
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemClicked(QListWidgetItem *)));
        otherLayout->addWidget(listWidget);
    }
    else {
        file_=0;
        out_=0;
    }
}



void Multiwin::mainButtonClicked() {
    otherWin->show();
    QString m = this->getDisplay();
    string myline = m.toStdString();

    for (unsigned int i=0; i<myline.length(); i++) {
        myline[i]=tolower(myline[i]);
    }
    std::vector<std::string> words;
    char delim = ' ';
    std::stringstream   mySstream( myline );
    std::string         temp;

    while( getline( mySstream, temp, delim ) ) {
        words.push_back( temp );
    }

    if(and_ == 1) {
        MySet<WebPage*> answer = searcher.find(words[0]);
        for (unsigned int i=1; i < words.size(); i++) {
            MySet<WebPage*> answer2 = searcher.find(words[i]);
            answer = answer.set_intersection(answer2);
        }
        
        MySet<WebPage*> temp;
        std::set<WebPage*>::iterator mo;
        for (mo=answer.begin(); mo!=answer.end(); ++mo) {
            temp = temp.set_union( ((*mo)->outgoing_links()));
            temp = temp.set_union( ((*mo)->incoming_links()));
        }
        answer = answer.set_union(temp);
        r.ranker(answer, config);
        display_results(answer);
    }

    else if (or_ == 1) {
        MySet<WebPage*> answer = searcher.find(words[0]);

        for (unsigned int i=1; i < words.size(); i++) {
            MySet<WebPage*> answer2 = searcher.find(words[i]);
            answer = answer.set_union(answer2);
        }
        if (answer.size() == 0) {
            //continue;
        }
        MySet<WebPage*> temp;
        std::set<WebPage*>::iterator mo;
        for (mo=answer.begin(); mo!=answer.end(); ++mo) {
            temp = temp.set_union( ((*mo)->outgoing_links()));
            temp = temp.set_union( ((*mo)->incoming_links()));
        }
        answer = answer.set_union(temp);
        r.ranker(answer, config);
        display_results(answer);

    }
    else {
        MySet<WebPage*> answer = searcher.find(myline);
        if (answer.size() == 0) {
            //continue;
        }
         MySet<WebPage*> temp;
        std::set<WebPage*>::iterator mo;
        for (mo=answer.begin(); mo!=answer.end(); ++mo) {
            temp = temp.set_union( ((*mo)->outgoing_links()));
            temp = temp.set_union( ((*mo)->incoming_links()));
        }
        answer = answer.set_union(temp);
        r.ranker(answer, config);
        display_results(answer);

    }
}


void Multiwin::otherButtonClicked() {
    otherWin->hide();
    delete listWidget;
}
void Multiwin::webButtonClicked() {
    thirdWin->hide();
}

void Multiwin::itemClicked(QListWidgetItem * g) {
    delete text;
    delete thirdButton;
    delete listWidgetout;

    thirdWin->show();
    int i=0;
    QString yy = g->text();
    string f = yy.toStdString();
    int count = 0;
    int r=0;
    while(f[r] != '[') {
        count++;
        r++;
    }
    f = f.substr(0, count);

    unsigned int check = 0;
    for(set<WebPage*>::iterator it = rr.begin(); it != rr.end() || check < rr.size(); ++it) {
        check++;
        if (f  == (*it)->filename()) {

            string ho = "                              "+(*it)->filename()+"                              ";
            QString om = QString::fromStdString(ho);
            thirdButton = new QPushButton(om);
            thirdLayout->addWidget(thirdButton);

            text = new QPlainTextEdit;
            text->setReadOnly(true);
            string arg = (**it).texter();
            text->setPlainText(QString::fromStdString(arg));
            thirdLayout->addWidget(text);
            i++;


            MySet<std::string> olink = (*it)->linker;
            listWidgetout = new QListWidget(thirdWin);
            int i=0;
            std::set<std::string>::iterator mon;
            for (mon=olink.begin(); mon!=olink.end(); ++mon) {
                string m = *mon;
                QListWidgetItem *newItem = new QListWidgetItem;

                QString outlink = QString::fromStdString("[outgoing link(s)]");
                QString qstr = QString::fromStdString(m);

                newItem->setText(qstr + outlink);
                listWidgetout->addItem(newItem);
                i++;
            }
            thirdLayout->addWidget(listWidgetout);
            QObject::connect(listWidgetout, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(linkClicked(QListWidgetItem *)));
        }
    }


}


void Multiwin::linkClicked(QListWidgetItem * g) {
    delete text;
    delete thirdButton;
    QString yy = g->text();
    string f = yy.toStdString();
    int count = 0;
    int r=0;
    while(f[r] != '[') {
        count++;
        r++;
    }
    f = f.substr(0, count);
    f= "data/"+f;
    for(unsigned int i = 0; i < (searcher.allweb).size(); i++) {
        if(f == (searcher.allweb)[i]->filename() ) {
            string ho = "                              "+(searcher.allweb)[i]->filename()+"                              ";
            QString om = QString::fromStdString(ho);
            thirdButton = new QPushButton(om);
            thirdLayout->addWidget(thirdButton);

            text = new QPlainTextEdit;
            text->setReadOnly(true);
            string arg = (searcher.allweb)[i]->texter();
            text->setPlainText(QString::fromStdString(arg));
            thirdLayout->addWidget(text);

            MySet<std::string> olink = (searcher.allweb)[i]->linker;
            delete listWidgetout;
            listWidgetout = new QListWidget(thirdWin);
            std::set<std::string>::iterator mon;
            for (mon=olink.begin(); mon!=olink.end(); ++mon) {
                string m = *mon;
                QListWidgetItem *newItem = new QListWidgetItem;

                QString outlink = QString::fromStdString("[outgoing link]");
                QString qstr = QString::fromStdString(m);

                newItem->setText(qstr + outlink);
                listWidgetout->addItem(newItem);
            }
            thirdLayout->addWidget(listWidgetout);
            QObject::connect(listWidgetout, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(linkClicked(QListWidgetItem *)));
        }
    }


}

QString Multiwin::getDisplay() {
    QString a = line->displayText();
    return a;
}

void Multiwin::display_results(MySet<WebPage*>& results) {
    rr=results;
    listWidget = new QListWidget(this);


   prComp comp1;
        std::vector<WebPage*> *sorter = new std::vector<WebPage*>;
        for(set<WebPage*>::iterator it = rr.begin(); it != rr.end(); ++it) {
            test = *it;
            sorter->push_back(test);
        }
        MergeSort<WebPage*,  prComp> g;
        g.mergeSort(sorter,comp1);
        std::vector<WebPage*> co = *sorter;
        for (unsigned int g = 0; g < co.size(); g++) {
            for(unsigned int i = 0; i < (searcher.allweb).size(); i++) {
                if(co[g]->filename() == (searcher.allweb)[i]->filename() ) {
                    web = (searcher.allweb)[i];
                }
            }
            QListWidgetItem *newItem = new QListWidgetItem;
            stringstream ss;
            ss << web->linker.size();
            string out_going_link =  ss.str();
            QString outlink = QString::fromStdString("[outgoing links: " + out_going_link + "]");
            QString qstr = QString::fromStdString(co[g]->filename());

            newItem->setText(qstr + outlink);
            listWidget->addItem(newItem);
        }
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemClicked(QListWidgetItem *)));
        otherLayout->addWidget(listWidget);
}