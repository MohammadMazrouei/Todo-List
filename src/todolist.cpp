#include "todolist.h"
#include "ui_todolist.h"
#include "showtask.h"


Todolist::Todolist(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Todolist)
{
	ui->setupUi(this);

	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(addressDatabas);
	username = getUsername();

	readData(username);
	setData();
	setGroup();
}


Todolist::~Todolist()
{
	delete ui;
}


QString Todolist::getUsername() {
	QFile lastUser("lastUser.txt");
	if(!lastUser.open(QFile::ReadOnly | QFile::Text )) {
		QMessageBox::warning(this, "File Problem!", "Not Open lastUser.txt File. \nPage : todolist -> Function : getUsername");
		return "";
	}
	QTextStream in(&lastUser);
	QString username = in.readLine();
	lastUser.close();
	return username;
}


void Todolist::saveID(int id){
	QFile userID("userID.txt");
	if(!userID.open(QFile::WriteOnly | QFile::Text )) {
		QMessageBox::warning(this, "File Problme!", "Not Open userID.txt File. \nPage : todolist -> Function : saveID");
		return;
	}
	QTextStream in(&userID);
	in << id;
	userID.close();
}


bool Todolist::isDigit(QString str){
	for(int i = 0; i < str.size(); i++){
		if(str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}


void Todolist::readData(QString username)
{
	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : todolist -> Function : readData");
		return;
	}

	QSqlQuery q;
	if(!q.exec("SELECT * FROM '"+username +"';")) {
		QMessageBox::warning(this, "Query Problem!", "Not Execute Database For Read. \nPage : todolist -> Function : readData");
		db.close();
		return;
	}

	getData(q);

	q.clear();
	db.close();
}


void Todolist::setData()
{
	ui->pte_showtask1->setPlainText("");
	ui->pte_showtask2->setPlainText("");
	ui->pte_showtask3->setPlainText("");
	ui->pte_showtask4->setPlainText("");

	int num, temp = start;
	QString tmp;

	if(tasks.size() - start <= 4)
		num = tasks.size() - start;
	else
		num = 4;

	switch(num){
	case 4:
		tmp = tasks[temp+3].title + " " + tasks[temp+3].group + "\n" + tasks[temp+3].deadline + "\n"
				+ tasks[temp+3].step[0] + "\n" + tasks[temp+3].step[1];
		ui->pte_showtask4->setPlainText(tmp);
	case 3:
		tmp = tasks[temp+2].title + " " + tasks[temp+2].group + "\n" + tasks[temp+2].deadline + "\n"
				+ tasks[temp+2].step[0] + "\n" + tasks[temp+2].step[1];
		ui->pte_showtask3->setPlainText(tmp);
	case 2:
		tmp = tasks[temp+1].title + " " + tasks[temp+1].group + "\n" + tasks[temp+1].deadline + "\n"
				+ tasks[temp+1].step[0] + "\n" + tasks[temp+1].step[1];
		ui->pte_showtask2->setPlainText(tmp);
	case 1:
		tmp = tasks[temp].title + " " + tasks[temp].group + "\n" + tasks[temp].deadline + "\n"
				+ tasks[temp].step[0] + "\n" + tasks[temp].step[1];
		ui->pte_showtask1->setPlainText(tmp);
	}
}


void Todolist::getData(QSqlQuery q)
{
	while(q.next()){
		task tmp;
		tmp.id = q.value(0).toString();
		tmp.title = q.value(2).toString();
		tmp.description = q.value(3).toString();
		tmp.step[0] = q.value(4).toString();
		tmp.step[1] = q.value(5).toString();
		tmp.step[2] = q.value(6).toString();
		tmp.step[3] = q.value(7).toString();
		tmp.step[4] = q.value(8).toString();
		tmp.step[5] = q.value(9).toString();
		tmp.group = q.value(10).toString();
		tmp.note = q.value(11).toString();
		tmp.deadline = q.value(12).toString();
		tmp.createdate = q.value(13).toString();
		tmp.priority = q.value(14).toString();
		tasks.push_back(tmp);
	}
	q.clear();
}


void Todolist::setGroup()
{
	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : todolist -> Function : setGroup");
		return;
	}

	QSqlQuery q;
	if(!q.exec("SELECT groupp FROM '"+username +"' GROUP BY groupp;")) {
		QMessageBox::warning(this, "Query Problem!", "Not Execute Database For Read Categories. \nPage : todolist -> Function : setGroup");
		db.close();
		return;
	}
	while(q.next())
		cate.push_back(q.value(0).toString());
	q.clear();
	db.close();

	QString tmp = "";
	for(int i = 0; i < cate.size(); i++) {
		tmp = QString::number(i+1) + ". " + cate[i] + "\n";
		ui->pte_categories->insertPlainText(tmp);
	}
}


void Todolist::on_btn_search_clicked()
{
	tasks.clear();

	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : todolist -> Function : on_btn_search_clicked");
		return;
	}

	QString tmp = ui->le_search->text();
	tmp = "%" + tmp + "%";
	QSqlQuery q;
	if(!q.exec("SELECT * FROM '"+username +"' WHERE title LIKE '"+tmp +"' OR description LIKE '"+tmp +"' OR"
			   " step1 LIKE '"+tmp +"' OR step2 LIKE '"+tmp +"' OR step3 LIKE '"+tmp +"' OR step4 LIKE '"+tmp +"' OR "
			   "step5 LIKE '"+tmp +"' OR step6 LIKE '"+tmp +"' OR note LIKE '"+tmp +"';"))
	{
		QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Search.  \nPage : todolist -> Function : on_btn_search_clicked");
		db.close();
		return;
	}

	getData(q);
	setData();
	q.clear();
	db.close();
}


void Todolist::on_btn_reset_clicked()
{
	ui->le_search->setText("");
	ui->le_categories->setText("");
	tasks.clear();
	start = 0;
	readData(username);
	setData();
}


void Todolist::on_pte_showtask1_selectionChanged()
{
	int s = tasks.size();
	if(start + 1 > s)
		return;

	saveID(tasks[start].id.toInt());
	showtask * st = new showtask();
	st->show();
	this->close();
}


void Todolist::on_pte_showtask2_selectionChanged()
{
	int s = tasks.size();
	if(start + 2 > s)
		return;

	saveID(tasks[start+1].id.toInt());
	showtask * st = new showtask();
	st->show();
	this->close();
}


void Todolist::on_pte_showtask3_selectionChanged()
{
	int s = tasks.size();
	if(start + 3 > s)
		return;

	saveID(tasks[start+2].id.toInt());
	showtask * st = new showtask();
	st->show();
	this->close();
}


void Todolist::on_pte_showtask4_selectionChanged()
{
	int s = tasks.size();
	if(start + 4 > s)
		return;

	saveID(tasks[start+3].id.toInt());
	showtask * st = new showtask();
	st->show();
	this->close();
}


void Todolist::on_btn_setting_clicked()
{
	setting * se = new setting();
	se->show();
	this->close();
}


void Todolist::on_btn_addtask_clicked()
{
	addtask * at = new addtask();
	at->show();
	this->close();
}


void Todolist::on_btn_sortby_clicked()
{
	tasks.clear();

	QMessageBox *quiz = new QMessageBox(
				QMessageBox::Information, tr("Sort by"), tr("Select ?"),
				QMessageBox::Yes | QMessageBox::No | QMessageBox::Close |
				QMessageBox::Cancel);
	quiz->button(QMessageBox::Close)->setText(tr("Title"));
	quiz->button(QMessageBox::No)->setText(tr("Deadline"));
	quiz->button(QMessageBox::Yes)->setText(tr("Create date"));
	quiz->button(QMessageBox::Cancel)->setText(tr("Priority"));
	int result = quiz->exec();
	delete quiz;


	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : todolist -> Function : on_btn_sortby_clicked");
		return;
	}

	QSqlQuery q;
	switch(result) {
	case QMessageBox::Yes:{ // create date


		if(!q.exec("SELECT * FROM '"+username +"' ORDER BY createdate;")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Sortby Createdate. \nPage : todolist -> Function : on_btn_sortby_clicked");
			db.close();
			return;
		}
		getData(q);
		setData();
		break;
	}
	case QMessageBox::No:{ // deadline


		if(!q.exec("SELECT * FROM '"+username +"' ORDER BY deadline;")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Sortby deadline. \nPage : todolist -> Function : on_btn_sortby_clicked");
			db.close();
			return;
		}
		getData(q);
		setData();
		break;
	}
	case QMessageBox::Close:{ // title


		if(!q.exec("SELECT * FROM '"+username +"' ORDER BY title;")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Sortby Title. \nPage : todolist -> Function : on_btn_sortby_clicked");
			db.close();
			return;
		}
		getData(q);
		setData();
		break;
	}
	case QMessageBox::Cancel:{ // priority


		if(!q.exec("SELECT * FROM '"+username +"' ORDER BY priority;")) {
			QMessageBox::warning(this, "Query Problem!", "Not Execute Databas For Sortby priority. \nPage : todolist -> Function : on_btn_sortby_clicked");
			db.close();
			return;
		}
		getData(q);
		setData();
		break;
	}
	}
	q.clear();
	db.close();
}


void Todolist::on_btn_categories_clicked()
{
	tasks.clear();

	if (!db.open()) {
		QMessageBox::warning(this, "Database Problem!", "Not Successes To Open Database. \nPage : todolist -> Functino : on_btn_categories_clicked");
		return;
	}

	int tmp2 = ui->le_categories->text().toInt();
	if(tmp2 >= cate.size()+1 || tmp2 == 0 || !isDigit(QString::number(tmp2))){
		QMessageBox::warning(this, "Unvalid number", "Out of range");
		return;
	}
	QString tmp = cate[ui->le_categories->text().toInt()-1];

	QSqlQuery q;
	if(!q.exec("SELECT * FROM '"+username +"' WHERE groupp = '"+tmp +"';")) {
		QMessageBox::warning(this, "Database Problem!", "Not Execute Databas For Sort. \nPage : todolist -> Functino : on_btn_categories_clicked");
		db.close();
		return;
	}
	getData(q);
	setData();
	q.clear();
	db.close();
}


void Todolist::on_btn_pervious_clicked()
{
	if(start > 0){
		start--;
		setData();
	}
}


void Todolist::on_btn_next_clicked()
{
	if(start < tasks.size()-4){
		start++;
		setData();
	}
}


void Todolist::on_btn_first_clicked()
{
	start = 0;
	setData();
}


void Todolist::on_btn_end_clicked()
{
	if(tasks.size() <= 4)
		start = 0;
	else
		start = tasks.size() - 4;
	setData();
}
