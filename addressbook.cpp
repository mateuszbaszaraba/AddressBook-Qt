#include "addressbook.h"
#include "ui_addressbook.h"

AddressBook::AddressBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddressBook)
{
    ui->setupUi(this);
}

AddressBook::~AddressBook()
{
    delete ui;
}

