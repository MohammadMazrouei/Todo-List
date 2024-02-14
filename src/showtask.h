#ifndef SHOWTASK_H
#define SHOWTASK_H

#include "todolist.h"
#include "addtask.h"

#include <QDialog>


namespace Ui {
class showtask;
}

class showtask : public QDialog
{
	Q_OBJECT

public:
	explicit showtask(QWidget *parent = nullptr);
	~showtask();
	void getData(QSqlQuery q);
	void setData();
	void readData();
	QString getUsername();
	QString getID();

private slots:
	void on_btn_edit_clicked();

	void on_btn_back_clicked();

	void on_btn_delete_clicked();

	void on_cb_step1_stateChanged(int arg1);

	void on_cb_step2_stateChanged(int arg1);

	void on_cb_step3_stateChanged(int arg1);

	void on_cb_step4_stateChanged(int arg1);

	void on_cb_step5_stateChanged(int arg1);

	void on_cb_step6_stateChanged(int arg1);

private:
	Ui::showtask *ui;
	task data;
	QString username;
	QString id;
	QSqlDatabase db;

};

#endif // SHOWTASK_H
