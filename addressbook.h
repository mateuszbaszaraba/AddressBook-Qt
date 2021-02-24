#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "finddialog.h"

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
    void removeContact();
    void editContact();
    void cancel();
    void next();
    void previous();
    void findContact();

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;

    QMap<QString, QString> contacts;
    QString oldName;
    QString oldAddress;
    FindDialog *dialog;

    enum Mode { NavigationMode, AddingMode, EditingMode };
    void updateInterface(Mode mode);
    Mode currentMode;
};
#endif // ADDRESSBOOK_H
