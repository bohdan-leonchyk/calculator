#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

#define LETTER 55

double firstNum;
bool isTypingSecondNumber = false;

LeonchykCalculator::LeonchykCalculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeonchykCalculator)
{
    ui->setupUi(this);

    connect(ui->zeroButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->oneButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->twoButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->threeButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->fourButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->fiveButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->sixButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->sevenButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->eightButton, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->nineButton, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->negativeButton, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->percentButton, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->sqrtButton, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui->plusButton, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->minusButton, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->divideButton, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->multiplyButton, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    connect(ui->SinButton, SIGNAL(released()), this, SLOT(trigonometric_operation_pressed()));
    connect(ui->CosButton, SIGNAL(released()), this, SLOT(trigonometric_operation_pressed()));
    connect(ui->TangButton, SIGNAL(released()), this, SLOT(trigonometric_operation_pressed()));
    connect(ui->LogButton, SIGNAL(released()), this, SLOT(trigonometric_operation_pressed()));

    connect(ui->x2Button, SIGNAL(released()), this, SLOT(numeral_system_pressed()));
    connect(ui->x16Button, SIGNAL(released()), this, SLOT(numeral_system_pressed()));

    ui->plusButton->setCheckable(true);
    ui->minusButton->setCheckable(true);
    ui->divideButton->setCheckable(true);
    ui->multiplyButton->setCheckable(true);

}

LeonchykCalculator::~LeonchykCalculator()
{
    delete ui;
}

void LeonchykCalculator::digit_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    double labelNumber;
    QString newLabel;

    if ((ui->plusButton->isChecked() || ui->minusButton->isChecked() ||
            ui->multiplyButton->isChecked() || ui->divideButton->isChecked()) &&
            !isTypingSecondNumber)
    {
        labelNumber = button->text().toDouble();
        isTypingSecondNumber = true;
        newLabel = QString::number(labelNumber,'g',15);
    }
    else
    {
        if (ui->label->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        }
        else
        {
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber,'g',15);
        }

    }

    ui->label->setText(newLabel);
}

void LeonchykCalculator::on_dotButton_released()
{
    ui->label->setText(ui->label->text() + ".");
}

void LeonchykCalculator::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if (button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber *= -1;
    }

    if (button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber *= 0.01;
    }

    if (button->text() == "Sqrt")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = std::sqrt(labelNumber);
    }

    newLabel = QString::number(labelNumber,'g',15);
    ui->label->setText(newLabel);
}

void LeonchykCalculator::on_resetButton_released()
{
    ui->plusButton->setChecked(false);
    ui->minusButton->setChecked(false);
    ui->multiplyButton->setChecked(false);
    ui->divideButton->setChecked(false);

    isTypingSecondNumber = false;

    ui->label->setText("0");
}

void LeonchykCalculator::on_equalButton_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if (ui->plusButton->isChecked())
    {
        labelNumber = firstNum + secondNum;
        ui->plusButton->setChecked(false);
    }
    else if (ui->minusButton->isChecked())
    {
        labelNumber = firstNum - secondNum;
        ui->minusButton->setChecked(false);
    }
    else if (ui->divideButton->isChecked())
    {
        labelNumber = ((secondNum == 0) ? 0 : firstNum / secondNum);
        ui->divideButton->setChecked(false);
    }
    else if (ui->multiplyButton->isChecked())
    {
        labelNumber = firstNum * secondNum;
        ui->multiplyButton->setChecked(false);
    }

    newLabel = QString::number(labelNumber,'g',15);
    ui->label->setText(newLabel);
    isTypingSecondNumber = false;
}

void LeonchykCalculator::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);
}

void LeonchykCalculator::trigonometric_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    QString newLabel;
    double labelNumber;

    labelNumber = ui->label->text().toDouble();

    if (button->text() == "Sin")
    {
        labelNumber = std::sin(labelNumber);
    }
    else if (button->text() == "Cos")
    {
        labelNumber = std::cos(labelNumber);
    }
    else if (button->text() == "Tang")
    {
        labelNumber = std::tan(labelNumber);
    }
    else if (button->text() == "Log")
    {
        if (labelNumber > 0)
        {
            labelNumber = std::log(labelNumber);
        }
        else
        {
            labelNumber = 0;
        }
    }

    newLabel = QString::number(labelNumber,'g',15);
    ui->label->setText(newLabel);
}

std::string toBase(int value, int base)
{
    std::string newValue;
    int level, last;

    level = 1;

    if (value < 0)
    {
        newValue += "-";
        value *= -1;
    }

    for (int reminder = value; reminder >= base; reminder /= base)
    {
        level *= base;
    }

    for (int times = 0; level >= base; level /= base)
    {
        times = value / level;
        value -= times * level;

        if ( times > 9 ) newValue += times+LETTER;
        else newValue += std::to_string(times);
    }

    last = value / level;

    if ( last > 9 ) newValue += last+LETTER;
    else newValue += std::to_string(last);

    return newValue;
}

void LeonchykCalculator::numeral_system_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    QString newLabel;
    double labelNumber;
    std::string result;

    labelNumber = ui->label->text().toInt();

    if (button->text() == "2x")
    {
        result = toBase(labelNumber, 2);
    }
    else if (button->text() == "16x")
    {
        result = toBase(labelNumber, 16);
    }

    newLabel = QString::fromStdString(result);
    ui->label->setText(newLabel);
}
