#include "showtask.h"
#include "ui_showtask.h"


showtask::showtask(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::showtask)
{
	ui->setupUi(this);

	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(addressDatabas);
	username = getUsername();
	id = getID();
	readData();
	setData();
}


showtask::~showtask()
{
	delete ui;
}


void showtask::readData()
{
	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : showtask -> Function : readData");
		return;
	}

	QSqlQuery q;
	if(!q.exec("SELECT * FROM '"+username +"' WHERE id = '"+id +"'; ")) {
		QMessageBox::warning(this, "Database Problem!", "Not Execute Databas For Read. \nPage : showtask -> Function : readData");
		db.close();
		return;
	}

	getData(q);
	q.clear();
	db.close();
}


void showtask::getData(QSqlQuery q)
{
	while(q.next()){
		data.title = q.value(2).toString();
		data.description = q.value(3).toString();
		data.step[0] = q.value(4).toString();
		data.step[1] = q.value(5).toString();
		data.step[2] = q.value(6).toString();
		data.step[3] = q.value(7).toString();
		data.step[4] = q.value(8).toString();
		data.step[5] = q.value(9).toString();
		data.group = q.value(10).toString();
		data.note = q.value(11).toString();
		data.deadline = q.value(12).toString();
		data.createdate = q.value(13).toString();
		data.priority = q.value(14).toString();
		data.checkStep[0] = q.value(15).toBool();
		data.checkStep[1] = q.value(16).toBool();
		data.checkStep[2] = q.value(17).toBool();
		data.checkStep[3] = q.value(18).toBool();
		data.checkStep[4] = q.value(19).toBool();
		data.checkStep[5] = q.value(20).toBool();
	}
	q.clear();
}


void showtask::setData()
{
	ui->pte_title->setPlainText(data.title);
	ui->pte_description->setPlainText(data.description);
	ui->cb_step1->setText(data.step[0]);
	ui->cb_step2->setText(data.step[1]);
	ui->cb_step3->setText(data.step[2]);
	ui->cb_step4->setText(data.step[3]);
	ui->cb_step5->setText(data.step[4]);
	ui->cb_step6->setText(data.step[5]);
	ui->pte_group->setPlainText(data.group);
	ui->pte_note->setPlainText(data.note);
	ui->pte_deadline->setPlainText(data.deadline);
	ui->pte_createdate->setPlainText(data.createdate);
	ui->label_priority->setText(data.priority);
	if(data.checkStep[0]){
		ui->cb_step1->setChecked(true);
		QFont tmp = ui->cb_step1->font();
		tmp.setStrikeOut(true);
		ui->cb_step1->setFont(tmp);
	}
	if(data.checkStep[1]){
		ui->cb_step2->setChecked(true);
		QFont tmp = ui->cb_step2->font();
		tmp.setStrikeOut(true);
		ui->cb_step2->setFont(tmp);
	}
	if(data.checkStep[2]){
		ui->cb_step3->setChecked(true);
		QFont tmp = ui->cb_step3->font();
		tmp.setStrikeOut(true);
		ui->cb_step3->setFont(tmp);
	}
	if(data.checkStep[3]){
		ui->cb_step4->setChecked(true);
		QFont tmp = ui->cb_step4->font();
		tmp.setStrikeOut(true);
		ui->cb_step4->setFont(tmp);
	}
	if(data.checkStep[4]){
		ui->cb_step5->setChecked(true);
		QFont tmp = ui->cb_step5->font();
		tmp.setStrikeOut(true);
		ui->cb_step5->setFont(tmp);
	}
	if(data.checkStep[5]){
		ui->cb_step6->setChecked(true);
		QFont tmp = ui->cb_step6->font();
		tmp.setStrikeOut(true);
		ui->cb_step6->setFont(tmp);
	}
}


QString showtask::getUsername()
{
	QFile lastUser("lastUser.txt");
	if(!lastUser.open(QFile::ReadOnly | QFile::Text )) {
		QMessageBox::warning(this, "File Problem!", "Not Open lastUser.txt File. \nPage : showtask -> Function : getUsername");
		return "";
	}
	QTextStream in(&lastUser);
	QString username = in.readLine().split(' ')[0];
	lastUser.close();
	return username;
}


QString showtask::getID()
{
	QFile userID("userID.txt");
	if(!userID.open(QFile::ReadOnly | QFile::Text )) {
		QMessageBox::warning(this, "File Problem!", "Not Open userID.txt File. \nPage : showtask -> Function : getID");
		return "";
	}
	QTextStream in(&userID);
	QString id = in.readLine();
	userID.close();
	return id;
}


void showtask::on_btn_delete_clicked()
{
	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : showtask -> Function : on_btn_delete_clicked");
		return;
	}

	QSqlQuery q;
	if(!q.exec("DELETE FROM '"+username +"' WHERE id = '"+id +"'; ")) {
		QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Delete. \nPage : showtask -> Function : on_btn_delete_clicked");
		db.close();
		return;
	}
	q.clear();
	db.close();

	Todolist * td = new Todolist();
	td->show();
	this->close();
}


void showtask::on_cb_step1_stateChanged(int arg1)
{
	if(!db.open()) {
		QMessageBox::warning(this, "Not Open Database!", "Not Successes To Open Database. \nPage : showtask -> Function : on_cb_step1_stateChanged");
		return;
	}

	QSqlQuery q;
	if(arg1) {
		QFont tmp = ui->cb_step1->font();
		tmp.setStrikeOut(true);
		ui->cb_step1->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step1 = 1 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step1's state. \nPage : showtask -> Function : on_cb_step1_stateChanged");
			db.close();
			return;
		}
	}
	else {
		QFont tmp = ui->cb_step1->font();
		tmp.setStrikeOut(false);
		ui->cb_step1->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step1 = 0 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step1's state. \nPage : showtask -> Function : on_cb_step1_stateChanged");
			db.close();
			return;
		}
	}
	q.clear();
	db.close();
}


void showtask::on_cb_step2_stateChanged(int arg1)
{
	if(!db.open()) {
		QMessageBox::warning(this, "Not Open Database!", "Not Successes To Open Database. \nPage : showtask -> Function : on_cb_step2_stateChanged");
		return;
	}

	QSqlQuery q;
	if(arg1) {
		QFont tmp = ui->cb_step2->font();
		tmp.setStrikeOut(true);
		ui->cb_step2->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step2 = 1 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step2's state. \nPage : showtask -> Function : on_cb_step2_stateChanged");
			db.close();
			return;
		}
	}
	else {
		QFont tmp = ui->cb_step2->font();
		tmp.setStrikeOut(false);
		ui->cb_step2->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step2 = 0 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step2's state. \nPage : showtask -> Function : on_cb_step2_stateChanged");
			db.close();
			return;
		}
	}
	q.clear();
	db.close();
}


void showtask::on_cb_step3_stateChanged(int arg1)
{
	if(!db.open()) {
		QMessageBox::warning(this, "Not Open Database!", "Not Successes To Open Database. \nPage : showtask -> Function : on_cb_step3_stateChanged");
		return;
	}

	QSqlQuery q;
	if(arg1) {
		QFont tmp = ui->cb_step3->font();
		tmp.setStrikeOut(true);
		ui->cb_step3->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step3 = 1 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step3's state. \nPage : showtask -> Function : on_cb_step3_stateChanged");
			db.close();
			return;
		}
	}
	else {
		QFont tmp = ui->cb_step3->font();
		tmp.setStrikeOut(false);
		ui->cb_step3->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step3 = 0 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step3's state. \nPage : showtask -> Function : on_cb_step3_stateChanged");
			db.close();
			return;
		}
	}
	q.clear();
	db.close();
}


void showtask::on_cb_step4_stateChanged(int arg1)
{
	if(!db.open()) {
		QMessageBox::warning(this, "Not Open Database!", "Not Successes To Open Database. \nPage : showtask -> Function : on_cb_step4_stateChanged");
		return;
	}

	QSqlQuery q;
	if(arg1) {
		QFont tmp = ui->cb_step4->font();
		tmp.setStrikeOut(true);
		ui->cb_step4->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step4 = 1 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step4's state. \nPage : showtask -> Function : on_cb_step4_stateChanged");
			db.close();
			return;
		}
	}
	else {
		QFont tmp = ui->cb_step4->font();
		tmp.setStrikeOut(false);
		ui->cb_step4->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step4 = 0 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step4's state. \nPage : showtask -> Function : on_cb_step4_stateChanged");
			db.close();
			return;
		}
	}
	q.clear();
	db.close();
}


void showtask::on_cb_step5_stateChanged(int arg1)
{
	if(!db.open()) {
		QMessageBox::warning(this, "Not Open Database!", "Not Successes To Open Database. \nPage : showtask -> Function : on_cb_step5_stateChanged");
		return;
	}

	QSqlQuery q;
	if(arg1) {
		QFont tmp = ui->cb_step5->font();
		tmp.setStrikeOut(true);
		ui->cb_step5->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step5 = 1 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step5's state. \nPage : showtask -> Function : on_cb_step5_stateChanged");
			db.close();
			return;
		}
	}
	else {
		QFont tmp = ui->cb_step5->font();
		tmp.setStrikeOut(false);
		ui->cb_step5->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step5 = 0 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step5's state. \nPage : showtask -> Function : on_cb_step5_stateChanged");
			db.close();
			return;
		}
	}
	q.clear();
	db.close();
}


void showtask::on_cb_step6_stateChanged(int arg1)
{
	if(!db.open()) {
		QMessageBox::warning(this, "Not Open Database!", "Not Successes To Open Database. \nPage : showtask -> Function : on_cb_step6_stateChanged");
		return;
	}

	QSqlQuery q;
	if(arg1) {
		QFont tmp = ui->cb_step6->font();
		tmp.setStrikeOut(true);
		ui->cb_step6->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step6 = 1 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step6's state. \nPage : showtask -> Function : on_cb_step6_stateChanged");
			db.close();
			return;
		}
	}
	else {
		QFont tmp = ui->cb_step6->font();
		tmp.setStrikeOut(false);
		ui->cb_step6->setFont(tmp);
		if(!q.exec("UPDATE '"+username +"' SET do_step6 = 0 WHERE id = '"+id +"';")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Change step6's state. \nPage : showtask -> Function : on_cb_step6_stateChanged");
			db.close();
			return;
		}
	}
	q.clear();
	db.close();
}


void showtask::on_btn_edit_clicked()
{
	addtask * ad = new addtask(true);
	ad->show();
	this->close();
}


void showtask::on_btn_back_clicked()
{
	Todolist * td = new Todolist();
	td->show();
	this->close();
}
