#include "setting.h"
#include "ui_setting.h"
#include "todolist.h"
#include "mainwindow.h"

setting::setting(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::setting)
{
	ui->setupUi(this);

	QFile lastUser("lastUser.txt");
	if(!lastUser.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, "File Problem!", "Not Open lastUser.txt File. \nPage : setting -> Function : setting");
		return;
	}
	QTextStream out(&lastUser);
	QString line = out.readLine();
	lastUser.close();

	ui->pte_info->setPlainText("Username : " + line + "\n");
}


setting::~setting()
{
	delete ui;
}


void setting::on_btn_back_clicked()
{
	Todolist * td = new Todolist();
	td->show();
	this->close();
}


void setting::on_btn_exit_clicked()
{
	this->close();
	QCoreApplication::quit();
}


void setting::on_btn_logout_clicked()
{
	QFile lastUser("lastUser.txt");
	if(!lastUser.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, "File Problem!", "Not Open lastUser.txt File. \nPage : setting -> Function : on_btn_logout_clicked");
		return;
	}
	lastUser.close();

	MainWindow * td = new MainWindow();
	td->show();
	this->close();
}
