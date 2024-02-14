#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>
#include <QSqlQuery>


class task2{
public:
	QString title;
	QString group;
	QString description;
	QString step[6];
	QString priority;
	QString deadline;
	QString createdate;
	QString note;
	bool checkStep[6] = {};
};


namespace Ui {
class addtask;
}

class addtask : public QDialog
{
	Q_OBJECT

public:
	explicit addtask(bool edited = false, QWidget *parent = nullptr);
	~addtask();
	QString getUsername();
	QString getID();
	bool check_title();
	bool check_group();
	bool check_description();
	bool check_step1();
	bool check_step2();
	bool check_step3();
	bool check_step4();
	bool check_step5();
	bool check_step6();
	bool check_deadline_year();
	bool check_deadline_month();
	bool check_deadline_day();
	bool check_deadline_hour();
	bool check_deadline_minute();
	bool check_note();
	bool check_priority();
	void show_inf(task2);
	void readData();
	void getData(QSqlQuery);
	bool isDigit(QString str);

private slots:
	void on_btn_cancel_clicked();

	void on_btn_ok_clicked();

	void on_checkBox_1_clicked();

	void on_checkBox_2_clicked();

	void on_checkBox_3_clicked();

	void on_checkBox_4_clicked();

	void on_checkBox_5_clicked();

private:
	Ui::addtask *ui;
	bool edit;
	task2 inf;
	QString username;
	QString id;
	QSqlDatabase db;
};

#endif // ADDTASK_H
