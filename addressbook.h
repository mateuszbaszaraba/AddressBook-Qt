#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class AddressBook; }
QT_END_NAMESPACE

class AddressBook : public QWidget
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = nullptr);

public slots:
    void addContact();
    void submitContact();
    void cancel();

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;

    QMap<QString, QString> contacts;
    QString oldName;
    QString oldAddress;
};
#endif // ADDRESSBOOK_H
