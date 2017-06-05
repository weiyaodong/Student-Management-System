#include "DataStorage.h"
#include <QFile>
#include <qtextstream.h>
#include <QMessageBox>

void BaseObject::set_id(const QVariant& id_)
{
	id = id_;
}

QVariant BaseObject::get_id() const
{
	return id;
}

TimeTable::TimeTable()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			table[i][j] = 0;
		}
	}
}

TimeTable::TimeTable(const TimeTable& time_table)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			table[i][j] = time_table.table[i][j];
		}
	}
}

bool TimeTable::check_empty() const
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (table[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

TimeTable TimeTable::intersection(const TimeTable& time_table) const
{
	TimeTable temp;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (time_table.table[i][j] && table[i][j])
			{
				temp.table[i][j] = 1;
			}
		}
	}
	return temp;
}

TimeTable TimeTable::union_(const TimeTable& time_table) const
{
	TimeTable temp;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (time_table.table[i][j] || table[i][j])
			{
				temp.table[i][j] = 1;
			}
		}
	}
	return temp;
}

void TimeTable::add(const TimeTable& time_table)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			table[i][j] |= time_table.table[i][j];
		}
	}
}

bool TimeTable::collision(const TimeTable& time_table) const
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (table[i][j] && time_table.table[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

void TimeTable::set_time(int row, int column)
{
	table[row][column] = 1;
}

double TimeTable::total_time() const
{
	double sum = 0.0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 14; ++j)
		{
			sum += table[i][j];
		}
	}
	sum *= 0.75;
	return sum;
}

void Lesson::set_teacher(Teacher* _teacher)
{
	teacher = _teacher;
}

Teacher* Lesson::get_teacher() const
{
	return teacher;
}

void Lesson::set_name(const QString& name)
{
	this->name = name;
}

QString Lesson::get_name() const
{
	return name;
}

void Lesson::set_timetable(const TimeTable& time_table)
{
	timeTable = time_table;
}

TimeTable Lesson::get_timetable() const
{
	return timeTable;
}

void Lesson::set_exam_time(const QString& time_table)
{
	examTime = time_table;
}

QString Lesson::get_exam_time() const
{
	return examTime;
}

void Lesson::add_student(Student* student)
{
	students.insert(student);
}

double Lesson::get_grade(Student* student)
{
	if (grades.contains(student))
	{
		return grades[student];
	}
	return -1;
}

QSet<Student*> Lesson::get_all_students() const
{
	return students;
}

double Lesson::get_average_score() const
{
	double sum = 0.0;
	int cnt = 0;
	for (Student* student: students)
	{
		if (grades.contains(student))
		{
			sum += grades[student];
			cnt += 1;
		}
	}
	return sum / cnt;
}

double Lesson::get_average_grade() const
{
	double sum = 0.0;
	int cnt = 0;
	for (Student* student : students)
	{
		if (grades.contains(student))
		{
			sum += ::to_grade(grades[student]);
			cnt += 1;
		}
	}
	return sum / cnt;
}

double Lesson::get_student_total_time() const
{
	return timeTable.total_time();
}

double Lesson::get_score() const
{
	return score;
}

void Lesson::set_score(const double& _score)
{
	score = _score;
}

void Lesson::set_total(const int& tot)
{
	total = tot;
}


double Student::get_total_score()
{
	double sum = 0.0;
	for (Lesson* lesson : lessons)
	{
		double temp = lesson->get_score();
		sum += temp;
	}
	return sum;
}

double Student::get_total_hours()
{
	double sum = 0;
	for (Lesson* lesson : lessons)
	{
		double temp = lesson->get_student_total_time();
		sum += temp;
	}
	return sum;
}

double Student::get_average_grade()
{
	double sum = 0;
	int cnt = 0;
	for (Lesson* lesson: lessons)
	{
		double temp = lesson->get_grade(this);
		if (temp != -1)
		{
			sum += temp;
			cnt += 1;
		}
	}
	return cnt == 0 ? 0 : sum / cnt;
}

bool Student::add_lesson(Lesson* lesson)
{
	if (timeTable.collision(lesson->get_timetable()))
	{
		//return false; 
	}
	timeTable.add(lesson->get_timetable());
	lessons.insert(lesson);
	return true;
}

QSet<Lesson*> Student::all_lessons() const
{
	return lessons;
}

void Student::set_password(const QString& password)
{
	this->password = password;
}

bool Student::check_password(const QString& str) const
{
	return password == str;
}

void Teacher::set_password(const QString& str)
{
	password = str;
}

bool Teacher::check_password(const QString& str) const
{
	return password == str;
}

bool Teacher::add_lesson(Lesson* lesson)
{
	if (timeTable.collision(lesson->get_timetable()))
	{
		return false;
	}
	timeTable.add(lesson->get_timetable());
	lessons.insert(lesson);
	return true;
}


QSet<Lesson*> Teacher::get_lessons() const
{
	return lessons;
}

bool DataStorage::read_student_file(const QString& filename)
{
	for (Student* student: students)
	{
		delete student;
	}
	students.clear();
	student_map.clear();
	QFile file(filename);
	if (file.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream stream(&file);
		QString line;
		do
		{			
			line = stream.readLine();
			if (!line.isEmpty())
			{
				QStringList pieces = line.split(",", QString::SkipEmptyParts);
				if (pieces.size() == 3)
				{
					Student* current_student = new Student(pieces.value(0).toLongLong(), pieces.value(1), pieces.value(2));
					students.insert(current_student);
					student_map.insert(current_student->get_id(), current_student);
				}
				else if (pieces.size() == 2)
				{
					Student* current_student = new Student(pieces.value(0).toLongLong(), pieces.value(1), "123456");
					students.insert(current_student);
					student_map.insert(current_student->get_id(), current_student);
				}
				else
				{
					return false;
				}
			}
		}
		while (!line.isEmpty());
		return true;
	}
	return false;
}

bool DataStorage::read_teacher_file(QString filename)
{
	for (Teacher* teacher: teachers)
	{
		delete teacher;
	}
	teachers.clear();
	teacher_map.clear();
	QFile file(filename);
	if (file.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream stream(&file);
		QString line;
		do
		{
			line = stream.readLine();
			if (!line.isEmpty())
			{
				QStringList pieces = line.split(",", QString::SkipEmptyParts);
				if (pieces.size() == 3)
				{
					Teacher* current_teacher = new Teacher(pieces.value(0).toLongLong(), pieces.value(1), pieces.value(2));
					teachers.insert(current_teacher);
					teacher_map.insert(current_teacher->get_id(), current_teacher);
				}
				else if (pieces.size() == 2)
				{
					Teacher* current_teacher = new Teacher(pieces.value(0).toLongLong(), pieces.value(1), "123456");
					teachers.insert(current_teacher);
					teacher_map.insert(current_teacher->get_id(), current_teacher);
				}
				else
				{
					return false;
				}
			}
		} while (!line.isEmpty());
		return true;
	}
	return false;
}

bool DataStorage::read_lesson_file(QString filename)
{
	for (Lesson* lesson: lessons)
	{
		delete lesson;
	}
	lessons.clear();
	lesson_map.clear();
	QFile file(filename);
	if (file.open(QFile::ReadOnly | QFile::Text))
	{
		QString line;
		QTextStream stream(&file);
		do
		{
			line = stream.readLine();
			if (!line.isEmpty())
			{
				QStringList pieces = line.split(",", QString::SkipEmptyParts);
				QVariant id = pieces.value(0).toLongLong();
				QString name = pieces.value(1);
				QVariant teacher_id = pieces.value(2).toLongLong();
				Teacher* teacher = get_teacher_by_id(teacher_id);
				double score = pieces.value(3).toDouble();
				int total = pieces.value(4).toInt();
				Lesson* lesson = new Lesson(id, teacher, name, score, total);
				if (teacher == nullptr)
				{
					QMessageBox::critical(nullptr, "Error", "teacher not found");
					return false;					
				}
				//QSet<Student*> students;
				for (int i = 5; i < pieces.size(); i++)
				{
					QVariant student_id = pieces.value(i).toLongLong();
					Student* student = get_student_by_id(student_id);
					if (student != nullptr)
					{
						lesson->add_student(student);
						student->add_lesson(lesson);
					}
					else
					{
						return false;
					}
				}
				teacher->add_lesson(lesson);
				lessons.insert(lesson);
				lesson_map[id] = lesson;
			}
		}
		while (!line.isEmpty());
		return true;
	}
	return false;
}

bool DataStorage::read_admin_file(QString filename)
{
	for (Administrator* admin: admins)
	{
		delete admin;
	}
	admins.clear();
	admin_map.clear();
	QFile file(filename);
	if (file.open(QFile::ReadOnly | QFile::Text))
	{
		QString line;
		QTextStream stream(&file);
		do
		{
			line = stream.readLine();
			if (!line.isEmpty())
			{
				QStringList pieces = line.split(",", QString::SkipEmptyParts);
				if (pieces.size() == 3)
				{
					Administrator* current_admin = new Administrator(pieces.value(0).toLongLong(), pieces.value(1), pieces.value(2));
					admins.insert(current_admin);
					admin_map.insert(current_admin->get_id(), current_admin);
				}
				else if (pieces.size() == 2)
				{
					Administrator* current_admin = new Administrator(pieces.value(0).toLongLong(), pieces.value(1), "123456");
					admins.insert(current_admin);
					admin_map.insert(current_admin->get_id(), current_admin);
				}
				else
				{
					return false;
				}
			}
		} while (!line.isEmpty());
		return true;
	}
	return false;
}

void DataStorage::add_lesson(Teacher* teacher, 
	const QString& name, 
	const QVariant& id, 
	const double& score,
	const int& total)
{
	Lesson* lesson = new Lesson(id, teacher, name, score, total);
	lessons.insert(lesson);
	lesson_map[id] = lesson;
	teacher->add_lesson(lesson);
}

void DataStorage::add_student(const QVariant& id, const QString& name, const QString& password)
{
	Student* student = new Student(id, name, password);
	students.insert(student);
	student_map[id] = student;
}

void DataStorage::add_admin(const QVariant& id, const QString& name, const QString& password)
{
	Administrator* admin = new Administrator(id, name, password);
	admins.insert(admin);
	admin_map[id] = admin;
}

void DataStorage::add_teacher(const QVariant& id, const QString& name, const QString& password)
{
	Teacher* teacher = new Teacher(id, name, password);
	teachers.insert(teacher);
	teacher_map[id] = teacher;
}

Student* DataStorage::get_student_by_id(const QVariant& id) const
{
	if (student_map.contains(id))
	{
		return student_map[id];
	}
	return nullptr;
}

Teacher* DataStorage::get_teacher_by_id(const QVariant& id) const
{
	if (teacher_map.contains(id))
	{
		return teacher_map[id];
	}
	return nullptr;
}

Lesson* DataStorage::get_lesson_by_id(const QVariant& id) const
{
	if (lesson_map.contains(id))
	{
		return lesson_map[id];
	}
	return nullptr;
}

Administrator* DataStorage::get_admin_by_id(const QVariant& id) const
{
	if (admin_map.contains(id))
	{
		return admin_map[id];
	}
	return nullptr;
}

