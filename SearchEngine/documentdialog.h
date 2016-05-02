#ifndef DOCUMENTDIALOG_H
#define DOCUMENTDIALOG_H

#include <QDialog>
#include "rapidxml.hpp"

namespace Ui {
class DocumentDialog;
}

class DocumentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocumentDialog(QWidget *parent = 0);
    ~DocumentDialog();
    //supplying this function with a rapid xml node pointer to a WikiBooks article
    //will display the title, author, and text of the document in a dialog box
    void setDocument(rapidxml::xml_node<>*);

private:
    Ui::DocumentDialog *ui;
};

#endif // DOCUMENTDIALOG_H
