#include "statsdialog.h"
#include "ui_statsdialog.h"

StatsDialog::StatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

StatsDialog::~StatsDialog()
{
    delete ui;
}

void StatsDialog::setStats(int pages, int words, std::vector<std::pair<std::__1::string, int> > &top50)
{
    ui->numPages->setText(QString::number(pages));
    ui->numWords->setText(QString::number(words));
    /*
    QString separated = "";
    int count = 0;
    for(std::pair<std::string,int> word : top50)
    {
        separated += QString::fromStdString(word.first);
        separated += "      #";
        separated += QString::number(word.second);
        separated += "\n";
        count++;
    }
    ui->top50Box->setText(separated);
    */

    ui->tableWidget->setRowCount(50);
    for(int i=0;i<top50.size();i++)
    {
        QTableWidgetItem* name = new QTableWidgetItem();
        name->setText(QString::fromStdString(top50.at(i).first));
        ui->tableWidget->setItem(i,0,name);

        QTableWidgetItem* num = new QTableWidgetItem();
        num->setText(QString::number(top50.at(i).second));
        ui->tableWidget->setItem(i,1,num);
    }

}
