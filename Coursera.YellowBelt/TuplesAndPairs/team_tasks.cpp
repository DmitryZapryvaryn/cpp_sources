#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

TaskStatus NextStatus(TaskStatus rhs) {
	return static_cast<TaskStatus>(static_cast<int>(rhs) + 1);
}

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		if(team_tasks.count(person))
			return team_tasks.at(person);
		else return { {} };
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		++team_tasks[person][TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count) {

		TasksInfo& person_tasks = team_tasks[person];

		TasksInfo updated_tasks;
		TasksInfo unresolved_tasks;
		for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = NextStatus(status)) {
			updated_tasks[NextStatus(status)] = task_count > person_tasks[status] ? person_tasks[status] : task_count;
			task_count -= updated_tasks[NextStatus(status)];

			unresolved_tasks[status] = person_tasks[status] - updated_tasks[NextStatus(status)];
			person_tasks[status] = updated_tasks[status] + unresolved_tasks[status];
		}

		person_tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

		RemoveZeros(updated_tasks);
		RemoveZeros(unresolved_tasks);
		RemoveZeros(person_tasks);

		return tuple(updated_tasks, unresolved_tasks);
	}

private:
	void RemoveZeros(TasksInfo& task_info) {
		vector<TaskStatus> keys_to_remove;
		for (const auto& [key, value] : task_info) {
			if (value == 0) {
				keys_to_remove.push_back(key);
			}
		}

		for (const auto& key : keys_to_remove) {
			task_info.erase(key);
		}
	}

	map<string, TasksInfo> team_tasks;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}