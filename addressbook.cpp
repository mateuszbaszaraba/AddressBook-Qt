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

    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);

    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);

    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);

    dialog = new FindDialog(this);


    connect(addButton, &QPushButton::clicked,
            this, &AddressBook::addContact);
    connect(submitButton, &QPushButton::clicked,
            this, &AddressBook::submitContact);
    connect(cancelButton, &QPushButton::clicked,
            this, &AddressBook::cancel);

    connect(nextButton, &QPushButton::clicked,
            this, &AddressBook::next);
    connect(previousButton, &QPushButton::clicked,
            this, &AddressBook::previous);

    connect(editButton, &QPushButton::clicked,
            this, &AddressBook::editContact);
    connect(removeButton, &QPushButton::clicked,
            this, &AddressBook::removeContact);

    connect(findButton, &QPushButton::clicked,
            this, &AddressBook::findContact);

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton, Qt::AlignTop);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addStretch();

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(addressText, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 2, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("Address Book by bbk"));
}

void AddressBook::addContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    nameLine->clear();
    addressText->clear();

    updateInterface(AddingMode);
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

    if(currentMode==AddingMode)
    {
        if(!contacts.contains(name))
        {
            contacts.insert(name, address);
            QMessageBox::information(this, tr("Add successful"),
                                     tr("\"%1\" has been added to address book.").arg(name));
        } else {
            QMessageBox::information(this, tr("Failed"),
                                     tr("\"%1\" is already in address book").arg(name));
        }
    }
    else if(currentMode==EditingMode)
    {
        if(oldName != name)
        {
            if(!contacts.contains(name))
            {
                QMessageBox::information(this, tr("Edit successful"),
                                         tr("\"%1\" has been edited in your address book.").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name, address);
            } else {
                QMessageBox::information(this, tr("Edit unsuccessful"),
                                         tr("\"%1\" is already in address book").arg(name));
            }
        } else if(oldAddress != address) {
            QMessageBox::information(this, tr("Edit successful"),
                                      tr("\"%1\" has been edited in your address book.").arg(name));
            contacts[name] = address;
        }
    }

    updateInterface(NavigationMode);
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

    int number = contacts.size();
    nextButton->setEnabled(number>1);
    previousButton->setEnabled(number>1);
}

void AddressBook::next()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i != contacts.end())
        i++;

    if (i == contacts.end())
        i = contacts.begin();

    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void AddressBook::previous()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i == contacts.end()){
        nameLine->clear();
        addressText->clear();
        return;
    }

    if (i == contacts.begin())
        i = contacts.end();

    i--;
    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void AddressBook::editContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    updateInterface(EditingMode);
}

void AddressBook::removeContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if(contacts.contains(name))
    {
        int button = QMessageBox::question(this,
                                        tr("Confirm remove"),
                                        tr("Are you sure you want to remove %1 ?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            previous();
            contacts.remove(name);

            QMessageBox::information(this, tr("Remove successful"),
                                     tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }
    updateInterface(NavigationMode);
}

void AddressBook::updateInterface(Mode mode)
{
    currentMode = mode;

    switch(currentMode) {

        case AddingMode:
        case EditingMode:

        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        addressText->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);

        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();
        break;

        case NavigationMode:

        if(contacts.isEmpty())
        {
            nameLine->clear();
            addressText->clear();
        }

        nameLine->setReadOnly(true);
        addressText->setReadOnly(true);
        addButton->setEnabled(true);

        int number = contacts.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number >1 );
        findButton->setEnabled(number > 2);

        submitButton->hide();
        cancelButton->hide();
        break;

    }
}

void AddressBook::findContact()
{
    dialog->show();

    if (dialog->exec() == QDialog::Accepted) {
        QString contactName = dialog->getFindText();

        if (contacts.contains(contactName)) {
            nameLine->setText(contactName);
            addressText->setText(contacts.value(contactName));
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
            return;
        }
    }

    updateInterface(NavigationMode);
}

















