#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AddressBook; }
QT_END_NAMESPACE

class AddressBook : public QMainWindow
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = nullptr);
    ~AddressBook();

private:
    Ui::AddressBook *ui;
};
#endif // ADDRESSBOOK_H
