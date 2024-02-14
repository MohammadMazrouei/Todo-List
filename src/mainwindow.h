#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "todolist.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	bool check_username();
	bool check_password();

private slots:
	void on_btn_login_clicked();

	void on_btn_signup_clicked();

private:
	Ui::MainWindow *ui;
	QSqlDatabase db;
};
#endif // MAINWINDOW_H
