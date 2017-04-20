#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class LeonchykCalculator;
}

class LeonchykCalculator : public QMainWindow
{
    Q_OBJECT

    public:
        explicit LeonchykCalculator(QWidget *parent = 0);
        ~LeonchykCalculator();

    private:
        Ui::LeonchykCalculator *ui;

    private slots:
        void digit_pressed();
        void on_dotButton_released();
        void unary_operation_pressed();
        void on_resetButton_released();
        void on_equalButton_released();
        void binary_operation_pressed();
        void trigonometric_operation_pressed();
        void numeral_system_pressed();
};

#endif // MAINWINDOW_H
