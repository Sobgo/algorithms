#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Point {
	double x, y;
};

class Figure {
	public:
		virtual bool contains(Point p) = 0;
};

class Rect : public Figure {
  private:
	Point top_left, bot_right;

  public:
	Rect(double x1, double y1, double x2, double y2) {
		top_left = {x1, y1};
		bot_right = {x2, y2};
	}

	bool contains(Point p) {
		return p.x > top_left.x && p.x < bot_right.x &&
			   p.y < top_left.y && p.y > bot_right.y;
	}
};

class Circle : public Figure {
  private:
	Point center;
	double radius;

  public:
	Circle(double x, double y, double r) {
		center = {x, y};
		radius = r;
	}

	bool contains(Point p) {
		return (p.x - center.x) * (p.x - center.x) +
			   (p.y - center.y) * (p.y - center.y) < radius * radius;
	}
};

class Triangle : public Figure {
  private:
	Point p1, p2, p3;

  public:
	Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
		p1 = {x1, y1};
		p2 = {x2, y2};
		p3 = {x3, y3};
	}

	bool contains(Point p) {
		double a = (p1.x - p.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p1.y - p.y);
		double b = (p2.x - p.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p.y);
		double c = (p3.x - p.x) * (p1.y - p3.y) - (p1.x - p3.x) * (p3.y - p.y);

		return (a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0);
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	char ch;
	double a, b, c, d, e, f;
	int iter = 0;

	vector < unique_ptr <Figure> > figures;

	while (cin >> ch) {
		if (ch == '*') break;

		if (ch == 'r') {
			cin >> a >> b >> c >> d;
			figures.push_back(unique_ptr <Figure> (new Rect(a, b, c, d)));
		} else if (ch == 'c') {
			cin >> a >> b >> c;
			figures.push_back(unique_ptr <Figure> (new Circle(a, b, c)));
		} else if (ch == 't') {
			cin >> a >> b >> c >> d >> e >> f;
			figures.push_back(unique_ptr <Figure> (new Triangle(a, b, c, d, e, f)));
		}
	}

	while (cin >> a >> b) {
		if (a == 9999.9 && b == 9999.9) break;

		iter++;
		int contained = 0;

		for (int i = 0; i < figures.size(); i++) {
			if (figures[i]->contains({a, b})) {
				cout << "Point " << iter << " is contained in figure " << i + 1 << "\n";
				contained++;
			}
		}

		if (!contained) cout << "Point " << iter << " is not contained in any figure\n";
	}

	return 0;
}
