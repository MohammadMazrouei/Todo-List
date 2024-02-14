#include "addtask.h"
#include "ui_addtask.h"
#include "todolist.h"
#include "showtask.h"


addtask::addtask(bool edited, QWidget *parent)
	: QDialog(parent),
	ui(new Ui::addtask)
{
	ui->setupUi(this);

	edit = edited;
	username = getUsername();
	id = getID();
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(addressDatabas);

	if(edited) {
		readData();
		show_inf(inf);
	}
}


addtask::~addtask()
{
	delete ui;
}


QString addtask::getID()
{
	QFile userID("userID.txt");
	if(!userID.open(QFile::ReadOnly | QFile::Text )) {
		QMessageBox::warning(this, "File Problem!", "Not Open userID.txt File. \nPage : addtask -> Function : getID");
		return "";
	}
	QTextStream in(&userID);
	QString id = in.readLine();
	userID.close();
	return id;
}


void addtask::show_inf(task2 info)
{
	if(info.title == "")
		return ;

	ui->pte_title->setPlainText(info.title);
	ui->pte_group->setPlainText(info.group);
	ui->pte_description->setPlainText(info.description);
	ui->pte_step1->setPlainText(info.step[0]);
	ui->pte_step2->setPlainText(info.step[1]);
	ui->pte_step3->setPlainText(info.step[2]);
	ui->pte_step4->setPlainText(info.step[3]);
	ui->pte_step5->setPlainText(info.step[4]);
	ui->pte_step6->setPlainText(info.step[5]);
	ui->pte_note->setPlainText(info.note);
	if(info.priority == '1')
		ui->checkBox_1->setChecked(true);
	else if(info.priority == '2')
		ui->checkBox_2->setChecked(true);
	else if(info.priority == '3')
		ui->checkBox_3->setChecked(true);
	else if(info.priority == '4')
		ui->checkBox_4->setChecked(true);
	else if(info.priority == '5')
		ui->checkBox_5->setChecked(true);
	QString deadline = info.deadline;
	ui->pte_year->setPlainText(deadline.split('-')[0]);
	ui->pte_month->setPlainText(deadline.split('-')[1]);
	ui->pte_day->setPlainText(deadline.split('-')[2]);
	ui->pte_hour->setPlainText(deadline.split('-')[3]);
	ui->pte_minute->setPlainText(deadline.split('-')[4]);
}


void addtask::readData()
{
	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : addtask -> Functino : readData");
		return;
	}

	QSqlQuery q;
	if(!q.exec("SELECT * FROM '"+username +"' WHERE id = '"+id +"'; ")) {
		QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Read. \nPage : addtask -> Functino : readData");
		db.close();
		return;
	}
	getData(q);
	q.clear();
	db.close();
}


void addtask::getData(QSqlQuery q)
{
	while(q.next()){
		inf.title = q.value(2).toString();
		inf.description = q.value(3).toString();
		inf.step[0] = q.value(4).toString();
		inf.step[1] = q.value(5).toString();
		inf.step[2] = q.value(6).toString();
		inf.step[3] = q.value(7).toString();
		inf.step[4] = q.value(8).toString();
		inf.step[5] = q.value(9).toString();
		inf.group = q.value(10).toString();
		inf.note = q.value(11).toString();
		inf.deadline = q.value(12).toString();
		inf.createdate = q.value(13).toString();
		inf.priority = q.value(14).toString();
	}
	q.clear();
}


bool addtask::check_title()
{
	QString title = ui->pte_title->toPlainText();
	if(title.size() <= 0 || title.size() >= 40)
		return false;

	return true;
}


bool addtask::check_group()
{
	QString group = ui->pte_group->toPlainText();
	if(group.size() <= 0 || group.size() >= 20)
		return false;

	return true;
}


bool addtask::check_description()
{
	QString description = ui->pte_description->toPlainText();
	if(description.size() <= 0 || description.size() >= 200)
		return false;

	return true;
}


bool addtask::check_step1()
{
	QString step1 = ui->pte_step1->toPlainText();
	if(step1.size() > 100)
		return false;

	return true;
}


bool addtask::check_step2()
{
	QString step2 = ui->pte_step2->toPlainText();
	if(step2.size() > 100)
		return false;

	return true;
}


bool addtask::check_step3()
{
	QString step3 = ui->pte_step3->toPlainText();
	if(step3.size() > 100)
		return false;

	return true;
}


bool addtask::check_step4()
{
	QString step4 = ui->pte_step4->toPlainText();
	if(step4.size() > 100)
		return false;

	return true;
}


bool addtask::check_step5()
{
	QString step5 = ui->pte_step5->toPlainText();
	if(step5.size() > 100)
		return false;

	return true;
}


bool addtask::check_step6()
{
	QString step6 = ui->pte_step6->toPlainText();
	if(step6.size() > 100)
		return false;

	return true;
}


bool addtask::check_deadline_year()
{
	QString year = ui->pte_year->toPlainText();
	if(!isDigit(year))
		return false;
	int yearInt = year.toInt();
	if(yearInt < 1000 || yearInt > 9999)
		return false;

	return true;
}


bool addtask::check_deadline_month()
{
	QString month = ui->pte_month->toPlainText();
	if(!isDigit(month))
		return false;
	int monthInt = month.toInt();
	if(monthInt < 1 || monthInt > 12)
		return false;

	return true;
}


bool addtask::check_deadline_day()
{
	QString day = ui->pte_day->toPlainText();
	if(!isDigit(day))
		return false;
	int dayInt = day.toInt();
	if(dayInt < 1 || dayInt > 31)
		return false;

	return true;
}


bool addtask::check_deadline_hour()
{
	QString hour = ui->pte_hour->toPlainText();
	if(!isDigit(hour))
		return false;
	int hourInt = hour.toInt();
	if(hourInt < 0 || hourInt > 23)
		return false;

	return true;
}


bool addtask::check_deadline_minute()
{
	QString minute = ui->pte_minute->toPlainText();
	if(!isDigit(minute))
		return false;
	int minuteInt = minute.toInt();
	if(minuteInt < 0 || minuteInt > 59)
		return false;

	return true;
}


bool addtask::check_note()
{
	QString note = ui->pte_note->toPlainText();
	if(note.size() > 100)
		return false;

	return true;
}


bool addtask::check_priority()
{
	if(!(ui->checkBox_1->isChecked() || ui->checkBox_2->isChecked() ||
		 ui->checkBox_3->isChecked() || ui->checkBox_4->isChecked() || ui->checkBox_5->isChecked()))
		return false;

	return true;
}


QString addtask::getUsername()
{
	QFile lastUser("lastUser.txt");
	if(!lastUser.open(QFile::ReadOnly | QFile::Text )) {
		QMessageBox::warning(this, "File Problem!", "Not Execute Databas For Read. \nPage : addtask -> Functino : getUsername");
		return "";
	}
	QTextStream in(&lastUser);
	QString username = in.readLine().split(' ')[0];
	lastUser.close();
	return username;
}


bool addtask::isDigit(QString str){
	for(int i = 0; i < str.size(); i++){
		if(str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}


void addtask::on_btn_ok_clicked()
{
	// check information
	{
		if(!check_title()) {
			QMessageBox::warning(this, "Title", "Title Is Wrong!");
			return;
		}
		if(!check_group()) {
			QMessageBox::warning(this, "Group", "Group Is Wrong!");
			return;
		}
		if(!check_description()) {
			QMessageBox::warning(this, "Description", "Description Is Wrong!");
			return;
		}
		if(!check_step1()) {
			QMessageBox::warning(this, "Steps", "Step 1 Is Wrong!");
			return;
		}
		if(!check_step2()) {
			QMessageBox::warning(this, "Steps", "Step 2 Is Wrong!");
			return;
		}
		if(!check_step3()) {
			QMessageBox::warning(this, "Steps", "Step 3 Is Wrong!");
			return;
		}
		if(!check_step4()) {
			QMessageBox::warning(this, "Steps", "Step 4 Is Wrong!");
			return;
		}
		if(!check_step5()) {
			QMessageBox::warning(this, "Steps", "Step 5 Is Wrong!");
			return;
		}
		if(!check_step6()) {
			QMessageBox::warning(this, "Steps", "Step 6 Is Wrong!");
			return;
		}
		if(!check_deadline_year()) {
			QMessageBox::warning(this, "Deadline", "Deadline Year Is Wrong!");
			return;
		}
		if(!check_deadline_month()) {
			QMessageBox::warning(this, "Deadline", "Deadline Month Is Wrong!");
			return;
		}
		if(!check_deadline_day()) {
			QMessageBox::warning(this, "Deadline", "Deadline Day Is Wrong!");
			return;
		}
		if(!check_deadline_hour()) {
			QMessageBox::warning(this, "Deadline", "Deadline Hour Is Wrong!");
			return;
		}
		if(!check_deadline_minute()) {
			QMessageBox::warning(this, "Deadline", "Deadline Minute Is Wrong!");
			return;
		}
		if(!check_note()) {
			QMessageBox::warning(this, "Note", "Note Is Wrong!");
			return;
		}
		if(!check_priority()) {
			QMessageBox::warning(this, "Priority", "Select A Priority!");
			return;
		}
	}


	// receive information
	{
		inf.title = ui->pte_title->toPlainText();
		inf.group = ui->pte_group->toPlainText();
		inf.description = ui->pte_description->toPlainText();
		inf.step[0] = ui->pte_step1->toPlainText();
		inf.step[1] = ui->pte_step2->toPlainText();
		inf.step[2] = ui->pte_step3->toPlainText();
		inf.step[3] = ui->pte_step4->toPlainText();
		inf.step[4] = ui->pte_step5->toPlainText();
		inf.step[5] = ui->pte_step6->toPlainText();
		inf.note = ui->pte_note->toPlainText();
		QString deadline =  ui->pte_year->toPlainText() + "-" + ui->pte_month->toPlainText() + "-" + ui->pte_day->toPlainText() + "-" + ui->pte_hour->toPlainText() + "-" + ui->pte_minute->toPlainText();
		inf.deadline = deadline;
		QString createdate = QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm");
		inf.createdate = createdate;
	}

	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : addtask -> Functino : on_btn_ok_clicked");
		return;
	}

	QString username = getUsername();
	QString id = getID();
	QSqlQuery q;

	if(edit) {
		if(!q.exec("UPDATE '"+username +"' SET title = '"+inf.title +"', description = '"+inf.description +"', "
				   "step1 = '"+inf.step[0] +"', step2 = '"+inf.step[1] +"', step3 = '"+inf.step[2] +"', "
				   "step4 = '"+inf.step[3] +"', step5 = '"+inf.step[4] +"', step6 = '"+inf.step[5] +"', "
				   "groupp = '"+inf.group +"', note = '"+inf.note +"', deadline = '"+inf.deadline +"', "
				   "createdate = '"+inf.createdate +"', priority = '"+inf.priority +"' "
				   "WHERE id = '"+id +"'; "))
		{
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Update. \nPage : addtask -> Functino : on_btn_ok_clicked");
			db.close();
			return;
		}
		q.clear();
		db.close();

		showtask * st = new showtask();
		st->show();
		this->close();
	}

	else {

		if(!q.exec("INSERT INTO '"+username +"'(username, title, description, step1, step2, step3, "
				   "step4, step5, step6, groupp, note, deadline, createdate, priority) "
				   "VALUES('"+username +"', '"+inf.title +"', '"+inf.description +"', '"+inf.step[0] +"', "
				   " '"+inf.step[1] +"', '"+inf.step[2] +"', '"+inf.step[3] +"', '"+inf.step[4] +"', '"+inf.step[5] +"', "
				   " '"+inf.group +"', '"+inf.note +"', '"+inf.deadline +"', '"+inf.createdate +"', '"+inf.priority +"'); "))
		{
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Insert. \nPage : addtask -> Functino : on_btn_ok_clicked");
			db.close();
			return;
		}
		q.clear();
		db.close();

		Todolist * td = new Todolist();
		td->show();
		this->close();
	}
}


void addtask::on_checkBox_1_clicked()
{
	inf.priority = '1';
	ui->checkBox_2->setChecked(false);
	ui->checkBox_3->setChecked(false);
	ui->checkBox_4->setChecked(false);
	ui->checkBox_5->setChecked(false);
}


void addtask::on_checkBox_2_clicked()
{
	inf.priority = '2';
	ui->checkBox_1->setChecked(false);
	ui->checkBox_3->setChecked(false);
	ui->checkBox_4->setChecked(false);
	ui->checkBox_5->setChecked(false);
}


void addtask::on_checkBox_3_clicked()
{
	inf.priority = '3';
	ui->checkBox_1->setChecked(false);
	ui->checkBox_2->setChecked(false);
	ui->checkBox_4->setChecked(false);
	ui->checkBox_5->setChecked(false);
}


void addtask::on_checkBox_4_clicked()
{
	inf.priority = '4';
	ui->checkBox_1->setChecked(false);
	ui->checkBox_2->setChecked(false);
	ui->checkBox_3->setChecked(false);
	ui->checkBox_5->setChecked(false);
}


void addtask::on_checkBox_5_clicked()
{
	inf.priority = '5';
	ui->checkBox_1->setChecked(false);
	ui->checkBox_2->setChecked(false);
	ui->checkBox_3->setChecked(false);
	ui->checkBox_4->setChecked(false);
}


void addtask::on_btn_cancel_clicked()
{
	if(edit) {
		showtask * st = new showtask();
		st->show();
		this->close();
	}
	else {
		Todolist * td = new Todolist();
		td->show();
		this->close();
	}
}
