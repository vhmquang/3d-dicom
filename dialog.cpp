#include "ui_dialog.h"
#include "dialog.h"
Dialog::Dialog(QWidget *parent):
    QDialog(parent),
    dui(new Ui::Dialog)
{
    dui->setupUi(this);
}
Dialog::~Dialog(){
    delete dui;
}
double* Dialog::point1Settings(){
    static double point1[6];
    point1[0] = dui->_P1_Value->value();
    point1[1] = dui->_P1_R->value();
    point1[2] = dui->_P1_G->value();
    point1[3] = dui->_P1_B->value();
    point1[4] = dui->_P1_Opacity->value();
    point1[5] = dui->_P1_Gradient->value();
    return point1;
}
double* Dialog::point2Settings(){
    static double point2[6];
    point2[0] = dui->_P2_Value->value();
    point2[1] = dui->_P2_R->value();
    point2[2] = dui->_P2_G->value();
    point2[3] = dui->_P2_B->value();
    point2[4] = dui->_P2_Opacity->value();
    point2[5] = dui->_P2_Gradient->value();
    return point2;
}
double* Dialog::point3Settings(){
    static double point3[6];
    point3[0] = dui->_P3_Value->value();
    point3[1] = dui->_P3_R->value();
    point3[2] = dui->_P3_G->value();
    point3[3] = dui->_P3_B->value();
    point3[4] = dui->_P3_Opacity->value();
    point3[5] = dui->_P3_Gradient->value();
    return point3;
}
double *Dialog::lightSettings(){
    static double light[3];
    light[0] = dui->_Ambient->value();
    light[1] = dui->_Diffuse->value();
    light[2] = dui->_Specular->value();
    return light;
}
