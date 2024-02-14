#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    QFile last_user("lastUser.txt");
    last_user.open(QFile::WriteOnly | QFile::Text);
    last_user.close();

    QFile user_id("userID.txt");
    user_id.open(QFile::WriteOnly | QFile::Text);
    user_id.close();

	bool log_in = true;
    QFile lastUser("lastUser.txt");
    lastUser.open(QFile::ReadOnly | QFile::Text);
	QTextStream in(&lastUser);
	if(in.readLine().isNull())
		log_in = false;
	lastUser.close();

	if(log_in) {
		Todolist w;
		w.show();
		return a.exec();
	}
	else {
		MainWindow w;
		w.show();
		return a.exec();
	}
}
