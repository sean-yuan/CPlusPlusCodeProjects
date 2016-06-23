#ifndef MULTIWIN_H
#define MULTIWIN_H
#include <iostream>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QInputDialog>
#include <QPlainTextEdit>
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
#include <QListWidget>
using namespace std;
class Multiwin : public QWidget
{
    Q_OBJECT
public:
    Multiwin(string h);
    QString getDisplay();
    void display_results(MySet<WebPage*>& results);
    std::map<std::string, std::string> configer(std::string file1);
    std::string parse_space(std::string s) ;
    int and_;
    int or_;
    int file_;
    int out_;
    int pr_;
    std::string config;

public slots:
    void itemClicked(QListWidgetItem * g);
    void linkClicked(QListWidgetItem * g);
    void ander();
    void order();
    void sortfile();
    void sortout();
    void sortpr();
    void mainButtonClicked();
    void webButtonClicked();
    void otherButtonClicked();
private:
    WebPage* web;
    WebPage* test;
    QPushButton* mainButton;
    QPushButton* webButton;
    QVBoxLayout* mainLayout;
    QPlainTextEdit * text;
    QVBoxLayout* thirdLayout;
    QWidget* thirdWin;
    QPushButton* thirdButton;

    QWidget* otherWin;
    QPushButton* otherButton;
    QLineEdit *line;
    QListWidget *listWidget;
    QListWidget *listWidgetout;
    QCheckBox *radio1;
    QCheckBox *radio2;
    QString qstr;
    QCheckBox *check1;
    QCheckBox *check22;
    QCheckBox *check2;
    QCheckBox *check3;
    QCheckBox *check4;
    QCheckBox *check5;

    MySet<WebPage*> rr;
    QVBoxLayout* otherLayout;
    Ranker r;
    SearchEng searcher;
    PageParser* pager;

};
#endif