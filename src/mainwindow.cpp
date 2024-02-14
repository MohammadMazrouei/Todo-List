#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(addressDatabas);
	if(!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : mainwindow -> Function : MainWindow");
		return;
	}
	QSqlQuery q;
	if(!q.exec("CREATE TABLE IF NOT EXISTS information(username VARCHAR(20), password VARCHAR(20)); ")) {
		QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Create Table Information. \nPage : mainwindow -> Function : MainWindow");
		db.close();
		return;
	}
	q.clear();
	db.close();
}


MainWindow::~MainWindow()
{
	delete ui;
}


bool MainWindow::check_username()
{
	QString username = ui->le_username->text();
	if(username.size() <= 0 || username.size() > 20 || username == "information")
		return false;

	return true;
}


bool MainWindow::check_password()
{
	QString password = ui->le_password->text();
	if(password.size() <= 0 || password.size() > 20)
		return false;

	return true;
}


void MainWindow::on_btn_login_clicked()
{
	// check information
	{
		if(!check_username()) {
			QMessageBox::warning(this, "Incorrect Name!", "Format Of Username Is Incorrect.");
			return;
		}
		if(!check_password()) {
			QMessageBox::warning(this, "Incorrect Pass!", "Format Of Password Is Incorrect.");
			return;
		}
	}

	if (!db.open()) {
		QMessageBox::warning(this, "Not Open Database!", "Not Successes To Open Database. \nPage : mainwindow -> Functino : on_btn_login_clicked");
		return;
	}

	QString username = ui->le_username->text();
	QString password = ui->le_password->text();
	QString pass = "";

	QSqlQuery q;
	if(!q.exec("SELECT * FROM information WHERE username = '"+username +"' ;")) {
		QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Login Search. \nPage : mainwindow -> Functino : on_btn_login_clicked");
		db.close();
		return;
	}

	while(q.next())
		pass = q.value(1).toString();
	q.clear();
	db.close();

	if (pass == "")
		QMessageBox::warning(this, "Not Find Username!", "Username Donnot Exist.");
	else if (pass != password)
		QMessageBox::warning(this, "Password!", "Password Is Incorrect.");
	else {
		QFile lastUser("lastUser.txt");
		if(!lastUser.open(QFile::WriteOnly | QFile::Text )) {
			QMessageBox::warning(this, "File Problem!", "Not Open lantUser.txt File. \nPage : mainwindow -> Functino : on_btn_login_clicked");
			return;
		}
		QTextStream in(&lastUser);
		in << username;
		lastUser.close();

		Todolist * td = new Todolist();
		td->show();
		this->close();
	}
}


void MainWindow::on_btn_signup_clicked()
{
	// check information
	{
		if(!check_username()) {
			QMessageBox::warning(this, "Incorrect Name!", "Format Of Username Is Incorrect.");
			return;
		}
		if(!check_password()) {
			QMessageBox::warning(this, "Incorrect Pass!", "Format Of Password Is Incorrect.");
			return;
		}
	}

	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : mainwindow -> Function : on_btn_signup_clicked");
		return;
	}

	QString username = ui->le_username->text();
	QString password = ui->le_password->text();
	QString name = "";

	QSqlQuery q;
	if(!q.exec("SELECT * FROM information WHERE username = '"+username +"' ;")) {
		QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Signup Search. \nPage : mainwindow -> Function : on_btn_signup_clicked");
		db.close();
		return;
	}

	while(q.next())
		name = q.value(0).toString();
	q.clear();

	if(name != "") {
		QMessageBox::warning(this, "Name Exsist!", "This Username Before Use.");
		db.close();
		return;
	}


	if(!q.exec("INSERT INTO information VALUES('"+username +"', '"+password +"'); ")) {
		QMessageBox::warning(this, "Query Problem!", "Information Don't Add To Database. \nPage : mainwindow -> Function : on_btn_signup_clicked");
		db.close();
		return;
	}

	QFile lastUser("lastUser.txt");
	if(!lastUser.open(QFile::WriteOnly | QFile::Text )) {
			QMessageBox::warning(this, "File Problem!", "Not Open lantUser.txt File. \nPage : mainwindow -> Functino : on_btn_sigtup_clicked");
			db.close();
			return;
	}
	QTextStream in(&lastUser);
	in << username;
	lastUser.close();

	// create table for new user
	{
		if(!q.exec("CREATE TABLE IF NOT EXISTS '"+username +"' "
				   "(id INTEGER PRIMARY KEY AUTOINCREMENT , "
				   "username VARCHAR(20), "
				   "title VARCHAR(40), "
				   "description VARCHAR(200), "
				   "step1 VARCHAR(100) DEFAULT NULL, "
				   "step2 VARCHAR(100) DEFAULT NULL, "
				   "step3 VARCHAR(100) DEFAULT NULL, "
				   "step4 VARCHAR(100) DEFAULT NULL, "
				   "step5 VARCHAR(100) DEFAULT NULL, "
				   "step6 VARCHAR(100) DEFAULT NULL, "
				   "groupp VARCHAR(20) DEFAULT NULL, "
				   "note VARCHAR(100) DEFAULT NULL, "
				   "deadline DATE, "
				   "createdate DATE, "
				   "priority VARCHAR(2), "
				   "do_step1 INT DEFAULT 0, "
				   "do_step2 INT DEFAULT 0, "
				   "do_step3 INT DEFAULT 0, "
				   "do_step4 INT DEFAULT 0, "
				   "do_step5 INT DEFAULT 0, "
				   "do_step6 INT DEFAULT 0); "))
		{
			QMessageBox::warning(this, "Databas Problem!", "Donn,t Create Table For New User");
			db.close();
			return;
		}
	}

	q.clear();
	db.close();

	Todolist * td = new Todolist();
	td->show();
	this->close();
}
