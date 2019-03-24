#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// ������������ ��� ��� ������� ������
enum class TaskStatus {
	NEW,          // �����
	IN_PROGRESS,  // � ����������
	TESTING,      // �� ������������
	DONE          // ���������
};

// ��������� ���-������� ��� map<TaskStatus, int>,
// ������������ ������� ���������� ����� ������� �������
using TasksInfo = map<TaskStatus, int>;

TaskStatus NextStatus(TaskStatus rhs) {
	return static_cast<TaskStatus>(static_cast<int>(rhs) + 1);
}

class TeamTasks {
public:
	// �������� ���������� �� �������� ����� ����������� ������������
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		if(team_tasks.count(person))
			return team_tasks.at(person);
		else return { {} };
	}

	// �������� ����� ������ (� ������� NEW) ��� ����������� �������������
	void AddNewTask(const string& person) {
		++team_tasks[person][TaskStatus::NEW];
	}

	// �������� ������� �� ������� ���������� ����� ����������� ������������,
	// ����������� ��. ����
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

// ��������� ������� �� ��������, ����� ����� �����������
// ���������� � ������������� ������ � ������� [] � �������� 0,
// �� ����� ��� ���� �������� �������
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}