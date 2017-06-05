#ifndef STUDENTMAINWINDOW_H
#define STUDENTMAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QtSql/QSqlDriver>
#include <QtSql/QSql>
#include <QComboBox>
#include <QString>

#include "DataStorage.h"

namespace Ui {
class StudentMainWindow;
}

class StudentMainWindow : public QMainWindow
{
    Q_OBJECT

    enum User_Type{
        STUDENT,
        TEACHER,
        ADMINISTRATOR
    };

public:
    explicit StudentMainWindow(QWidget *parent = nullptr);
    ~StudentMainWindow();

	

private:
	User_Type current_user_type;
	QString username;
	Student* cur_student;
	Teacher* cur_teacher;
	Administrator* cur_admin;

	QVariant user_id;

	DataStorage data_storage;

	QWidget* dataReadinWidget;
	QHBoxLayout* dataReadinStudentHBoxLayout;
	QHBoxLayout* dataReadinTeacherHBoxLayout;
	QHBoxLayout* dataReadinLessonsHBoxLayout;
	QHBoxLayout* dataReadinAdminHBoxLayout;
	QHBoxLayout* dataReadinOperateHBoxLayout;
	QVBoxLayout* dataReadinVBoxLayout;

	QLabel* dataReadinStudentLabel1;
	QLabel* dataReadinStudentLabel2;
	QPushButton* dataReadinStudentButton;
	
	QLabel* dataReadinTeacherLabel1;
	QLabel* dataReadinTeacherLabel2;
	QPushButton* dataReadinTeacherButton;

	QLabel* dataReadinAdminLabel1;
	QLabel* dataReadinAdminLabel2;
	QPushButton* dataReadinAdminButton;

	QLabel* dataReadinLessonsLabel1;
	QLabel* dataReadinLessonsLabel2;
	QPushButton* dataReadinLessonsButton;

	QPushButton* dataReadinQuitButton;
	QPushButton* dataReadinEnterButton;

    QTabWidget* window = nullptr;
    QTabWidget* loginTabWidget = nullptr;
	QWidget* studentLoginWidget = nullptr;
	QWidget* teacherLoginWidget = nullptr;
	QWidget* adminLoginWidget = nullptr;


	QLineEdit* studentLoginUsernameLineEdit;
	QLineEdit* studentLoginPasswordLineEdit;
	QLineEdit* teacherLoginUsernameLineEdit;
	QLineEdit* teacherLoginPasswordLineEdit;
	QLineEdit* adminLoginUsernameLineEdit;
	QLineEdit* adminLoginPasswordLineEdit;

	// STUDENT USER INTERFACE BEGIN

	QTabWidget* studentChooseLessonTabWidget;
	QTableWidget* studentViewTimeTableTab;
	

	QTableWidget* studentViewAllLessonsTableWidget;

	QWidget* studentSearchLessonTab;
	QTableWidget* studentSearchLessonTableWidget;
	QLabel* studentSearchLessonLabel;
	QComboBox* studentSearchLessonComboBox;
	QLineEdit* studentSearchLessonLineEdit;
	QPushButton* studentSearchLessonButton;
	QHBoxLayout* studentSearchLessonHBoxLayout;
	QVBoxLayout* studentSearchLessonVBoxLayout;

	QWidget* studentViewCurrentLessonSelectionTab;
	QHBoxLayout* studentViewCurrentLessonSelectionHBoxLayout;
	QVBoxLayout* studentViewCurrentLessonSelectionVBoxLayout;
	QLabel* studentLeastScoreLabel;
	QLabel* studentGreatestScoreLabel;
	QLabel* studentChoosenScoreLabel;
	QLabel* studentChoosenHoursLabel;
	QTableWidget* studentChoosenLessonsTableWidget;

	QWidget* studentGradeQueryingTab;
	QHBoxLayout* studentGradeQueryingHBoxLayout;
	QVBoxLayout* studentGradeQueryingVBoxLayout;
	QLabel* studentGradeQueryingLabel;
	QLineEdit* studentGradeQueryingLineEdit;
	QPushButton* studentGradeQueryingButton;
	QTableWidget* studentGradeQueryingResult;

	QWidget* studentAccountManageTab;
	QPushButton* studentAccountChangePasswordButton;
	QPushButton* studentAccountLogoutButton;

	QVBoxLayout* studentAccountVBoxLayout;

	// STUDENT USER INTERFACE END

	// TEACHER USER INTERFACE BEGIN

	QTableWidget* teacherViewTimeTableWidget;
	QWidget* teacherSetGradeTab;
	QWidget* teacherAccountManageTab;

	QTableWidget* teacherSetGradeTableWidget;
	QComboBox* teacherSetGradeChooseLessonComboBox;
	QLabel* teacherSetGradeChooseLessonLabel;
	QPushButton* teacherSetGradeChooseLessonButton;
	QVBoxLayout* teacherSetGradeVBoxLayout;
	QHBoxLayout* teacherSetGradeHBoxLayout;

	QPushButton* teacherAccountLogoutButton;
	QPushButton* teacherAccountChangePasswordButton;

	// TEACHER USER INTERFACE END

	// ADMINISTRATOR USER INTERFACE BEGIN

	QWidget* adminStudentManagementTab;
	QWidget* adminTeacherManagementTab;
	QWidget* adminLessonManagementTab;
	QWidget* adminAccountManagementTab;

	
	QComboBox* adminSearchStudentComboBox;
	QLineEdit* adminSearchStudentLineEdit;
	QPushButton* adminSearchStudentButton;
	QPushButton* adminAddStudentButton;
	QVBoxLayout* adminSearchStudentVBoxLayout;
	QHBoxLayout* adminSearchStudentHBoxLayout;
	QTableWidget* adminSearchStudentResultTableWidget;

	QComboBox* adminSearchTeacherComboBox;
	QLineEdit* adminSearchTeacherLineEdit;
	QPushButton* adminSearchTeacherButton;
	QPushButton* adminAddTeacherButton;
	QVBoxLayout* adminSearchTeacherVBoxLayout;
	QHBoxLayout* adminSearchTeacherHBoxLayout;
	QTableWidget* adminSearchTeacherResultTableWidget;
	
	QComboBox* adminSearchLessonComboBox;
	QLineEdit* adminSearchLessonLineEdit;
	QPushButton* adminSearchLessonButton;
	QPushButton* adminAddLessonButton;
	QVBoxLayout* adminSearchLessonVBoxLayout;
	QHBoxLayout* adminSearchLessonHBoxLayout;
	QTableWidget* adminSearchLessonResultTableWidget;

	QPushButton* adminAccountLogoutButton;
	QPushButton* adminAccountChangePasswordButton;

	// ADMINISTRATOR USER INTERFACE END

	// PASSWORD CHANGE WIDGET BEGIN

	QWidget* changePasswordWidget;
	QVBoxLayout* changePasswordVBoxLayout;
	QLineEdit* currentPasswordLineEdit;
	QLineEdit* newPasswordLineEdit;
	QLineEdit* confirmNewPasswordLineEdit;

	QLabel* currentPasswordLabel;
	QLabel* newPasswordLabel;
	QLabel* confirmNewPasswordLabel;
	QLabel* changePasswordHintLabel;

	QGridLayout* changePasswordGridLayout;
	QPushButton* changePasswordButton;

	// PASSWORD CHANGE WIDGET END

	

	//void set_window_title();

	void set_up_file_readin_widget();

	void set_login_tab_widget();

	QWidget* create_login_widget(User_Type type);
    void set_up_student_main_window();
    void set_up_teacher_main_window();
    void set_up_admin_main_window();

		

	bool check_student_existence(const QString& id) const;
	bool check_teacher_existence(const QString& id) const;
	bool check_lessons_existence(const QString& id) const;
	bool check_admin_existence(const QString& id) const;
	

	bool check_student_password_correctness(const QString& id, const QString& password) const;
	bool check_teacher_password_correctness(const QString& id, const QString& password) const;
	bool check_admin_password_correctness(const QString& id, const QString& password) const;



    Ui::StudentMainWindow *ui;

	void studentViewAllLessonsTableWidget_setup();
	void studentSearchLessonTableWidget_setup();
	void studentChoosenLessonsTableWidget_setup();
	void studentGradeQueryingResult_setup();
	void studentViewTimeTableTab_setup();

	void teacherSetGradeTableWidget_setup();
	void teacherViewTimeTableWidget_setup();

	void adminSearchStudentTab_setup();
	void adminSearchTeacherTab_setup();
	void adminSearchLessonTab_setup();
	void adminAccountManagementTab_setup();

private slots:

	void dataReadinStudentButtonClicked() const;
	void dataReadinTeacherButtonClicked() const;
	void dataReadinAdminButtonClicked() const;
	void dataReadinLessonsButtonClicked() const;

	void dataReadinEnterButtonClicked();
	void dataReadinQuitButtonClicked() const;
	

	void deleteLoginWidget() const;
	void studentLogin();
	void teacherLogin();
	void adminLogin();

	void studentGradeQueryingButtonClicked();
	void studentSearchLessonButtonClicked();

	void studentViewAllLessonsDoubleClicked(int row, int column);
	void studentSearchLessonDoubleClicked(int row, int column);
	void studentChoosenLessonsDoubleClicked(int row, int column);


	void teacherSetGradeShowLesson();
	void teacherSetGradeCellDoubleClicked(int row, int column);


	void adminSearchStudentButtonClicked();
	void adminAddStudentButtonClicked();
	void adminSearchStudentResultDoubleClicked(int row, int column);
	void adminSearchTeacherButtonClicked();
	void adminAddTeacherButtonClicked();
	void adminSearchTeacherResultDoubleClicked(int row, int column);
	void adminSearchLessonButtonClicked();
	void adminAddLessonButtonClicked();
	void adminSearchLessonResultDoubleClicked(int row, int column);

	void logout();
	void showChangePasswordWidget();
	void changePasswordHint();
	void changePassword();
};

#endif // STUDENTMAINWINDOW_H
