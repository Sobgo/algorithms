#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Team {
	public:
	string name;
	int points, wins, ties, losses, goals_scored, goals_against;
	
	Team(string name) {
		this->name = name;
		points = 0; wins = 0; ties = 0; losses = 0; goals_scored = 0; goals_against = 0;
	}

	void add_match(int goals_scored, int goals_against) {
		this->goals_scored += goals_scored;
		this->goals_against += goals_against;

		if (goals_scored > goals_against) {
			points += 3;
			wins++;
		} else if (goals_scored == goals_against) {
			points++;
			ties++;
		} else {
			losses++;
		}
	}

	void get_stats() {
		cout << points << "p, " << wins + ties + losses << "g (" << wins << "-" << ties << "-" << losses << "), ";
		cout << goals_scored - goals_against << "gd (" << goals_scored << "-" << goals_against << ")\n";
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string buff; getline(cin, buff); 
	int n = stoi(buff);

	for (int i = 0; i < n; ++i) {
		string tournament_name; getline(cin, tournament_name);
		
		getline(cin, buff); 
		int t = stoi(buff);

		map <string, int> teams;
		vector <Team> v;

		int iter = 0;

		for (int j = 0; j < t; ++j) {
			string team_name; getline(cin, team_name);
			teams[team_name] = iter++;
			v.push_back(Team(team_name));
		}

		getline(cin, buff);
		int g = stoi(buff);

		string team1, team2;
		int goals1, goals2;

		for (int j = 0; j < g; ++j) {	
			getline(cin, team1, '#');

			getline(cin, buff, '@');
			goals1 = stoi(buff);

			getline(cin, buff, '#');
			goals2 = stoi(buff);

			getline(cin, team2);

			v[teams[team1]].add_match(goals1, goals2);
			v[teams[team2]].add_match(goals2, goals1);
		}

		cout << tournament_name << "\n";

		sort(v.begin(), v.end(), [](const Team &a, const Team &b) {
			if (a.points > b.points) return true;
			if (a.points < b.points) return false;

			if (a.wins > b.wins) return true;
			if (a.wins < b.wins) return false;

			if (a.goals_scored - a.goals_against > b.goals_scored - b.goals_against) return true;
			if (a.goals_scored - a.goals_against < b.goals_scored - b.goals_against) return false;

			if (a.goals_scored > b.goals_scored) return true;
			if (a.goals_scored < b.goals_scored) return false;

			if (a.wins + a.ties + a.losses < b.wins + b.ties + b.losses) return true;
			if (a.wins + a.ties + a.losses > b.wins + b.ties + b.losses) return false;

			for (int i = 0; i < a.name.length(); ++i) {
				if (tolower(a.name[i]) < tolower(b.name[i])) return true;
				if (tolower(a.name[i]) > tolower(b.name[i])) return false;
			}

			return false;
		});

		for (int j = 0; j < v.size(); ++j) {
			cout << j + 1 << ") " << v[j].name << " ";
			v[j].get_stats();
		}

		if (i < n - 1) cout << "\n";
	}

	return 0;
}
