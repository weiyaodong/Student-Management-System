#include "studentmainwindow.h"
#include "ui_studentmainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QFileDialog>

StudentMainWindow::StudentMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentMainWindow)
{
	set_up_file_readin_widget();
 	
}

StudentMainWindow::~StudentMainWindow()
{
    delete ui;
}

void StudentMainWindow::set_up_file_readin_widget()
{
	dataReadinWidget = new QWidget;
	dataReadinWidget->setWindowModality(Qt::ApplicationModal);
	dataReadinWidget->setFixedSize(700, 400);
	dataReadinWidget->setWindowTitle("Read File!");

	dataReadinAdminHBoxLayout = new QHBoxLayout;
	dataReadinStudentHBoxLayout = new QHBoxLayout;
	dataReadinTeacherHBoxLayout = new QHBoxLayout;
	dataReadinLessonsHBoxLayout = new QHBoxLayout;
	dataReadinOperateHBoxLayout = new QHBoxLayout;
	dataReadinVBoxLayout = new QVBoxLayout;

	dataReadinStudentLabel1 = new QLabel("Student File name:");
	dataReadinStudentLabel2 = new QLabel(QCoreApplication::applicationDirPath() + "/student.txt");
	dataReadinTeacherLabel1 = new QLabel("Teacher File name:");
	dataReadinTeacherLabel2 = new QLabel(QCoreApplication::applicationDirPath() + "/teacher.txt");
	dataReadinAdminLabel1 = new QLabel("Admin File name:");
	dataReadinAdminLabel2 = new QLabel(QCoreApplication::applicationDirPath() + "/admin.txt");
	dataReadinLessonsLabel1 = new QLabel("Lessons File name:");
	dataReadinLessonsLabel2 = new QLabel(QCoreApplication::applicationDirPath() + "/lessons.txt");

	dataReadinStudentButton = new QPushButton("View File");
	dataReadinTeacherButton = new QPushButton("View File");
	dataReadinAdminButton = new QPushButton("View File");
	dataReadinLessonsButton = new QPushButton("View File");

	dataReadinStudentHBoxLayout->addWidget(dataReadinStudentLabel1);
	dataReadinStudentHBoxLayout->addWidget(dataReadinStudentLabel2);
	dataReadinStudentHBoxLayout->addWidget(dataReadinStudentButton);

	dataReadinTeacherHBoxLayout->addWidget(dataReadinTeacherLabel1);
	dataReadinTeacherHBoxLayout->addWidget(dataReadinTeacherLabel2);
	dataReadinTeacherHBoxLayout->addWidget(dataReadinTeacherButton);

	dataReadinAdminHBoxLayout->addWidget(dataReadinAdminLabel1);
	dataReadinAdminHBoxLayout->addWidget(dataReadinAdminLabel2);
	dataReadinAdminHBoxLayout->addWidget(dataReadinAdminButton);

	dataReadinLessonsHBoxLayout->addWidget(dataReadinLessonsLabel1);
	dataReadinLessonsHBoxLayout->addWidget(dataReadinLessonsLabel2);
	dataReadinLessonsHBoxLayout->addWidget(dataReadinLessonsButton);

	dataReadinQuitButton = new QPushButton("Quit!");
	dataReadinEnterButton = new QPushButton("Enter!");

	dataReadinOperateHBoxLayout->addWidget(dataReadinQuitButton);
	dataReadinOperateHBoxLayout->addWidget(dataReadinEnterButton);

	dataReadinVBoxLayout->addLayout(dataReadinStudentHBoxLayout);
	dataReadinVBoxLayout->addLayout(dataReadinTeacherHBoxLayout);
	dataReadinVBoxLayout->addLayout(dataReadinAdminHBoxLayout);
	dataReadinVBoxLayout->addLayout(dataReadinLessonsHBoxLayout);
	dataReadinVBoxLayout->addLayout(dataReadinOperateHBoxLayout);

	dataReadinWidget->setLayout(dataReadinVBoxLayout);

	connect(dataReadinStudentButton, SIGNAL(clicked()), this, SLOT(dataReadinStudentButtonClicked()));
	connect(dataReadinTeacherButton, SIGNAL(clicked()), this, SLOT(dataReadinTeacherButtonClicked()));
	connect(dataReadinAdminButton, SIGNAL(clicked()), this, SLOT(dataReadinAdminButtonClicked()));
	connect(dataReadinLessonsButton, SIGNAL(clicked()), this, SLOT(dataReadinLessonsButtonClicked()));

	connect(dataReadinEnterButton, SIGNAL(clicked()), this, SLOT(dataReadinEnterButtonClicked()));
	connect(dataReadinQuitButton, SIGNAL(clicked()), this, SLOT(dataReadinQuitButtonClicked()));

	dataReadinWidget->show();
}

void StudentMainWindow::set_login_tab_widget()
{
	loginTabWidget = new QTabWidget;
	loginTabWidget->addTab(create_login_widget(STUDENT), "student login");
	loginTabWidget->addTab(create_login_widget(TEACHER), "teacher login");
	loginTabWidget->addTab(create_login_widget(ADMINISTRATOR), "admin login");
	loginTabWidget->setWindowFlags(loginTabWidget->windowFlags() & ~Qt::WindowCloseButtonHint);
}

QWidget * StudentMainWindow::create_login_widget(User_Type type)
{
	QWidget* widget = new QWidget;
	QLabel* usernameLabel = new QLabel;
	QLabel* passwordLabel = new QLabel;
	QGridLayout* gridLayout = new QGridLayout;
	QPushButton* loginButton = new QPushButton("login");
	QPushButton* quitButton = new QPushButton("quit");
	QHBoxLayout* hBoxLayout = new QHBoxLayout;
	QVBoxLayout* vBoxLayout = new QVBoxLayout;

	if(type == STUDENT)
	{
		studentLoginPasswordLineEdit = new QLineEdit;
		studentLoginUsernameLineEdit = new QLineEdit;
		studentLoginPasswordLineEdit->setEchoMode(QLineEdit::Password);
		gridLayout->addWidget(studentLoginUsernameLineEdit, 1, 2);
		gridLayout->addWidget(studentLoginPasswordLineEdit, 2, 2);
	}
	else if(type == TEACHER)
	{
		teacherLoginPasswordLineEdit = new QLineEdit;
		teacherLoginUsernameLineEdit = new QLineEdit;
		teacherLoginPasswordLineEdit->setEchoMode(QLineEdit::Password);
		gridLayout->addWidget(teacherLoginUsernameLineEdit, 1, 2);
		gridLayout->addWidget(teacherLoginPasswordLineEdit, 2, 2);
	}
	else if(type == ADMINISTRATOR)
	{
		adminLoginPasswordLineEdit = new QLineEdit;
		adminLoginUsernameLineEdit = new QLineEdit;
		adminLoginPasswordLineEdit->setEchoMode(QLineEdit::Password);
		gridLayout->addWidget(adminLoginUsernameLineEdit, 1, 2);
		gridLayout->addWidget(adminLoginPasswordLineEdit, 2, 2);
	}

	usernameLabel->setText("Number");
	passwordLabel->setText("Password");

	gridLayout->setContentsMargins(50, 100, 50, 100);
	gridLayout->setSpacing(40);
	gridLayout->addWidget(usernameLabel, 1, 1);
	gridLayout->addWidget(passwordLabel, 2, 1);

	hBoxLayout->addStretch();
	hBoxLayout->addWidget(loginButton);
	hBoxLayout->addWidget(quitButton);
	hBoxLayout->addStretch();

	vBoxLayout->addLayout(gridLayout);
	vBoxLayout->addLayout(hBoxLayout);

	widget->setLayout(vBoxLayout);

	connect(quitButton, SIGNAL(clicked()), this, SLOT(deleteLoginWidget()));

	if (type == STUDENT)
	{
		connect(loginButton, SIGNAL(clicked()), this, SLOT(studentLogin()));
	} 
	else if (type == TEACHER)
	{
		connect(loginButton, SIGNAL(clicked()), this, SLOT(teacherLogin()));
	} 
	else if (type == ADMINISTRATOR)
	{
		connect(loginButton, SIGNAL(clicked()), this, SLOT(adminLogin()));
	}

	return widget;
}

void StudentMainWindow::set_up_student_main_window()
{
	current_user_type = STUDENT;
	user_id = studentLoginUsernameLineEdit->text().toLongLong();
	window = new QTabWidget;
	window->setFixedSize(960, 640);
	window->setWindowModality(Qt::ApplicationModal);	
	cur_student = data_storage.student_map[user_id];

	window->setWindowTitle("Student: " + cur_student->get_name());

	studentChooseLessonTabWidget = new QTabWidget;

	studentViewAllLessonsTableWidget_setup();

	studentSearchLessonTab = new QWidget;

	studentSearchLessonComboBox = new QComboBox;
	studentSearchLessonComboBox->addItem("Search by name:");
	studentSearchLessonComboBox->addItem("Search by ID:");

	studentSearchLessonHBoxLayout = new QHBoxLayout;
	studentSearchLessonVBoxLayout = new QVBoxLayout;
	studentSearchLessonButton = new QPushButton("Search!");
	studentSearchLessonLabel = new QLabel("lesson name:");
	studentSearchLessonLineEdit = new QLineEdit;

	studentSearchLessonHBoxLayout->addWidget(studentSearchLessonComboBox);
	studentSearchLessonHBoxLayout->addWidget(studentSearchLessonLineEdit);
	studentSearchLessonHBoxLayout->addWidget(studentSearchLessonButton);
	studentSearchLessonVBoxLayout->addLayout(studentSearchLessonHBoxLayout);

	connect(studentSearchLessonButton, SIGNAL(clicked()), this, SLOT(studnetSearchLessonButtonClicked()));
	
	studentSearchLessonTableWidget_setup();


	studentSearchLessonTab->setLayout(studentSearchLessonVBoxLayout);
	
	studentChooseLessonTabWidget->addTab(studentSearchLessonTab, "Search Lesson");
	
	
	studentViewCurrentLessonSelectionHBoxLayout = new QHBoxLayout;
	studentViewCurrentLessonSelectionVBoxLayout = new QVBoxLayout;

	studentLeastScoreLabel = new QLabel(" Least score: 22 " );
	studentGreatestScoreLabel = new QLabel(" Greatest score: 35");
	studentChoosenScoreLabel = new QLabel(" Choosen score: ");
	studentChoosenHoursLabel = new QLabel(" Choosen hours: ");
	studentViewCurrentLessonSelectionHBoxLayout->addWidget(studentLeastScoreLabel);
	studentViewCurrentLessonSelectionHBoxLayout->addWidget(studentGreatestScoreLabel);
	studentViewCurrentLessonSelectionHBoxLayout->addWidget(studentChoosenScoreLabel);
	studentViewCurrentLessonSelectionHBoxLayout->addWidget(studentChoosenHoursLabel);

	studentViewCurrentLessonSelectionVBoxLayout->addLayout(studentViewCurrentLessonSelectionHBoxLayout);
	
	studentChoosenLessonsTableWidget_setup();

	studentViewCurrentLessonSelectionTab = new QWidget;
	studentViewCurrentLessonSelectionTab->setLayout(studentViewCurrentLessonSelectionVBoxLayout);
	studentChooseLessonTabWidget->addTab(studentViewCurrentLessonSelectionTab, "View Current Score");
	window->addTab(studentChooseLessonTabWidget, "Choose Lesson");
	
	studentViewTimeTableTab_setup();
	
	studentGradeQueryingTab = new QWidget;
	studentGradeQueryingHBoxLayout = new QHBoxLayout;
	studentGradeQueryingLabel = new QLabel("Enter your password");
	studentGradeQueryingLineEdit = new QLineEdit;
	studentGradeQueryingButton = new QPushButton("Enter");
	studentGradeQueryingHBoxLayout->addWidget(studentGradeQueryingLabel);
	studentGradeQueryingHBoxLayout->addWidget(studentGradeQueryingLineEdit);
	studentGradeQueryingHBoxLayout->addWidget(studentGradeQueryingButton);;

	connect(studentGradeQueryingButton, SIGNAL(clicked()), this, SLOT(studentGradeQueryingButtonClicked()));

	studentGradeQueryingVBoxLayout = new QVBoxLayout;

	studentGradeQueryingVBoxLayout->addLayout(studentGradeQueryingHBoxLayout);
	studentGradeQueryingResult_setup();
	studentGradeQueryingTab->setLayout(studentGradeQueryingVBoxLayout);
	window->addTab(studentGradeQueryingTab, "Grade Querying");
	
	studentAccountManageTab = new QWidget;

	studentAccountLogoutButton = new QPushButton("Logout!", studentAccountManageTab);
	studentAccountChangePasswordButton = new QPushButton("change password!", studentAccountManageTab);
	studentAccountLogoutButton->setGeometry(370, 270, 170, 30);
	studentAccountChangePasswordButton->setGeometry(370, 320, 170, 30);

	connect(studentAccountLogoutButton, SIGNAL(clicked()), this, SLOT(logout()));
	connect(studentAccountChangePasswordButton, SIGNAL(clicked()), this, SLOT(showChangePasswordWidget()));

	window->addTab(studentAccountManageTab, "Account Management");


	window->show();


}

void StudentMainWindow::set_up_teacher_main_window()
{
	current_user_type = TEACHER;
	window = new QTabWidget;
	window->setFixedSize(960, 640);
	window->setWindowModality(Qt::ApplicationModal);

	teacherViewTimeTableWidget_setup();

	teacherSetGradeTab = new QWidget;
	teacherSetGradeChooseLessonLabel = new QLabel("Choose Lesson");
	teacherSetGradeChooseLessonButton = new QPushButton("Choose");
	teacherSetGradeVBoxLayout = new QVBoxLayout;
	teacherSetGradeHBoxLayout = new QHBoxLayout;
	teacherSetGradeChooseLessonComboBox = new QComboBox;

	teacherSetGradeTableWidget_setup();
	
	teacherSetGradeChooseLessonButton->setFixedWidth(100);
	teacherSetGradeChooseLessonLabel->setFixedWidth(110);

	teacherSetGradeHBoxLayout->addWidget(teacherSetGradeChooseLessonLabel);
	teacherSetGradeHBoxLayout->addWidget(teacherSetGradeChooseLessonComboBox);
	teacherSetGradeHBoxLayout->addWidget(teacherSetGradeChooseLessonButton);

	connect(teacherSetGradeChooseLessonButton, SIGNAL(clicked()), this, SLOT(teacherSetGradeShowLesson()));

	teacherSetGradeVBoxLayout->addLayout(teacherSetGradeHBoxLayout);	
	teacherSetGradeVBoxLayout->addWidget(teacherSetGradeTableWidget);
	
	teacherSetGradeTab->setLayout(teacherSetGradeVBoxLayout);
	window->addTab(teacherSetGradeTab, "Set Grade");
	
	teacherAccountManageTab = new QWidget;

	teacherAccountLogoutButton = new QPushButton("Logout!", teacherAccountManageTab);
	teacherAccountChangePasswordButton = new QPushButton("change password!", teacherAccountManageTab);
	teacherAccountLogoutButton->setGeometry(370, 270, 170, 30);
	teacherAccountChangePasswordButton->setGeometry(370, 320, 170, 30);

	connect(teacherAccountLogoutButton, SIGNAL(clicked()), this, SLOT(logout()));
	connect(teacherAccountChangePasswordButton, SIGNAL(clicked()), this, SLOT(showChangePasswordWidget()));


	window->addTab(teacherAccountManageTab, "Account Manage");

	cur_teacher = data_storage.teacher_map[user_id];

	window->setWindowTitle("Teacher: " + cur_teacher->get_name());

	window->show();
}

void StudentMainWindow::set_up_admin_main_window()
{
	current_user_type = ADMINISTRATOR;
	
	window = new QTabWidget;
	window->setFixedSize(960, 640);
	window->setWindowModality(Qt::ApplicationModal);
	cur_admin = data_storage.admin_map[user_id];
	window->setWindowTitle("Administrator: " + cur_admin->get_name());
	adminSearchStudentTab_setup();
	adminSearchTeacherTab_setup();
	adminSearchLessonTab_setup();
	adminAccountManagementTab_setup();

	window->show();
}

bool StudentMainWindow::check_student_existence(const QString& id) const
{
	QVariant current_id = id.toLongLong();
	if (data_storage.student_map.contains(id))
	{
		return true;
	}
	return false;
}

bool StudentMainWindow::check_teacher_existence(const QString& id) const
{
	QVariant current_id = id.toLongLong();
	if (data_storage.teacher_map.contains(id))
	{
		return true;
	}
	return false;
}

bool StudentMainWindow::check_lessons_existence(const QString& id) const
{
	QVariant current_id = id.toLongLong();
	if (data_storage.lesson_map.contains(id))
	{
		return true;
	}
	return false;
}

bool StudentMainWindow::check_admin_existence(const QString& id) const
{
	QVariant current_id = id.toLongLong();
	if (data_storage.admin_map.contains(id))
	{
		return true;
	}
	return false;
}

void StudentMainWindow::studentLogin()
{
	if(check_student_existence(studentLoginUsernameLineEdit->text()))
	{
		if(!check_student_password_correctness(studentLoginUsernameLineEdit->text(), studentLoginPasswordLineEdit->text()))
		{
			QMessageBox::critical(nullptr, "Error", "password wrong!", QMessageBox::Yes);
			return;
		}		
	}
	else
	{
		QMessageBox::critical(nullptr, "Error", "No such student!", QMessageBox::Yes);
		return;
	}
	username = studentLoginUsernameLineEdit->text();
	studentLoginPasswordLineEdit->clear();
	set_up_student_main_window();

}

void StudentMainWindow::teacherLogin()
{
	if (check_teacher_existence(teacherLoginUsernameLineEdit->text()))
	{
		if (!check_teacher_password_correctness(teacherLoginUsernameLineEdit->text(), teacherLoginPasswordLineEdit->text()))
		{
			QMessageBox::critical(nullptr, "Error", "password wrong!", QMessageBox::Yes);
			return;
		}
	}
	else
	{
		QMessageBox::critical(nullptr, "Error", "No such teacher!", QMessageBox::Yes);
		return;
	}

	username = teacherLoginUsernameLineEdit->text();
	teacherLoginPasswordLineEdit->clear();
	set_up_teacher_main_window();
}

void StudentMainWindow::adminLogin()
{
	if (check_admin_existence(adminLoginUsernameLineEdit->text()))
	{
		if (!check_admin_password_correctness(adminLoginUsernameLineEdit->text(), adminLoginPasswordLineEdit->text()))
		{
			QMessageBox::critical(nullptr, "Error", "password wrong!", QMessageBox::Yes);
			return;
		}
	}
	else
	{
		QMessageBox::critical(nullptr, "Error", "No such admin!", QMessageBox::Yes);
		return;
	}
	username = adminLoginUsernameLineEdit->text();
	adminLoginPasswordLineEdit->clear();
	set_up_admin_main_window();
}

void StudentMainWindow::studentGradeQueryingButtonClicked()
{
	if (!check_student_password_correctness(username, studentGradeQueryingLineEdit->text()))
	{
		QMessageBox::critical(nullptr, "Error", "password wrong!", QMessageBox::Yes);
	}
	else
	{
		// todo
		
	}
}

void StudentMainWindow::studentSearchLessonButtonClicked()
{
	// todo
	if (studentSearchLessonComboBox->currentIndex() == 0)
	{
		// search by name
	}
	else
	{
		// search by id
		QString querying_string = studentSearchLessonLineEdit->text();
		if (querying_string.isEmpty())
		{

		}
		else
		{

		}
	}
}

void StudentMainWindow::studentViewAllLessonsDoubleClicked(int row, int column)
{
	// todo
}

void StudentMainWindow::studentSearchLessonDoubleClicked(int row, int column)
{
	// todo
}

void StudentMainWindow::studentChoosenLessonsDoubleClicked(int row, int column)
{
	// todo
}

void StudentMainWindow::teacherSetGradeShowLesson()
{
	// todo
}

void StudentMainWindow::teacherSetGradeCellDoubleClicked(int row, int column)
{
	// todo
}

void StudentMainWindow::adminSearchStudentButtonClicked()
{
	if(adminSearchStudentLineEdit->text().isEmpty())
	{
		// TODO
	}
	else
	{
		// todo
	}
}

void StudentMainWindow::adminAddStudentButtonClicked()
{
	// todo
}

void StudentMainWindow::adminSearchStudentResultDoubleClicked(int row, int column)
{
	// todo
}

void StudentMainWindow::adminSearchTeacherButtonClicked()
{
	// todo
}

void StudentMainWindow::adminAddTeacherButtonClicked()
{
	// todo
}

void StudentMainWindow::adminSearchTeacherResultDoubleClicked(int row, int column)
{
	// todo
}

void StudentMainWindow::adminSearchLessonButtonClicked()
{
	// todo
}

void StudentMainWindow::adminAddLessonButtonClicked()
{
	// todo
}

void StudentMainWindow::adminSearchLessonResultDoubleClicked(int row, int column)
{
	// todo
}

void StudentMainWindow::logout()
{
	delete window;
}

void StudentMainWindow::showChangePasswordWidget()
{
	changePasswordWidget = new QWidget;
	changePasswordVBoxLayout = new QVBoxLayout;
	currentPasswordLineEdit = new QLineEdit;
	newPasswordLineEdit = new QLineEdit;
	confirmNewPasswordLineEdit = new QLineEdit;

	currentPasswordLineEdit->setEchoMode(QLineEdit::Password);
	newPasswordLineEdit->setEchoMode(QLineEdit::Password);
	confirmNewPasswordLineEdit->setEchoMode(QLineEdit::Password);

	currentPasswordLabel = new QLabel("Current Password: ");
	newPasswordLabel = new QLabel("New Password: ");
	confirmNewPasswordLabel = new QLabel("Confirm New Password: ");
	changePasswordHintLabel = new QLabel;

	changePasswordGridLayout = new QGridLayout;
	changePasswordButton = new QPushButton("Change!");

	changePasswordGridLayout->addWidget(currentPasswordLabel, 0, 0);
	changePasswordGridLayout->addWidget(newPasswordLabel, 1, 0);
	changePasswordGridLayout->addWidget(confirmNewPasswordLabel, 2, 0);
	changePasswordGridLayout->addWidget(currentPasswordLineEdit, 0, 1);
	changePasswordGridLayout->addWidget(newPasswordLineEdit, 1, 1);
	changePasswordGridLayout->addWidget(confirmNewPasswordLineEdit, 2, 1);
	changePasswordGridLayout->addWidget(changePasswordHintLabel, 3, 0, 1, 2);
	changePasswordGridLayout->addWidget(changePasswordButton, 4, 0, 1, 2);

	changePasswordWidget->setLayout(changePasswordGridLayout);
	//changePasswordWidget->setFixedSize(300, 300);
	changePasswordWidget->setWindowTitle("Change Password");

	connect(changePasswordButton, SIGNAL(clicked()), this, SLOT(changePassword()));
	connect(newPasswordLineEdit, SIGNAL(editingFinished()), 
		this, SLOT(changePasswordHint()));
	connect(confirmNewPasswordLineEdit, SIGNAL(editingFinished()), 
		this, SLOT(changePasswordHint()));
	 
	changePasswordWidget->setWindowModality(Qt::ApplicationModal);
	changePasswordWidget->show();

}

void StudentMainWindow::changePasswordHint()
{
	//qDebug() << "fuck you" << endl;
	if (newPasswordLineEdit->text().length() < 6)
	{
		changePasswordHintLabel->setStyleSheet("QLabel{color:red;}");
		changePasswordHintLabel->setText("YOUR PASSWORD IS TOO SHORT!");
	}
	else if(newPasswordLineEdit->text().length() > 16)
	{
		changePasswordHintLabel->setStyleSheet("QLabel{color:red;}");
		changePasswordHintLabel->setText("YOUR PASSWORD IS TOO LONG!");
	}
	else if (newPasswordLineEdit->text() != confirmNewPasswordLineEdit->text())
	{
		changePasswordHintLabel->setStyleSheet("QLabel{color:red;}");
		changePasswordHintLabel->setText("CONFIRM YOUR PASSWORD!");
	}
	else
	{
		changePasswordHintLabel->setStyleSheet("QLabel{color:green;}");
		changePasswordHintLabel->setText("PASSWORD CONFIRMED!");
	}
}

void StudentMainWindow::changePassword()
{
	if (!check_student_password_correctness(username, currentPasswordLineEdit->text()))
	{
		QMessageBox::critical(nullptr, "Error", "password wrong!", QMessageBox::Yes);
	}
	// todo
}

bool StudentMainWindow::check_student_password_correctness(const QString& id, const QString& password) const
{
	QVariant current_id = id.toLongLong();
	Student* current_student = data_storage.get_student_by_id(current_id);
	if (current_student != nullptr && current_student->check_password(password))
	{
		return true;
	}
	return false;
}

bool StudentMainWindow::check_teacher_password_correctness(const QString& id, const QString& password) const
{
	QVariant current_id = id.toLongLong();
	Teacher* current_teacher = data_storage.get_teacher_by_id(current_id);
	if (current_teacher != nullptr && current_teacher->check_password(password))
	{
		return true;
	}
	return false;
}

bool StudentMainWindow::check_admin_password_correctness(const QString& id, const QString& password) const
{
	QVariant current_id = id.toLongLong();
	Administrator* current_admin = data_storage.get_admin_by_id(current_id);
	if (current_admin != nullptr && current_admin->check_password(password))
	{
		return true;
	}
	return false;
}

void StudentMainWindow::studentViewAllLessonsTableWidget_setup()
{
	studentViewAllLessonsTableWidget = new QTableWidget;
	studentChooseLessonTabWidget->addTab(studentViewAllLessonsTableWidget, "View All");
	studentViewAllLessonsTableWidget->setColumnCount(8);
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Code"));
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Time"));
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Test time"));
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Score"));
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Total"));
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Remain"));
	studentViewAllLessonsTableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Teacher"));
	
	connect(studentViewAllLessonsTableWidget, SIGNAL(cellDoubleClicked(int row, int column)), this, SLOT(studentViewAllLessonsDoubleClicked(int row, int column)));

	int counter = 0;

	for (Lesson* lesson: cur_student->all_lessons())
	{
		studentViewAllLessonsTableWidget->insertRow(++counter);
		studentViewAllLessonsTableWidget->setItem(counter, 0, new QTableWidgetItem(lesson->get_name()));
		studentViewAllLessonsTableWidget->setItem(counter, 1, new QTableWidgetItem(lesson->get_id().toString()));
		studentViewAllLessonsTableWidget->setItem(counter, 2, new QTableWidgetItem(lesson->get_timetable().to_qstring()));
		studentViewAllLessonsTableWidget->setItem(counter, 3, new QTableWidgetItem(lesson->get_exam_time()));
		studentViewAllLessonsTableWidget->setItem(counter, 4, new QTableWidgetItem(lesson->get_score()));
		studentViewAllLessonsTableWidget->setItem(counter, 5, new QTableWidgetItem(lesson->get_total()));
		studentViewAllLessonsTableWidget->setItem(counter, 6, new QTableWidgetItem(lesson->get_remain()));
		studentViewAllLessonsTableWidget->setItem(counter, 7, new QTableWidgetItem(lesson->get_teacher()->get_name()));
	}

}

void StudentMainWindow::studentSearchLessonTableWidget_setup()
{
	studentSearchLessonTableWidget = new QTableWidget;
	studentSearchLessonVBoxLayout->addWidget(studentSearchLessonTableWidget);
	studentSearchLessonTableWidget->setColumnCount(8);
	studentSearchLessonTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	studentSearchLessonTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Code"));
	studentSearchLessonTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Time"));
	studentSearchLessonTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Test time"));
	studentSearchLessonTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Score"));
	studentSearchLessonTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Total"));
	studentSearchLessonTableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("remain"));
	studentSearchLessonTableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Teacher"));

	connect(studentSearchLessonTableWidget, SIGNAL(cellDoubleClicked(int row, int column)), this, SLOT(studentSearchLessonDoubleClicked(int row, int column)));
}

void StudentMainWindow::studentChoosenLessonsTableWidget_setup()
{
	studentChoosenLessonsTableWidget = new QTableWidget;
	studentViewCurrentLessonSelectionVBoxLayout->addWidget(studentChoosenLessonsTableWidget);
	studentChoosenLessonsTableWidget->setColumnCount(8);
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Code"));
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Time"));
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Test time"));
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Score"));
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Total"));
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("remain"));
	studentChoosenLessonsTableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Teacher"));

	connect(studentChoosenLessonsTableWidget, SIGNAL(cellDoubleClicked(int row, int column)), this, SLOT(studentChoosenLessonsDoubleClicked));

}

void StudentMainWindow::studentGradeQueryingResult_setup()
{
	studentGradeQueryingResult = new QTableWidget;
	studentGradeQueryingVBoxLayout->addWidget(studentGradeQueryingResult);
	studentGradeQueryingResult->setColumnCount(5);
	studentGradeQueryingResult->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	studentGradeQueryingResult->setHorizontalHeaderItem(1, new QTableWidgetItem("Score"));
	studentGradeQueryingResult->setHorizontalHeaderItem(2, new QTableWidgetItem("Hours per week"));
	studentGradeQueryingResult->setHorizontalHeaderItem(3, new QTableWidgetItem("Result"));
	studentGradeQueryingResult->setHorizontalHeaderItem(4, new QTableWidgetItem("Grade"));
}

void StudentMainWindow::studentViewTimeTableTab_setup()
{
	studentViewTimeTableTab = new QTableWidget;
	window->addTab(studentViewTimeTableTab, "View Timetable");
	studentViewTimeTableTab->setColumnCount(14);
	studentViewTimeTableTab->setRowCount(11);
	
	for (int i = 0; i < 14; ++i)
	{
		studentViewTimeTableTab->setColumnWidth(i, 65);
	}

	for (int i = 0; i < 11; i++)
	{
		studentViewTimeTableTab->setRowHeight(i, 55);
	}

	studentViewTimeTableTab->setHorizontalHeaderItem(0, new QTableWidgetItem("Mon(O)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(1, new QTableWidgetItem("Mon(E)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(2, new QTableWidgetItem("TUE(O)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(3, new QTableWidgetItem("TUE(E)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(4, new QTableWidgetItem("WEN(O)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(5, new QTableWidgetItem("WEN(E)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(6, new QTableWidgetItem("THU(O)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(7, new QTableWidgetItem("THU(E)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(8, new QTableWidgetItem("FRI(O)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(9, new QTableWidgetItem("FRI(E)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(10, new QTableWidgetItem("SAT(O)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(11, new QTableWidgetItem("SAT(E)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(12, new QTableWidgetItem("SUN(O)"));
	studentViewTimeTableTab->setHorizontalHeaderItem(13, new QTableWidgetItem("SUN(E)"));
}

void StudentMainWindow::teacherSetGradeTableWidget_setup()
{
	teacherSetGradeTableWidget = new QTableWidget;
	connect(teacherSetGradeTableWidget, SIGNAL(cellDoubleClicked(int row, int column)), this, SLOT(teacherSetGradeCellDoubleClicked(int row, int column)));
	teacherSetGradeTableWidget->setColumnCount(4);
	teacherSetGradeTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	teacherSetGradeTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Number"));
	teacherSetGradeTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Score"));
	teacherSetGradeTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Grade"));

}

void StudentMainWindow::teacherViewTimeTableWidget_setup()
{

	teacherViewTimeTableWidget = new QTableWidget;
	
	teacherViewTimeTableWidget->setColumnCount(14);
	teacherViewTimeTableWidget->setRowCount(11);

	for (int i = 0; i < 14; ++i)
	{
		teacherViewTimeTableWidget->setColumnWidth(i, 65);
	}

	for (int i = 0; i < 11; i++)
	{
		teacherViewTimeTableWidget->setRowHeight(i, 55);
	}

	teacherViewTimeTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Mon(O)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Mon(E)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("TUE(O)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("TUE(E)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("WEN(O)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("WEN(E)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("THU(O)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("THU(E)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("FRI(O)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("FRI(E)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem("SAT(O)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(11, new QTableWidgetItem("SAT(E)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(12, new QTableWidgetItem("SUN(O)"));
	teacherViewTimeTableWidget->setHorizontalHeaderItem(13, new QTableWidgetItem("SUN(E)"));
	window->addTab(teacherViewTimeTableWidget, "View Timetable");


}

void StudentMainWindow::adminSearchStudentTab_setup()
{
	adminStudentManagementTab = new QWidget;
	window->addTab(adminStudentManagementTab, "Student Management");

	adminSearchStudentButton = new QPushButton("Search!");
	adminAddStudentButton = new QPushButton("Add Student");
	adminSearchStudentLineEdit = new QLineEdit;
	adminSearchStudentComboBox = new QComboBox;
	adminSearchStudentVBoxLayout = new QVBoxLayout;
	adminSearchStudentHBoxLayout = new QHBoxLayout;
	adminSearchStudentResultTableWidget = new QTableWidget;

	adminSearchStudentHBoxLayout->addWidget(adminSearchStudentComboBox);
	adminSearchStudentHBoxLayout->addWidget(adminSearchStudentLineEdit);
	adminSearchStudentHBoxLayout->addWidget(adminSearchStudentButton);
	adminSearchStudentHBoxLayout->addWidget(adminAddStudentButton);

	adminSearchStudentVBoxLayout->addLayout(adminSearchStudentHBoxLayout);
	adminSearchStudentVBoxLayout->addWidget(adminSearchStudentResultTableWidget);
	adminStudentManagementTab->setLayout(adminSearchStudentVBoxLayout);

	adminSearchStudentComboBox->addItem("Search by name");
	adminSearchStudentComboBox->addItem("Search by ID");
	
	connect(adminSearchStudentButton, SIGNAL(clicked()), this, SLOT(adminSearchStudentButtonClicked()));
	connect(adminSearchStudentResultTableWidget, SIGNAL(cellDoubleClicked(int row, int column)), this, SLOT(adminSearchStudentResultDoubleClicked(int row, int column)));

	adminSearchStudentResultTableWidget->setColumnCount(2);
	adminSearchStudentResultTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	adminSearchStudentResultTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("ID"));

}

void StudentMainWindow::adminSearchTeacherTab_setup()
{
	adminTeacherManagementTab = new QWidget;
	window->addTab(adminTeacherManagementTab, "Teacher Management");

	adminSearchTeacherButton = new QPushButton("Search!");
	adminAddTeacherButton = new QPushButton("Add Teacher");
	adminSearchTeacherLineEdit = new QLineEdit;
	adminSearchTeacherComboBox = new QComboBox;
	adminSearchTeacherVBoxLayout = new QVBoxLayout;
	adminSearchTeacherHBoxLayout = new QHBoxLayout;
	adminSearchTeacherResultTableWidget = new QTableWidget;

	adminSearchTeacherHBoxLayout->addWidget(adminSearchTeacherComboBox);
	adminSearchTeacherHBoxLayout->addWidget(adminSearchTeacherLineEdit);
	adminSearchTeacherHBoxLayout->addWidget(adminSearchTeacherButton);
	adminSearchTeacherHBoxLayout->addWidget(adminAddTeacherButton);

	adminSearchTeacherVBoxLayout->addLayout(adminSearchTeacherHBoxLayout);
	adminSearchTeacherVBoxLayout->addWidget(adminSearchTeacherResultTableWidget);
	adminTeacherManagementTab->setLayout(adminSearchTeacherVBoxLayout);

	adminSearchTeacherComboBox->addItem("Search by name");
	adminSearchTeacherComboBox->addItem("Search by ID");

	connect(adminSearchTeacherButton, SIGNAL(clicked()), this, SLOT(adminSearchTeacherButtonClicked()));
	connect(adminSearchTeacherResultTableWidget, SIGNAL(cellDoubleClicked(int row, int column)), this, SLOT(adminSearchTeacherResultDoubleClicked(int row, int column)));
	connect(adminAddTeacherButton, SIGNAL(clicked()), this, SLOT(adminAddTeacherButtonClicked()));

	adminSearchTeacherResultTableWidget->setColumnCount(2);
	adminSearchTeacherResultTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	adminSearchTeacherResultTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("ID"));
}

void StudentMainWindow::adminSearchLessonTab_setup()
{
	adminLessonManagementTab = new QWidget;
	window->addTab(adminLessonManagementTab, "Lesson Management");

	adminSearchLessonButton = new QPushButton("Search!");
	adminAddLessonButton = new QPushButton("Add Lesson");
	adminSearchLessonLineEdit = new QLineEdit;
	adminSearchLessonComboBox = new QComboBox;
	adminSearchLessonVBoxLayout = new QVBoxLayout;
	adminSearchLessonHBoxLayout = new QHBoxLayout;
	adminSearchLessonResultTableWidget = new QTableWidget;

	adminSearchLessonHBoxLayout->addWidget(adminSearchLessonComboBox);
	adminSearchLessonHBoxLayout->addWidget(adminSearchLessonLineEdit);
	adminSearchLessonHBoxLayout->addWidget(adminSearchLessonButton);
	adminSearchLessonHBoxLayout->addWidget(adminAddLessonButton);

	adminSearchLessonVBoxLayout->addLayout(adminSearchLessonHBoxLayout);
	adminSearchLessonVBoxLayout->addWidget(adminSearchLessonResultTableWidget);
	adminLessonManagementTab->setLayout(adminSearchLessonVBoxLayout);

	adminSearchLessonComboBox->addItem("Search by name");
	adminSearchLessonComboBox->addItem("Search by ID");

	connect(adminSearchLessonButton, SIGNAL(clicked()), this, SLOT(adminSearchLessonButtonClicked()));
	connect(adminAddLessonButton, SIGNAL(clicked()), this, SLOT(adminAddLessonButtonClicked()));
	connect(adminSearchLessonResultTableWidget, SIGNAL(cellDoubleClicked(int row, int column)), this, SLOT(adminSearchLessonResultDoubleClicked(int row, int column)));

	adminSearchLessonResultTableWidget->setColumnCount(2);
	adminSearchLessonResultTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
	adminSearchLessonResultTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("ID"));
}

void StudentMainWindow::adminAccountManagementTab_setup()
{
	adminAccountManagementTab = new QWidget;
	window->addTab(adminAccountManagementTab, "Account Management");
	
	adminAccountLogoutButton = new QPushButton("Logout", adminAccountManagementTab);
	adminAccountChangePasswordButton = new QPushButton("Change Password", adminAccountManagementTab);
	adminAccountLogoutButton->setGeometry(370, 270, 170, 30);
	adminAccountChangePasswordButton->setGeometry(370, 320, 170, 30);
	connect(adminAccountLogoutButton, SIGNAL(clicked()), this, SLOT(logout()));
	connect(adminAccountChangePasswordButton, SIGNAL(clicked()), this, SLOT(showChangePasswordWidget()));
}

void StudentMainWindow::dataReadinStudentButtonClicked() const
{
	QString fileName = QFileDialog::getOpenFileName(nullptr , tr("Open File"),nullptr,tr("txtFile (*.* *.txt)"));
	dataReadinStudentLabel2->setText(fileName);
}

void StudentMainWindow::dataReadinTeacherButtonClicked() const
{
	QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), nullptr, tr("txtFile (*.* *.txt)"));
	dataReadinTeacherLabel2->setText(fileName);
}

void StudentMainWindow::dataReadinAdminButtonClicked() const
{
	QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), nullptr, tr("txtFile (*.* *.txt)"));
	dataReadinAdminLabel2->setText(fileName);
}

void StudentMainWindow::dataReadinLessonsButtonClicked() const
{
	QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), nullptr, tr("txtFile (*.* *.txt)"));
	dataReadinLessonsLabel2->setText(fileName);
}

void StudentMainWindow::dataReadinEnterButtonClicked()
{
	if (!data_storage.read_student_file(dataReadinStudentLabel2->text()))
	{
		QMessageBox::critical(nullptr, "ERROR", "STUDENT DATA FILE FORMAT ERROR OR DOESN'T EXIST");
		return;
	}
	if(!data_storage.read_teacher_file(dataReadinTeacherLabel2->text()))
	{
		QMessageBox::critical(nullptr, "ERROR", "TEACHER DATA FILE FORMAT ERROR OR DOESN'T EXIST");
		return;
	}
	if(!data_storage.read_admin_file(dataReadinAdminLabel2->text()))
	{
		QMessageBox::critical(nullptr, "ERROR", "ADMINISTRATOR DATA FILE FORMAT ERROR OR DOESN'T EXIST");
		return;
	}
	if(!data_storage.read_lesson_file(dataReadinLessonsLabel2->text()))
	{
		QMessageBox::critical(nullptr, "ERROR", "LESSON DATA FILE FORMAT ERROR OR DOESN'T EXIST");
		return;
	}

	dataReadinWidget->close();
	set_login_tab_widget();
	loginTabWidget->setWindowTitle("Login");
	loginTabWidget->show();
}

void StudentMainWindow::dataReadinQuitButtonClicked() const
{
	//delete dataReadinWidget;
	dataReadinWidget->close();
}

void StudentMainWindow::deleteLoginWidget() const
{
	delete loginTabWidget;
}