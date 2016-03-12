#ifndef DIALOG
#define DIALOG
#include <QDialog>
#include <QWidget>
namespace Ui {
class Dialog;
}
class Dialog : public QDialog{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    double *point1Settings();
    double *point2Settings();
    double *point3Settings();
    double *lightSettings();

private:
    Ui::Dialog *dui;

};

#endif // DIALOG

