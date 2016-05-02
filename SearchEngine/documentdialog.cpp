#include "documentdialog.h"
#include "ui_documentdialog.h"
#include "rapidxml.hpp"

DocumentDialog::DocumentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocumentDialog)
{
    ui->setupUi(this);
}

DocumentDialog::~DocumentDialog()
{
    delete ui;
}

void DocumentDialog::setDocument(rapidxml::xml_node<>* page)
{
    rapidxml::xml_node<>* temp = nullptr;
    temp = page->first_node("title");
    if(temp!=nullptr)
        ui->titleHeader->setText(QString::fromStdString(temp->value()));

    temp = page->first_node("revision")->first_node("contributor")->first_node("username");
    if(temp!=nullptr)
        ui->authorHeader->setText(QString::fromStdString(temp->value()));

    temp = page->first_node("revision")->first_node("text");
    if(temp!=nullptr)
        ui->textBrowser->setText(QString::fromStdString(temp->value()));
}

