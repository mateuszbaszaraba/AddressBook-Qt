#include "addressbook.h"
#include "ui_addressbook.h"

#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

AddressBook::AddressBook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);


    QLabel *addressLabel = new QLabel(tr("Address:"));
    addressText = new QTextEdit;
    addressText->setReadOnly(true);

    addButton = new QPushButton(tr("&Add"));
    addButton->show();
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();


    connect(addButton, &QPushButton::clicked,
            this, &AddressBook::addContact);
    connect(submitButton, &QPushButton::clicked,
            this, &AddressBook::submitContact);
    connect(cancelButton, &QPushButton::clicked,
            this, &AddressBook::cancel);

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton, Qt::AlignTop);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addStretch();


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(addressText, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);

    setLayout(mainLayout);
    setWindowTitle(tr("Address Book by bbk"));
}

void AddressBook::addContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    nameLine->clear();
    addressText->clear();

    nameLine->setReadOnly(false);
    nameLine->setFocus(Qt::OtherFocusReason);
    addressText->setReadOnly(false);

    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
}

void AddressBook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if(name.isEmpty() || address.isEmpty())
    {
        QMessageBox::information(this, tr("Empty field"),
                tr("Please enter a name and address."));
        return;
    }

    if(!contacts.contains(name))
    {
        contacts.insert(name, address);
        QMessageBox::information(this, tr("Add successful"),
                                 tr("\"%1\" has been added to address book.").arg(name));
    } else {
        QMessageBox::information(this, tr("Failed"),
                                 tr("\"%1\" is already in address book").arg(name));
        return;
    }

    if(contacts.isEmpty())
    {
        nameLine->clear();
        addressText->clear();
    }

    nameLine->setReadOnly(true);
    addressText->setReadOnly(true);
    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}

void AddressBook::cancel()
{
    nameLine->setText(oldName);
    nameLine->setReadOnly(true);


    addressText->setText(oldAddress);
    addressText->setReadOnly(true);

    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
}
















