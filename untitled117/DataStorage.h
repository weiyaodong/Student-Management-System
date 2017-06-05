#pragma once

#include <QVariant>
#include <QSet>

inline double to_grade(double score)
{
	if (score < 60.0)
	{
		return 0.0;
	}
	if (score > 94.0)
	{
		return 5.0;
	}
	return static_cast<int>((score - 45) / 3) * 0.3;
}

class BaseObject
{
public:
	explicit BaseObject(QVariant id):id(id)
	{

//		if (mapping.contains(id))
//		{
//			assert(0);
//		}
//		mapping[id] = this;
	}
	virtual ~BaseObject(){}
	void set_id(const QVariant& id_);
	QVariant get_id() const;

	//static QMap<QVariant, BaseObject*> mapping;
//	static BaseObject* get_element_by_id(const QVariant& id)
//	{
//		if (!mapping.contains(id))
//			return nullptr;
//		return mapping[id];
//	}

private:

	//static QSet<QVariant> id_collector;

	QVariant id;
};

class Lesson;

class TimeTable
{
public:

	TimeTable();

	TimeTable(const TimeTable& time_table);

	bool check_empty() const;

	TimeTable intersection(const TimeTable& time_table) const;

	TimeTable union_(const TimeTable& time_table) const;
	QString to_qstring() const
	{
		return QString();
	}

	void add(const TimeTable& time_table);

	bool collision(const TimeTable& time_table) const;

	void set_time(int row, int column);

	double total_time() const;

private:
	int table[11][14];
};

class Lesson : public BaseObject
{
	friend class Student;
	friend class Teacher;

public:

	explicit Lesson(const QVariant& id,
		Teacher* teacher,
		const QString& name,
		const double& score,
		const int& total,
		const QSet<Student*>& students = QSet<Student*>(), 
		const TimeTable& time_table = TimeTable(), 		
		const QString& exam_time = QString(),
		const QMap<Student*, double>& grades = QMap<Student*, double>() )
		: BaseObject(id),
		  students(students),
		  teacher(teacher),
		  name(name),
		  total(total),
		  timeTable(time_table),
		  grades(grades), examTime(exam_time), maximum(0), score(score)
	{
	}

	void set_teacher(Teacher* _teacher);

	Teacher* get_teacher() const;

	void set_name(const QString& name);

	QString get_name() const;

	void set_timetable(const TimeTable& time_table);

	TimeTable get_timetable() const;

	void set_exam_time(const QString& time_table);

	QString get_exam_time() const;

	void add_student(Student* student);

	double get_grade(Student* student);

	QSet<Student*> get_all_students() const;

	double get_average_score() const;
	double get_average_grade() const;

	double get_student_total_time() const;

	double get_score() const;

	void set_score(const double& _score);

	int get_total() const
	{
		return total;
	}

	void set_total(const int& tot);

	int get_remain() const
	{
		return total - students.size();
	}


private:
	QSet<Student*> students;
	Teacher* teacher;
	QString name;
	int total;
	TimeTable timeTable;
	QMap<Student*, double> grades;
	QString examTime;
	int maximum;
	double score;
};

class Student :public BaseObject
{
public:
	friend class Lesson;

	explicit Student(const QVariant& id, 
		const QString& name,
		const QString& password): BaseObject(id), name(name), password(password)
	{}

	double get_total_score();
	double get_total_hours();
	double get_average_grade();
	bool add_lesson(Lesson* lesson);
	QSet<Lesson*> all_lessons() const;

	QString get_name() const
	{
		return name;
	}

	void set_password(const QString& password);

	bool check_password(const QString& str) const;

private:
	QString name;
	QString password;
	QSet<Lesson*> lessons;
	TimeTable timeTable;
};

class Teacher : public BaseObject
{
public:
	explicit Teacher(const QVariant& id,
		const QString& name,
		const QString& password,
		const QSet<Lesson*>& lessons = QSet<Lesson*>(), 
		const TimeTable& time_table = TimeTable())
		: BaseObject(id),
		  lessons(lessons),
		name(name),
		password(password),
		  timeTable(time_table)
	{
	}

	void set_password(const QString& str);

	bool check_password(const QString& str) const;

	bool add_lesson(Lesson* lesson);

	QString get_name() const
	{
		return name;
	}

	QSet<Lesson*> get_lessons() const;

private:
	QSet<Lesson*> lessons;
	QString name;
	QString password;
	TimeTable timeTable;
};

class Administrator:public BaseObject
{
public:
	explicit Administrator(const QVariant& id, const QString& name, const QString& password)
		: BaseObject(id),
		  name(name),
		  password(password)
	{
	}

	bool check_password(const QString& str) const
	{
		return password == str;
	}

	void set_password(const QString& new_password)
	{
		password = new_password;
	}

	QString get_name() const
	{
		return name;
	}

	void set_name(const QString& new_name)
	{
		name = new_name;
	}

private :
	QString name;
	QString password;
};

class DataStorage
{
public:

	bool read_student_file(const QString& filename);

	//student id,student name[,student password]

	bool read_teacher_file(QString filename);

	//teacher id,teacher name[,teacher password]

	bool read_lesson_file(QString filename);

	//lesson id,lesson name,teacher id,score,total num[,student id1,student id2, ...]

	bool read_admin_file(QString filename);

	// admin id,admin name[,admin password]

	void DataStorage::add_lesson(Teacher* teacher,
		const QString& name,
		const QVariant& id,
		const double& score,
		const int& total);
	void add_student(const QVariant& id, const QString& name, const QString& password);
	void add_admin(const QVariant& id, const QString& name, const QString& password);
	void add_teacher(const QVariant& id, const QString& name, const QString& password);


	Student* get_student_by_id(const QVariant& id) const;
	Teacher* get_teacher_by_id(const QVariant& id) const;
	Lesson* get_lesson_by_id(const QVariant& id) const;
	Administrator* get_admin_by_id(const QVariant& id) const;


	QMap<QVariant, Student*> student_map;
	QMap<QVariant, Teacher*> teacher_map;
	QMap<QVariant, Lesson*> lesson_map;
	QMap<QVariant, Administrator*> admin_map;

	QSet<Student*> students;
	QSet<Teacher*> teachers;
	QSet<Administrator*> admins;
	QSet<Lesson*> lessons;
};