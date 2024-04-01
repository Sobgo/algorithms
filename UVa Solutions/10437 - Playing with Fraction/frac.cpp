#include <iostream>
#include <stack>

typedef long long int lli;

lli gcd (lli a, lli b) { lli t; while (b != 0) { t = b; b = a % b; a = t; } return a; }
lli lcm (lli a, lli b) { return a / gcd(a, b) * b; }
lli abs (lli a) { return a < 0 ? -a : a; }

class Frac {
	public:
	lli num, den;
	Frac(lli num, lli den = 1);
	void simplify();

	Frac operator+ (Frac f);
	Frac operator- (Frac f);
	Frac operator* (Frac f);
	Frac operator/ (Frac f);
};

std::ostream& operator<<(std::ostream& out, const Frac& f) {
	if (f.den == 1) out << f.num;
	else out << f.num << "|" << f.den;
	return out;
}

Frac eval(std::string s);

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::string s;

	while (std::getline(std::cin, s)) {
		try {
			Frac res = eval(s);
			std::cout << res << "\n";
		} catch (const char* msg) {
			std::cout << "INVALID\n";
		}
	}

	return 0;
}

// ------ Parser Implementation -------

bool isop (char &c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '|';
}

lli priority(char &op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == '|') return 3;
	return -1;
}

void process_op(std::stack <Frac> &nums, char &op) {
	Frac a = nums.top(); nums.pop();
	Frac b = nums.top(); nums.pop();

	if (op == '+') nums.push(b + a);
	if (op == '-') nums.push(b - a);
	if (op == '*') nums.push(b * a);
	if (op == '/' || op == '|') nums.push(b / a);
}

Frac eval(std::string s) {
	std::stack <Frac> nums;
	std::stack <char> ops;

	lli num = 0;
	bool add = false;

	for (char &token : s) {
		if (isdigit(token)) {
			num = num * 10 + (token - '0');
			add = true;
		}

		if (isop(token) || token == '(' || token == ')') {
			if (add) {
				nums.push(Frac(num));
				add = false;
				num = 0;
			}
		} else continue;

		if (token == '(') {
			ops.push('(');
		} else if (token == ')') {
			while (ops.top() != '(') {
				process_op(nums, ops.top());
				ops.pop();
			}
			ops.pop();
		} else {
			while (!ops.empty() && priority(ops.top()) >= priority(token)) {
				process_op(nums, ops.top());
				ops.pop();
			}
			ops.push(token);
		}
	}

	if (add) {
		nums.push(Frac(num));
	}

	while (!ops.empty()) {
		process_op(nums, ops.top());
		ops.pop();
	}

	return nums.top();
}

// ------ Frac Implementation -------

void Frac::simplify() {
	if (num == 0) {
		den = 1;
		return;
	}

	if (den < 0) {
		num = -num;
		den = -den;
	}

	lli g = gcd(abs(num), abs(den));
	num /= g;
	den /= g;
}

Frac::Frac(lli num, lli den) {
	if (den < 0) {
		num = -num;
		den = -den;
	}

	if (den == 0) {
		throw "Denominator cannot be 0!";
	}

	this->num = num;
	this->den = den;

	simplify();
	std::cout << "";
}

Frac Frac::operator+ (Frac f) {
	lli l = lcm(den, f.den);
	return Frac(num * (l / den) + f.num * (l / f.den), l);
}

Frac Frac::operator- (Frac f) {
	lli l = lcm(den, f.den);
	return Frac(num * (l / den) - f.num * (l / f.den), l);
}

Frac Frac::operator* (Frac f) {
	return Frac(num * f.num, den * f.den);
}

Frac Frac::operator/ (Frac f) {
	return Frac(num * f.den, den * f.num);
}
