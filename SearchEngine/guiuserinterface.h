#ifndef GUIUSERINTERFACE_H
#define GUIUSERINTERFACE_H

#include <QMainWindow>
#include <QFileDialog>
#include "indexhandler.h"
#include "queryprocessor.h"
#include "pagelocation.h"
#include "documentparser.h"

namespace Ui {
class GUIUserInterface;
}

class GUIUserInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit GUIUserInterface(QWidget *parent = 0);
    ~GUIUserInterface();

    void setName(const QString &name);
    QString name() const;


private slots:
    //calls query processor based on user specified query
    void on_searchQuery_clicked();
    //calls query processor based on user specified query
    void on_queryText_returnPressed();
    //part of destructor
    void on_GUIUserInterface_destroyed();
    //opens File dialog widget to add files to index
    void on_addFilesButton_clicked();
    //clears index and persistent index
    void on_clearAllButton_clicked();
    //parse data into the given data structure
    void on_parseDataButton_clicked();

    void on_pendFileNames_doubleClicked(const QModelIndex &index);
    //opens up a wikobooks document
    void on_tesultsTableWidget_doubleClicked(const QModelIndex &index);
    //reads in persistent index
    void on_pushButton_clicked();
    //shows statistics in dialog
    void on_getStatsbutton_clicked();

private:
    Ui::GUIUserInterface *ui;
    IndexHandler indexhandler;
    QueryProcessor processor;

    //changing screen vars
    QStringList pendingPaths;
    QStringList currPaths;

    //query results
    vector<PageLocation> results;


};

#endif // GUIUSERINTERFACE_H
