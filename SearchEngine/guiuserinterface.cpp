#include "guiuserinterface.h"
#include "ui_guiuserinterface.h"
#include <iostream>
#include "rapidxml.hpp"
#include "documentdialog.h"
#include <algorithm>
#include "statsdialog.h"
#include <QDialog>

GUIUserInterface::GUIUserInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUIUserInterface)
{
    ui->setupUi(this);

    //after UI is setup, setup the Search Engine
    processor.setHandler(indexhandler);

    //setup for certeain widgets
    ui->tesultsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tesultsTableWidget->verticalHeader()->setVisible(false);
    ui->tesultsTableWidget->setColumnWidth(0,100);
    ui->tesultsTableWidget->setColumnWidth(1,275);
    ui->tesultsTableWidget->setColumnWidth(2,250);
    ui->tesultsTableWidget->setColumnWidth(3,100);

}

GUIUserInterface::~GUIUserInterface()
{
    //saves the persistent index

    indexhandler.writePersistentIndex();
    indexhandler.deleteIndex();
    delete ui;
}


//Executed when query is enterred and searched for
void GUIUserInterface::on_searchQuery_clicked()
{
    cout << "load query begin" << endl;
    results.clear();
    //do something with query
    string queryString = ui->queryText->text().toStdString();
    processor.processQuery(queryString);
    results = processor.getResults();
    processor.clearResults();
    //LUKE add processor.clear()
    ui->tesultsTableWidget->clearContents();
    //ui->tesultsTableWidget
    ui->tesultsTableWidget->setRowCount(min(static_cast<int>(results.size()),15));

    for(int row=0;row<results.size() && row<15;row++)
    {
       rapidxml::xml_node<>* pageNode= indexhandler.parser().getPage(results.at(row).getPageID());
       rapidxml::xml_node<>* tempNode = nullptr;
       //setting ID
       QTableWidgetItem* idItem = new QTableWidgetItem();
       idItem->setText(QString::number(results.at(row).getPageID()));
       ui->tesultsTableWidget->setItem(row,0,idItem);

       //seting title
       QTableWidgetItem* titleItem = new QTableWidgetItem();
       tempNode = pageNode->first_node("title");
       string title = "N/A";
       if(tempNode!=nullptr)
           title = tempNode->value();
       titleItem->setText(QString::fromStdString(title));
       ui->tesultsTableWidget->setItem(row,1,titleItem);

       //seting author
       QTableWidgetItem* authorItem = new QTableWidgetItem();
       tempNode = pageNode->first_node("revision")->first_node("contributor")->first_node("username");
       string author = "N/A";
       if(tempNode!=nullptr)
           author = tempNode->value();
       authorItem->setText(QString::fromStdString(author));
       ui->tesultsTableWidget->setItem(row,2,authorItem);

       //seting TF/IDF
       QTableWidgetItem* tfidfItem = new QTableWidgetItem();
       double d = results.at(row).getTfIdf();
       tfidfItem->setText(QString::number(d));
       ui->tesultsTableWidget->setItem(row,3,tfidfItem);

    }

    //ui->tesultsTableWidget->resizeColumnsToContents();
    cout << "r" << ui->tesultsTableWidget->rowCount() << "c" << ui->tesultsTableWidget->columnCount() << endl;

    //add error message/RED outline/highlight for improperly formatted query
}

//refer to the searchQuery button press action
void GUIUserInterface::on_queryText_returnPressed()
{
    on_searchQuery_clicked();
}

//called when the Main Window (program) is closed
void GUIUserInterface::on_GUIUserInterface_destroyed()
{
    /*
    indexhandler.writePersistentIndex();
    indexhandler.deleteIndex();
    */
}

void GUIUserInterface::on_addFilesButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("XML Files (*.xml)"));
    pendingPaths.append(fileNames);
    ui->pendFileNames->addItems(pendingPaths);
}

void GUIUserInterface::on_clearAllButton_clicked()
{
    indexhandler.clearIndex();
    ui->pendFileNames->clear();
    pendingPaths.clear();
    ui->currFileNames->clear();
    currPaths.clear();
    //LUKE: need to clear table view
    ui->queryText->clear();

    ui->avlRadio->setEnabled(true);
    ui->hashRadio->setEnabled(true);
    ui->pushButton->setEnabled(true);
}

void GUIUserInterface::on_parseDataButton_clicked()
{
    if(ui->hashRadio->isChecked())
    {
        indexhandler.setIndexType(2);
    } else
    {
        indexhandler.setIndexType(1);
    }

    //TODO:need to check and make sure the file isnt already part of the persistent index
    for(int i = 0; i< pendingPaths.size();i++)
    {
        vector<string> alreadyParsed = indexhandler.parser().getFilesAdded();
        if(std::count(alreadyParsed.begin(),alreadyParsed.end(),pendingPaths.at(i).toStdString())==0)
        {
            indexhandler.addNewPath(pendingPaths.at(i).toStdString());
            indexhandler.addPath(pendingPaths.at(i).toStdString());
        }

    }
    //type 1=avl 2=hash

    indexhandler.createIndex();
    indexhandler.indexPaths(indexhandler.getNewPaths());
    //indexhandler.clearNewPaths();

    ui->pendFileNames->clear();
    ui->currFileNames->clear();

    //TODO: read in persistent data into index, as well as file paths
    //indexhandler.readPersistentIndex();

    pendingPaths.clear();
    currPaths.clear();
    for(string s:indexhandler.parser().getFilesAdded())
    {
        currPaths.append(QString::fromStdString(s));
    }
    //currPaths.append(pendingPaths);

    ui->currFileNames->clear();
    ui->currFileNames->addItems(currPaths);


    //TODO: add both "new files" and files from "persistent" into the "currently in index" list

    //we dont need to have the radio buttons once we have loaded files into a structure
    ui->avlRadio->setEnabled(false);
    ui->hashRadio->setEnabled(false);
    ui->pushButton->setEnabled(false);
}


void GUIUserInterface::on_pendFileNames_doubleClicked(const QModelIndex &index)
{
    //cout << index.row() << endl;
}

void GUIUserInterface::on_tesultsTableWidget_doubleClicked(const QModelIndex &index)
{
    //do somethi g with the index/row clicjked
    cout << "double clicked row: " << index.row() << endl;

    DocumentDialog dialog;
    dialog.setDocument(indexhandler.parser().getPage(results.at(index.row()).getPageID()));
    dialog.show();
    dialog.exec();
}

void GUIUserInterface::on_pushButton_clicked()
{
    if(ui->hashRadio->isChecked())
       {
           indexhandler.setIndexType(2);
       } else
       {
           indexhandler.setIndexType(1);
       }
   indexhandler.createIndex();

    //read into the
    indexhandler.readPersistentIndex();

    currPaths.clear();
    for(string s:indexhandler.parser().getFilesAdded())
    {
        currPaths.append(QString::fromStdString(s));
    }
    //currPaths.append(pendingPaths);

    ui->currFileNames->clear();
    ui->currFileNames->addItems(currPaths);

    ui->avlRadio->setEnabled(false);
    ui->hashRadio->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

void GUIUserInterface::on_getStatsbutton_clicked()
{
    indexhandler.calculateStats();
    int nw = indexhandler.getNumWords();
    int np = indexhandler.getNumPages();
    vector< pair<string,int> > words = indexhandler.getTop50Words();

    StatsDialog window;
    window.setStats(np,nw,words);
    window.show();
    window.exec();
}
