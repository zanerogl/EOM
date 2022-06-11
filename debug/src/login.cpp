#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    this->setWindowIcon(QIcon(":/res/Zanerogl.png"));
    UI_Init();

}

login::~login()
{
    delete ui;
}

void login::UI_Init()
{
    image = new QImage(":/res/login.jpg");
    ui->avatar->setPixmap(QPixmap::fromImage(*image).scaled(ui->avatar->width(), ui->avatar->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void login::account_init()
{
    usernames.push_back("Zanerogl");
    usernames.push_back("Alfred");
    usernames.push_back("WSM");

    passwords.push_back("123698745");
}

void login::on_login_2_clicked()
{
    if((ui->username->text() == "Zanerogl" || ui->username->text() == "Alfred" || ui->username->text() == "WSM") && ui->password->text() == "123698745")
    {
        this->hide();
        window = new MainWindow;
    }
    else{
        ui->warning->setText("Incorrect account");
    }
}


void login::on_register_2_clicked()
{
    ui->warning->setText("In development...");
}
