#ifndef TODOLIST_H
#define TODOLIST_H

#include "setting.h"
#include "addtask.h"

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QtDebug>


#ifdef __linux__
    #define addressDatabas "/home/mohammad/Documents/University/Projects/todo_list/Todo-List/src/database.sqlite"
#elif _WIN32
	#define addressDatabas "D:/Blue Folder/Project/1 Big Projects/To-do list/database.sqlite"
#endif


class task{
public:
	QString id;
	QString title = "";
	QString group = "";
	QString description = "";
	QString step[6] = {""};
	QString priority = "";
	QString deadline = "";
	QString createdate = "";
	QString note = "";
	bool checkStep[6] = {};
};


namespace Ui {
class Todolist;
}


class Todolist : public QDialog
{
	Q_OBJECT

public:
	explicit Todolist(QWidget *parent = nullptr);
	~Todolist();
	void setData();
	QString getUsername();
	void readData(QString username);
	void getData(QSqlQuery q);
	void setGroup();
	bool isDigit(QString str);
	void saveID(int id);


private slots:

	void on_btn_setting_clicked();

	void on_btn_addtask_clicked();

	void on_btn_sortby_clicked();

	void on_btn_categories_clicked();

	void on_btn_pervious_clicked();

	void on_btn_next_clicked();

	void on_btn_first_clicked();

	void on_btn_end_clicked();

	void on_btn_search_clicked();

	void on_btn_reset_clicked();

	void on_pte_showtask1_selectionChanged();

	void on_pte_showtask2_selectionChanged();

	void on_pte_showtask3_selectionChanged();

	void on_pte_showtask4_selectionChanged();

private:
	Ui::Todolist *ui;
	QString username;
	int start = 0;
	QList<task> tasks;
	QList<QString> cate;
	QSqlDatabase db;
};

#endif // TODOLIST_H
