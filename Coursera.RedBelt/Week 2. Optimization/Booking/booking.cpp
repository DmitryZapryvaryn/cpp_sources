//#include "../../test_runner.h"
//#include "../../profiler.h"

#include <deque>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

class BookingManager {
public:
	void Book(int64_t time, const string& hotel_name, int user_id, int room_count) {
		Adjust(time);

		event_queue.push({ hotel_name, user_id, room_count, time });
		hotel_booking[hotel_name].AddClient(user_id, room_count);
	}

	size_t GetClientCount(const string& hotel_name) const {
		if (hotel_booking.count(hotel_name) == 0) { return 0u; }
		return hotel_booking.at(hotel_name).GetUserCount();
	}

	size_t GetBookedRooms(const string& hotel_name) const {
		if (hotel_booking.count(hotel_name) == 0) { return 0u; }
		return hotel_booking.at(hotel_name).GetRoomCount();
	}
private:
	struct BookingInfo {
		string hotel_name;
		int user, room_count;
		int64_t last_time;
	};

	class HotelManager {
	public:
		HotelManager() : booked_rooms(0) {}
		void AddClient(int user_id, int room_count) {
			users_rooms[user_id] += room_count;
			booked_rooms += room_count;
		}

		void UpdateRoomCount(int user_id, int room_count) {
			if (users_rooms.count(user_id) > 0) {
				booked_rooms -= room_count;
				int& user_room_count = users_rooms[user_id];
				if ((user_room_count - room_count) <= 0) {
					users_rooms.erase(user_id);
				}
				else {
					user_room_count -= room_count;
				}
			}
		}

		size_t GetUserCount() const {
			return users_rooms.size();
		}

		size_t GetRoomCount() const {
			return booked_rooms;
		}

	private:
		map<int, int> users_rooms;
		size_t booked_rooms;
	};

	static const int time_to_live = 86400;

	queue<BookingInfo> event_queue;
	map<string, HotelManager> hotel_booking;

	void Adjust(int64_t time) {
		while (!event_queue.empty() && (time - event_queue.front().last_time) >= time_to_live) {
			auto booking_info = event_queue.front();
			hotel_booking[booking_info.hotel_name].UpdateRoomCount(booking_info.user, booking_info.room_count);
			event_queue.pop();
		}
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	BookingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;

		string hotel_name;
		if (query_type == "BOOK") {
			int64_t time;
			int user_id, room_count;
			cin >> time >> hotel_name >> user_id >> room_count;
			manager.Book(time, hotel_name, user_id, room_count);
		}
		else if (query_type == "CLIENTS") {
			cin >> hotel_name;
			cout << manager.GetClientCount(hotel_name) << "\n";
		}
		else if (query_type == "ROOMS") {
			cin >> hotel_name;
			cout << manager.GetBookedRooms(hotel_name) << "\n";
		}
	}
	return 0;
}