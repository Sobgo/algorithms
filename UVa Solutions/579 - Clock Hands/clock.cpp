#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

using pii = pair<int, int>;

// clang-format off
map<string, pii> tz = {
	{"UTC", {0, 0}},    {"GMT", {0, 0}},   {"BST", {1, 0}},
	{"IST", {1, 0}},    {"WET", {0, 0}},   {"WEST", {1, 0}},
	{"CET", {1, 0}},    {"CEST", {2, 0}},  {"EET", {2, 0}},
	{"EEST", {3, 0}},   {"MSK", {3, 0}},   {"MSD", {4, 0}},
	{"AST", {-4, 0}},   {"ADT", {-3, 0}},  {"NST", {-3, -30}},
	{"NDT", {-2, -30}}, {"EST", {-5, 0}},  {"EDT", {-4, 0}},
	{"CST", {-6, 0}},   {"CDT", {-5, 0}},  {"MST", {-7, 0}},
	{"MDT", {-6, 0}},   {"PST", {-8, 0}},  {"PDT", {-7, 0}},
	{"HST", {-10, 0}},  {"AKST", {-9, 0}}, {"AKDT", {-8, 0}},
	{"AEST", {10, 0}},  {"AEDT", {11, 0}}, {"ACST", {9, 30}},
	{"ACDT", {10, 30}}, {"AWST", {8, 0}}
};
// clang-format on

pii shift_timezone(pii time, string tz1, string tz2) {
	time = {time.first - tz[tz1].first, time.second - tz[tz1].second};
	time = {time.first + tz[tz2].first, time.second + tz[tz2].second};

	// handle time overflows
	if (time.second < 0) {
		time.second += 60;
		time.first--;
	} else if (time.second >= 60) {
		time.second -= 60;
		time.first++;
	}

	time.first = (time.first + 24) % 24;
	return time;
}

class Time {
  private:
	// 24h format time in UTC
	pii time;

  public:
	pii get_time(string time, string timezone, bool pm = true) {
		if (time == "noon")
			return shift_timezone({12, 0}, timezone, "UTC");

		if (time == "midnight")
			return shift_timezone({0, 0}, timezone, "UTC");

		int hour = stoi(time.substr(0, time.find(':')));
		int minute = stoi(time.substr(time.find(':') + 1, 2));

		if (pm && hour != 12) {
			hour += 12;
		} else if (!pm && hour == 12) {
			hour = 0;
		}

		return shift_timezone({hour, minute}, timezone, "UTC");
	}

	double get_angle() {
		double hour_angle = time.first * 30 + time.second * 0.5;
		double minute_angle = time.second * 6;

		double angle = abs(hour_angle - minute_angle);
		if (angle > 180)
			angle = 360 - angle;

		return angle;
	}

	Time(string time, string timezone, bool ampm = false) {
		this->time = get_time(time, timezone, ampm);
	}

	void internal() { printf("%02d:%02d\n", time.first, time.second); }

	void print(string timezone) {
		time = shift_timezone(time, "UTC", timezone);

		if (time.first == 12 && time.second == 0)
			printf("noon\n");
		else if (time.first == 0 && time.second == 0)
			printf("midnight\n");
		else {
			// convert to 12h format
			int hour = time.first % 12;

			if (hour == 0)
				hour = 12;
			if (time.first >= 12)
				printf("%d:%02d p.m.\n", hour, time.second);
			else
				printf("%d:%02d a.m.\n", hour, time.second);
		}
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string time;

	while (true) {
		cin >> time;
		if (time == "0:00")
			break;

		Time t(time, "UTC", false);
		printf("%.3f\n", t.get_angle());
	}

	return 0;
}
