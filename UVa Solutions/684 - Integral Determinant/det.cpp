#include <iostream>
#include <vector>
using namespace std;

typedef long long int lli;

// clang-format off
namespace Math {
	lli gcd (lli a, lli b) { lli t; while (b != 0) { t = b; b = a % b; a = t; } return a; }
	lli lcm (lli a, lli b) { return a / gcd(a, b) * b; }
	lli pow (lli a, lli b) { lli res = 1; while (b > 0) { if (b & 1) res *= a; a *= a; b >>= 1; } return res; }
	lli abs (lli a) { return a < 0 ? -a : a; }
}
// clang-format on

class Rational {
	lli m_num, m_den;
	static void simplify(Rational &f);
	static lli gcd(Rational &f);

  public:
	Rational(lli num, lli den = 1);

	lli num() const;
	lli den() const;

	void num(lli num);
	void den(lli den);

	Rational operator-();
	Rational operator+(Rational f);
	Rational operator-(Rational f);
	Rational operator*(Rational f);
	Rational operator/(Rational f);
	bool operator==(Rational f);
	bool operator!=(Rational f);
	bool operator<(Rational f);
	bool operator>(Rational f);
	bool operator<=(Rational f);
	bool operator>=(Rational f);
};

class Matrix {
	bool m_sign;
	int m_width, m_height;
	vector<vector<Rational>> m_matrix;

  public:
	Matrix(int width, int height);
	Matrix(Matrix &m, int i, int j);

	int width() const;
	int height() const;
	bool sign() const;

	Rational get(int i, int j) const;
	void set(int i, int j, Rational f);

	void swap_rows(int i, int j);
	void add_rows(int i, int j, Rational k);

	Matrix reduced();
	Rational det();

	void print(std::ostream &out = std::cout) const;
};

std::ostream &operator<<(std::ostream &out, const Rational &f) {
	if (f.den() == 1)
		out << f.num();
	else
		out << f.num() << "|" << f.den();
	return out;
}

std::ostream &operator<<(std::ostream &out, const Matrix &m) {
	m.print(out);
	return out;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	lli temp;

	while (cin >> n) {
		if (n == 0)
			break;

		Matrix matrix(n, n);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> temp;
				matrix.set(i, j, temp);
			}
		}

		cout << matrix.det() << "\n";
	}

	cout << "*\n";
	return 0;
}

/// ------ Rational Implementation -------

lli Rational::gcd(Rational &f) {
	return Math::gcd(Math::abs(f.m_num), Math::abs(f.m_den));
}

void Rational::simplify(Rational &f) {
	if (f.m_num == 0) {
		f.m_den = 1;
		return;
	}

	if (f.m_den < 0) {
		f.m_num = -f.num();
		f.m_den = -f.den();
	}

	lli g = gcd(f);
	f.m_num /= g;
	f.m_den /= g;
}

Rational::Rational(lli num, lli den) {
	if (den < 0) {
		num = -num;
		den = -den;
	}

	if (den == 0) {
		throw "Denominator cannot be 0!";
	}

	m_num = num;
	m_den = den;

	simplify(*this);
}

lli Rational::num() const { return m_num; }
lli Rational::den() const { return m_den; }

void Rational::num(lli num) {
	m_num = num;
	simplify(*this);
}

void Rational::den(lli den) {
	if (den == 0) {
		throw "Denominator cannot be 0!";
	}

	m_den = den;
	simplify(*this);
}

Rational Rational::operator-() { return Rational(-m_num, m_den); }

Rational Rational::operator+(Rational f) {
	lli m = Math::lcm(m_den, f.m_den);
	return Rational(m_num * (m / m_den) + f.m_num * (m / f.m_den), m);
}

Rational Rational::operator-(Rational f) {
	lli m = Math::lcm(m_den, f.den());
	return Rational(m_num * (m / m_den) - f.m_num * (m / f.m_den), m);
}

Rational Rational::operator*(Rational f) {
	return Rational(m_num * f.m_num, m_den * f.m_den);
}

Rational Rational::operator/(Rational f) {
	return Rational(m_num * f.m_den, m_den * f.m_num);
}

inline bool Rational::operator==(Rational f) {
	return m_num == f.m_num && m_den == f.m_den;
}

inline bool Rational::operator!=(Rational f) {
	return m_num != f.m_num || m_den != f.m_den;
}

inline bool Rational::operator<(Rational f) {
	return m_num * f.m_den < f.m_num * m_den;
}

inline bool Rational::operator>(Rational f) {
	return m_num * f.m_den > f.m_num * m_den;
}

inline bool Rational::operator<=(Rational f) {
	return m_num * f.m_den <= f.m_num * m_den;
}

inline bool Rational::operator>=(Rational f) {
	return m_num * f.m_den >= f.m_num * m_den;
}

/// ------ Matrix Implementation -------

Matrix::Matrix(int width, int height) {
	m_width = width;
	m_height = height;
	m_sign = true;
	m_matrix = vector<vector<Rational>>(width, vector<Rational>(height, 0));
}

Matrix::Matrix(Matrix &m, int i, int j) {
	m_width = m.width() - 1;
	m_height = m.height() - 1;
	m_sign = !m.sign();
	m_matrix = vector<vector<Rational>>(m_width, vector<Rational>(m_height, 0));

	for (int k = 0; k < m_width; ++k) {
		for (int l = 0; l < m_height; ++l) {
			m_matrix[k][l] = m.get(k + (k >= i), l + (l >= j));
		}
	}
}

int Matrix::width() const { return m_width; }
int Matrix::height() const { return m_height; }
bool Matrix::sign() const { return m_sign; }

Rational Matrix::get(int i, int j) const { return m_matrix[i][j]; }
void Matrix::set(int i, int j, Rational f) { m_matrix[i][j] = f; }

void Matrix::swap_rows(int i, int j) {
	swap(m_matrix[i], m_matrix[j]);
	m_sign = !m_sign;
}

void Matrix::add_rows(int i, int j, Rational k) {
	for (int l = 0; l < m_width; ++l) {
		m_matrix[i][l] = m_matrix[i][l] + m_matrix[j][l] * k;
	}
}

Matrix Matrix::reduced() {
	Matrix m(*this);

	for (int i = 0; i < m_width; ++i) {

		// Find non-zero element in column i
		if (m.get(i, i) == 0) {
			for (int j = i + 1; j < m_width; ++j) {
				if (m.get(j, i) != 0) {
					m.swap_rows(i, j);
					break;
				}
			}
		}

		// Make all other elements in column i equal to 0
		for (int j = i + 1; j < m_width; ++j) {
			if (m.get(j, i) != 0) {
				m.add_rows(j, i, -m.get(j, i) / m.get(i, i));
			}
		}
	}

	return m;
}

Rational Matrix::det() {
	if (m_width != m_height) {
		throw "Matrix is not square!";
	}

	Matrix m = reduced();
	Rational res = 1;

	for (int i = 0; i < m.width(); ++i) {
		res = res * m.get(i, i);
	}

	if (!m.sign()) {
		res = -res;
	}

	return res;
}

void Matrix::print(std::ostream &out) const {
	for (int i = 0; i < m_width; ++i) {
		for (int j = 0; j < m_height; ++j) {
			out << m_matrix[i][j] << " ";
		}
		out << "\n";
	}
}
