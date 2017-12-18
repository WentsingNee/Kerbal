#include "matrix.hpp"

#include <algorithm>

#include "../String_serve.hpp"
#include <windows.h>//测试时间用的

#if __cplusplus < 201103L //C++0x
#	pragma message("\n"\
"			* Matrix 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性\n"\
"					* Matrix 为 C++ 11 准备的新特性: 转移构造函数\n"\
"					* Matrix 为 C++ 11 准备的新特性: 利用一维初始化列表进行构造\n"\
"					* Matrix 为 C++ 11 准备的新特性: 利用二维初始化列表进行构造\n"\
"					* Matrix 为 C++ 11 准备的新特性: 转移赋值运算符"\
)
#endif //C++0x

namespace kerbal
{
	namespace
	{
		using namespace std;
		using namespace _String;
	}
	using namespace array_2d;

	Matrix::Matrix() throw () :
			Array_2d<double>()
	{
	}

	Matrix::Matrix(const int row, const int column) :
			Array_2d<double>(row, column)
	{
	}

	Matrix::Matrix(const int row, const int column, const double &val) :
			Array_2d<double>(row, column, val)
	{
	}

	Matrix::Matrix(double (*function)(), const int row, const int column, bool para) :
			Array_2d<double>(function, row, column, para)
	{
	}

	Matrix::Matrix(double (*function)(int, int), const int row, const int column, bool para) :
			Array_2d<double>(function, row, column, para)
	{
	}

	Matrix::Matrix(const double arr[], int len, bool in_a_row) :
			Array_2d<double>(arr, len, in_a_row)
	{ //利用一维数组进行构造
	}

#if __cplusplus >= 201103L //C++0x
	Matrix::Matrix(std::initializer_list<std::initializer_list<double>> src) :
	Array_2d<double>(src)
	{ //利用二维初始化列表进行构造
	}

	Matrix::Matrix(std::initializer_list<double> src) :
	Array_2d<double>(src)
	{ //利用一维初始化列表进行构造
	}

	Matrix::Matrix(Matrix &&src)
	{ //转移构造函数
		row = src.row;
		column = src.column;
		p = src.p;

		src.p = NULL;
		src.row = 0;
		src.column = 0;
	}

#endif //C++0x

	Matrix::Matrix(const Matrix &src) :
			Array_2d<double>(src)
	{
	}

	Matrix::~Matrix() // virtual
	{
	}

	void Matrix::print(Frame frame, bool print_corner, std::ostream &output) const
	{
		//Frame frame 默认= Fr_RtMatrix, bool print_corner 默认= true, ostream &output = output
		int i, j;
		const string *corner = NULL;
		switch (frame) {
			case Fr_RtMatrix:
				Array_2d<double>::print(true, print_corner, output);
				return;
			case Fr_RdMatrix:
				corner = Corner_RdMatrix;
				break;
			case Fr_Det:
				corner = Corner_Det;
				break;
			case Fr_double:
				corner = Corner_double;
				break;
			case Fr_Null:
				Array_2d<double>::print(false, false, output);
				return;
		}

		output << resetiosflags(ios::right) << setiosflags(ios::left) << setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格

		output << corner[0];
		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << " ";
		}
		output << " " << corner[1] << endl;

		for (i = 0; i < row; i++) {
			output << corner[4];

			for (j = 0; j < column; j++) {
				output << "  " << setw(12) << p[i][j];
			}
			output << " " << corner[4] << endl;
		}

		output << corner[2];
		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << " ";
		}
		output << " " << corner[3];
		if (print_corner) {
			output << " " << row << " × " << column;
		}
		output << endl;
	}

	void Matrix::save(const string &file_name) const throw (std::runtime_error)
	{
		const size_t sizeof_row = sizeof(row);
		const size_t sizeof_column = sizeof(column);
		const size_t sizeof_element = sizeof(p[0][0]);

		ofstream fout(&file_name[0], ios::out | ios::binary);
		//输出位宽信息

		try {
			switch (sizeof(size_t)) {
				case 4: //size_t 32位版本
					fout.write((char*) &sizeof_row, 4); //输出变量row在内存中所占的长度
					fout.write("\0\0\0", 4); //不足8位补4个零
					fout.write((char*) &sizeof_column, 4);
					fout.write("\0\0\0", 4);
					fout.write((char*) &sizeof_element, 4);
					fout.write("\0\0\0", 4);
					break;
				case 8: //size_t 64位版本
					fout.write((char*) &sizeof_row, 8); //输出变量row在内存中所占的长度
					fout.write((char*) &sizeof_column, 8);
					fout.write((char*) &sizeof_element, 8);
					break;
				default:
					fout.close();
					throw runtime_error("不支持的位宽");
			}

			fout.write((char*) &row, sizeof(row)); //输出矩阵行数
			fout.write((char*) &column, sizeof(column)); //输出矩阵列数
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					fout.write((char*) (p[i] + j), sizeof_element); //输出矩阵元素
				}
			}
		} catch (const __cxxabiv1:: __forced_unwind &) {
			fout.close();
			throw;
		}
		fout.close();
	}

	const Matrix Matrix::load_from(const string &file_name)
	{
		ifstream fin(&file_name[0], ios::in | ios::binary);

		size_t size_of_row_in_file;
		size_t size_of_column_in_file;
		size_t size_of_ele_in_file;

		fin.read((char*) &size_of_row_in_file, 4);
		fin.ignore(4);
		fin.read((char*) &size_of_column_in_file, 4);
		fin.ignore(4);
		fin.read((char*) &size_of_ele_in_file, 4);
		fin.ignore(4);

		cout << size_of_row_in_file << endl;
		cout << size_of_column_in_file << endl;
		cout << size_of_ele_in_file << endl;

		static const size_t size_of_row = sizeof(row);
		static const size_t size_of_column = sizeof(column);
		static const size_t size_of_ele = sizeof(double);

		if (size_of_row != size_of_row_in_file

		|| size_of_column != size_of_column_in_file

		|| size_of_ele != size_of_ele_in_file) {

			throw runtime_error("位宽不兼容");

		}

		int row;
		int column;
		fin.read((char*) &row, size_of_row);
		fin.read((char*) &column, size_of_column);

		Matrix tmp(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				fin.read((char*) (tmp.p[i] + j), size_of_ele);
			}
		}
		fin.close();
		return tmp;
	}

	void Matrix::switch_rows(const int row1, const int row2) throw (out_of_range)
	{
		//交换矩阵的两行

		this->test_row(row1);
		this->test_row(row2);
		swap(p[row1], p[row2]);
	}

	void Matrix::k_multiply_a_row(const double k, const int row_dest) throw (out_of_range)
	{
		test_row(row_dest);

		for (int i = 0; i < column; i++) {
			p[row_dest][i] *= k;
		}
	}

	void Matrix::k_multiply_a_row_plus_to_another(const double k, const int row_from, const int row_dest) throw (out_of_range)
	{
		test_row(row_from);
		test_row(row_dest);

		if (k == 0.0) {
			return;
		}

		for (int i = 0; i < column; i++) {
			p[row_dest][i] += k * p[row_from][i];
		}
	}

	void Matrix::do_optimize_rows() throw (invalid_argument)
	{
		//将行列式针对行进行优化
		test_square();
		bool k = false; //是否取相反数
		const int &n = row;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n - i; j++) {

				if (p[j][0] != 0) {
					if (p[j + 1][0] == 0 || fabs(p[j][0]) < fabs(p[j + 1][0])) {
						swap(p[j], p[j + 1]);
						k = !k;
					}
				}

			}
		}

		if (p[n - 1][0] != 0) {
			for (int i = 0; i < n - 1; i++) {
				if (p[i][0] != 0.0) {
					double ra = p[i][0] / p[n - 1][0];
					for (int j = 0; j < n; j++) { //列循环
						p[i][j] -= ra * p[n - 1][j];
					}
				}
			}
		}

		if (k) { //k == true
			for (int j = 0; j < n; j++) { //列循环
				if (p[j][0])
					p[j][0] = -p[j][0];
			}
		}
	}

	void Matrix::switch_columns(const int column1, const int column2) throw (out_of_range)
	{
		this->test_column(column1);
		this->test_column(column2);

		for (int i = 0; i < row; i++) {
			swap(p[i][column1], p[i][column2]);
		}
	}

	double Matrix::Det() const throw (invalid_argument)
	{
		this->test_square();

#		define n row
		switch (n) {
			case 1:
				return p[0][0];
			case 2:
				return p[0][0] * p[1][1] - p[0][1] * p[1][0];
			case 3:
				return p[0][0] * (p[1][1] * p[2][2] - p[1][2] * p[2][1])
						- p[0][1] * (p[1][0] * p[2][2] - p[1][2] * p[2][0])
						+ p[0][2] * (p[1][0] * p[2][1] - p[1][1] * p[2][0]);
		}

		double sum = 0.0;

		if (n >= 5) { //如果代数余子式在4阶及以上, 则对代数余子式进行行优化
			for (int i = 0; i < n; i += 2) { //i为偶数
				if (p[i][0] != 0.0) { //p[0][i]!=0
					Matrix daishu = CofactorOf(*this, i, 0);
					daishu.do_optimize_rows();
					sum += p[i][0] * daishu.Det(); //i为偶数
				}
			}
			for (int i = 1; i < n; i += 2) { //i为奇数
				if (p[i][0] != 0.0) { //p[0][i]!=0
					Matrix daishu = CofactorOf(*this, i, 0);
					daishu.do_optimize_rows();
					sum -= p[i][0] * daishu.Det(); //i为奇数

				}
			}
		} else {
			for (int i = 0; i < n; i += 2) { //i为偶数
				if (p[i][0] != 0.0) { //p[0][i]!=0
					Matrix daishu = CofactorOf(*this, i, 0);
					sum += p[i][0] * daishu.Det(); //i为偶数
				}
			}
			for (int i = 1; i < n; i += 2) { //i为奇数
				if (p[i][0] != 0.0) { //p[0][i]!=0
					Matrix daishu = CofactorOf(*this, i, 0);
					sum -= p[i][0] * daishu.Det(); //i为奇数
				}
			}
		}
#		undef n
		return sum;
	}

	Matrix Matrix::Adjugate_matrix() const throw (invalid_argument)
	{
//返回本方阵的伴随矩阵

		this->test_square();
		Matrix result(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if ((i + j) % 2) {
					//i+j为奇数
					result.p[j][i] = -CofactorOf(*this, i, j).Det();
				} else {
					//i+j为偶数
					result.p[j][i] = CofactorOf(*this, i, j).Det();
				}
			}
		}
		return result;
	}

	Matrix Matrix::Inverse_matrix() const throw (invalid_argument)
	{
//返回本方阵的逆矩阵
		this->test_square();

		double D = this->Det();
		if (D == 0.0) {
			throw invalid_argument("A does not have an inverse matrix");
		}
		const double k = 1.0 / D;
		return Matrix(k * this->Adjugate_matrix());
	}

//运算符重载
	const Matrix operator+(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{ //检查A,B是否同样大小
		if (A.row != B.row) {
			throw invalid_argument("error: row(A) ≠ row(B)");
		}
		if (A.column != B.column) {
			throw invalid_argument("error: column(A) ≠ column(B)");
		}
		const int &row = A.row;
		const int &column = A.column;

		Matrix result(row, column);

		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				result.p[i][j] = A.p[i][j] + B.p[i][j];
			}
		}

		return result;
	}

	const Matrix operator-(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{ //检查A,B是否同样大小
		if (A.row != B.row) {
			throw invalid_argument("error: row(A) ≠ row(B)");
		}
		if (A.column != B.column) {
			throw invalid_argument("error: column(A) ≠ column(B)");
		}
		const int &row = A.row;
		const int &column = A.column;

		Matrix result(row, column);

		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				result.p[i][j] = A.p[i][j] - B.p[i][j];
			}
		}

		return result;
	}

	const Matrix operator*(const double k, const Matrix &A) throw ()
	{ //数k乘矩阵
		if (k == 1) {
			return A;
		}
		Matrix result(A);
		int i, j;
		for (i = 0; i < A.row; i++) {
			for (j = 0; j < A.column; j++) {
				result.p[i][j] *= k;
			}
		}
		return result;
	}

	const Matrix operator*(const Matrix &A, const double k) throw ()
	{ //矩阵乘数k
		if (k == 1) {
			return A;
		}
		Matrix result(A);
		int i, j;
		for (i = 0; i < A.row; i++) {
			for (j = 0; j < A.column; j++) {
				result.p[i][j] *= k;
			}
		}
		return result;
	}

	const Matrix operator*(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{ //矩阵乘矩阵

//检查A的列数是否等于B的行数
		if (A.column != B.row) {
			throw invalid_argument("error: column(A) ≠ row(B)");
		}
		const int &row = A.row;
		const int &column = B.column;

		Matrix result(row, column, 0);

		int i, j, k;
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				for (k = 0; k < A.column; k++) {
					result.p[i][j] += A.p[i][k] * B.p[k][j];
				}
			}
		}
//		cout << result.get_data() << endl;
		return result;
	}

	const Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C) throw (invalid_argument)
	{ // A * B + C

//检查A的列数是否等于B的行数
		if (A.column != B.row) {
			throw invalid_argument("error: column(A) ≠ row(B)");
		}
		const int &row = A.row;
		const int &column = B.column;
		if (row != C.row || column != C.column) {
			throw invalid_argument("error: size(A*B) ≠ size(C)");
		}

		Matrix result(C);

		int i, j, k;
		for (i = 0; i < row; ++i) {
			for (j = 0; j < column; ++j) {
				for (k = 0; k < A.column; ++k) {
					result.p[i][j] += A.p[i][k] * B.p[k][j];
				}
			}
		}
		return result;
	}

	const Matrix dot_product(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{ //矩阵点乘矩阵

		if (A.row == 1 && A.column == 1) {
			return A.p[0][0] * B;
		} else if (B.row == 1 && B.column == 1) {
			return B.p[0][0] * A;
		} else if (A.row != B.row) { //检查A,B是否同样大小
			throw invalid_argument("error: row(A) ≠ row(B)");
		} else if (A.column != B.column) { //检查A,B是否同样大小
			throw invalid_argument("error: column(A) ≠ column(B)");
		}
		const int &row = A.row;
		const int &column = A.column;

		Matrix result(row, column);
		int i, j;
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				result.p[i][j] = A.p[i][j] * B.p[i][j];
			}
		}

		return result;
	}

	const Matrix eye(int n)
	{ //构造一个单位矩阵
		Matrix result(n, n, 0);
		for (int i = 0; i < n; ++i) {
			result.p[i][i] = 1;
		}
		return result;
	}

	const Matrix operator^(const Matrix &A, const int n) throw (invalid_argument)
	{ //计算矩阵A的n次方

		A.test_square();

		switch (n) {
			case 0:
				return eye(A.row);
			case 1:
				return A;
			case 2:
				return A * A;
			default:
				if (n < 0) {
					return A.Inverse_matrix() ^ -n;
				} else {
					Matrix tmp(A ^ (n / 2));
					tmp = tmp * tmp;
					if (n % 2) {
						//指数为奇数
						tmp = tmp * A;
					}
					return tmp;
				}
		}
	}

	const Matrix operator&&(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{ //将两个矩阵按竖直方向连接
		/*   A
		 *  ---
		 *   B  */

		if (A.column != B.column) {
			throw invalid_argument("串联的矩阵的列数不一致");
		}

		const int row_total = A.row + B.row;
		const int &column_total = A.column;

		Matrix result(row_total, column_total);

		for (int i = 0; i < A.row; i++) { //行循环
			std::copy(A.p[i], A.p[i] + column_total, result.p[i]);
		}

		for (int i = 0; i < B.row; i++) { //行循环
			std::copy(B.p[i], B.p[i] + column_total, result.p[A.row + i]);
		}

		return result;
	}

	const Matrix operator||(const Matrix &A, const Matrix &B) throw (invalid_argument)
	{ //将两个矩阵按水平方向连接
		/*   A | B   */

		if (A.row != B.row) {
			throw invalid_argument("串联的矩阵的行数不一致");
		}
		const int &row_total = A.row;
		const int column_total = A.column + B.column;

		Matrix result(row_total, column_total);

		for (int i = 0; i < row_total; i++) { //行循环
			std::copy(A.p[i], A.p[i] + A.column, result.p[i]);
			std::copy(B.p[i], B.p[i] + B.column, result.p[i] + A.column);
		}

		return result;
	}

	const Matrix Matrix::operator+() const
	{
		return *this;
	}

	const Matrix Matrix::operator-() const
	{
		Matrix result(row, column);
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < column; ++j) {
				result.p[i][j] = -p[i][j];
			}
		}
		return result;
	}

	Matrix& Matrix::operator+=(const Matrix &with) throw (std::invalid_argument)
	{
		if (row != with.row) {
			throw invalid_argument("error: row(A) ≠ row(B)");
		}
		if (column != with.column) {
			throw invalid_argument("error: column(A) ≠ column(B)");
		}

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < column; ++j) {
				p[i][j] += with.p[i][j];
			}
		}

		return *this;
	}

	Matrix& Matrix::operator-=(const Matrix &with) throw (std::invalid_argument)
	{
		if (row != with.row) {
			throw invalid_argument("error: row(A) ≠ row(B)");
		}
		if (column != with.column) {
			throw invalid_argument("error: column(A) ≠ column(B)");
		}

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < column; ++j) {
				p[i][j] -= with.p[i][j];
			}
		}

		return *this;
	}

	Matrix& Matrix::operator*=(double k) throw ()
	{
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < column; ++j) {
				p[i][j] *= k;
			}
		}

		return *this;
	}

	void operator<<=(Matrix &tar, Matrix &src)
	{ //将矩阵src的资产转移给tar, src变为与原来同样大小的随机矩阵
		tar.clear();
		tar.row = src.row;
		tar.column = src.column;
		tar.p = src.p;

		src.p = new double*[src.row];
		for (int i = 0; i < src.row; ++i) {
			src.p[i] = new double[src.column];
		}
	}

	Matrix& Matrix::operator=(const Matrix &src)
	{
		//cout << this << " = " << &src << endl;
		if (row == src.row) {
			if (column == src.column) { //行,列数都与原来相等
				if (this == &src) { //自己给自己赋值
					return *this;
				}
				const size_t size_of_a_row = src.column * sizeof(double);
				for (int i = 0; i < src.row; i++) {
					memcpy(p[i], src.p[i], size_of_a_row);
				}
			} else { //行数与原来相等, 列数不等

				this->column = src.column;
				const size_t size_of_a_row = column * sizeof(double);
				for (int i = 0; i < row; i++) {
					delete[] p[i];
					memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
				}
			}
		} else {
			for (int i = 0; i < row; i++)
				delete[] p[i];
			delete[] p;

			this->row = src.row;
			this->column = src.column;

			p = new double*[row]; //开辟行
			const size_t size_of_a_row = column * sizeof(double);
			for (int i = 0; i < row; i++) {
				memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
			}
		}

		return *this;
	}

#if __cplusplus >= 201103L //C++0x
	const Matrix& Matrix::operator=(Matrix &&src)
	{ //转移赋值运算符

		this->clear();
		row = src.row;
		column = src.column;
		p = src.p;

		src.p = NULL;
		src.row = 0;
		src.column = 0;
		return *this;
	}
#endif

	const Matrix Matrix::sub_of(int up, int down, int left, int right) const throw (invalid_argument, out_of_range)
	{
		if (up >= down || left >= right) {
			throw new invalid_argument("up >= down or left >= right");
		}

		this->test_row(up);
		this->test_row(down - 1);
		this->test_column(left);
		this->test_column(right - 1);

		Matrix result(down - up, right - left);
		for (int i = up; i < down; ++i) {
			std::copy(p[i] + left, p[i] + right, result.p[i - up]);
		}
		return result;
	}

	const Matrix pow(const Matrix &A, const int n) throw (invalid_argument)
	{
		return A ^ n;
	}

	double tr(const Matrix &src) throw (invalid_argument)
	{ //返回方阵的迹
		src.test_square();
		double result = 0;
		for (int i = 0; i < src.row; i++) {
			result += src.p[i][i];
		}
		return result;
	}

	void Matrix::test_row(const int row_test) const throw (out_of_range)
	{
		if (row_test < 0 || row_test >= this->row) {
			throw out_of_range(
					"The " + to_string(this->row) + " × " + to_string(this->column) + " Matrix doesn't have the no."
							+ to_string(row_test) + " row!");
		}
	}

	void Matrix::test_column(const int column_test) const throw (out_of_range)
	{
		if (column_test < 0 || column_test >= this->column) {
			throw out_of_range(
					"The " + to_string(this->row) + " × " + to_string(this->column) + " Matrix doesn't have the no."
							+ to_string(column_test) + " column!");
		}
	}

	void Matrix::test_square() const throw (invalid_argument)
	{
		if (row != column) {
			throw invalid_argument("A is not a square matrix");
		}
	}

	const Matrix conv2(const Matrix &core, const Matrix &A, int size)
	{ //矩阵卷积
		int i, j, m, n;
		if (size == 2) {
			Matrix zsmall(A.row - core.row + 1, A.column - core.column + 1, 0);
			for (i = 0; i < zsmall.row; ++i) {
				for (m = i; m < i + core.row; ++m) {
					for (j = 0; j < zsmall.column; ++j) {
						for (n = j; n < j + core.column; ++n) {
							zsmall.p[i][j] += A.p[m][n] * core.p[m - i][n - j];
							cout << A.p[m][n] << "*" << core.p[m - i][n - j] << "   ";
						}
						cout << endl;
					}
				}
			}
			zsmall.print();
			return zsmall;
		}

		Matrix z(A.row + core.row - 1, A.column + core.column - 1, 0);
		for (m = 0; m < A.row; ++m) {
			for (i = m; i < m + core.row && i < z.row; ++i) {
				for (n = 0; n < A.column; ++n) {
					for (j = n; j < n + core.column && j < z.column; ++j) {
						z.p[i][j] += A.p[m][n] * core.p[i - m][j - n];
					}
				}
			}
		}

		if (size == 1) {

			Matrix z2 = z.sub_of((core.row - 1) / 2, A.row + (core.row - 1) / 2, (core.column - 1) / 2,
					A.column + (core.column - 1) / 2);

			return z2;
		} else {
			return z;
		}
	}

//计算
	bool Matcmp(const Matrix &A, const Matrix &B, double eps)
	{
		for (int i = 0; i < A.row; i++) {
			for (int j = 0; j < A.column; j++) {
				if (fabs(A.p[i][j] - B.p[i][j]) > eps) {
					return false;
				}
			}
		}
		return true;
	}

	const Matrix TransposeOf(const Matrix &A)
	{ //返回矩阵A的转置矩阵

		Matrix result(A.column, A.row);
		for (int i = 0; i < result.row; i++) {
			for (int j = 0; j < result.column; j++) {
				result.p[i][j] = A.p[j][i];
			}
		}
		return result;
	}

	const Matrix CofactorOf(const Matrix &A, const int row_tar, const int column_tar) throw (out_of_range)
	{ //构造方阵A的余子式A(x,y)

		A.test_row(row_tar);
		A.test_column(column_tar);

		Matrix result(A.row - 1, A.column - 1);

		const size_t size_of_a_row_of_a_left = column_tar * sizeof(double); //这一行为加快速度而存在
		const size_t size_of_a_row_of_a_right = (A.column - 1 - column_tar) * sizeof(double); //这一行为加快速度而存在
		for (int i = 0; i < row_tar; i++) {
			memcpy(result.p[i], A.p[i], size_of_a_row_of_a_left);
			memcpy(result.p[i] + column_tar, A.p[i] + column_tar + 1, size_of_a_row_of_a_right);
		}
		for (int i = row_tar + 1; i < A.row; i++) {
			memcpy(result.p[i - 1], A.p[i], size_of_a_row_of_a_left);
			memcpy(result.p[i - 1] + column_tar, A.p[i] + column_tar + 1, size_of_a_row_of_a_right);
		}
		return result;
	}

	void Matrix::do_Cofactor(const int row_tar, const int column_tar) throw (out_of_range)
	{ //返回一个矩阵划去row_tar 行和 column_tar 列后的矩阵
		*this = CofactorOf(*this, row_tar, column_tar);
	}

//应用部分

	const Matrix rotate_X(double sigma)
	{
		double cosine = cos(sigma);
		double sine = sin(sigma);
		double a[3][3] = { 1, 0, 0, 0, cosine, -sine, 0, sine, cosine };
		return Matrix(a, 3, 3);
	}

	const Matrix rotate_Y(double sigma)
	{
		double cosine = cos(sigma);
		double sine = sin(sigma);
		double a[3][3] = { cosine, 0, sine, 0, 1, 0, -sine, 0, cosine };
		return Matrix(a, 3, 3);
	}

	const Matrix rotate_Z(double sigma)
	{
		double cosine = cos(sigma);
		double sine = sin(sigma);
		double a[3][3] = { cosine, -sine, 0, sine, cosine, 0, 0, 0, 1 };
		return Matrix(a, 3, 3);
	}

	void rotate_X(double sigma, const double& x0, double& y0, double& z0) throw ()
	{
		double cosine = cos(sigma);
		double sine = sin(sigma);
		double y1 = y0 * cosine - z0 * sine;
		double z1 = y0 * sine + z0 * cosine;

		y0 = y1;
		z0 = z1;
	}

	void rotate_Y(double sigma, double& x0, const double& y0, double& z0) throw ()
	{
		double cosine = cos(sigma);
		double sine = sin(sigma);
		double x1 = x0 * cosine + z0 * sine;
		double z1 = -x0 * sine + z0 * cosine;

		x0 = x1;
		z0 = z1;
	}

	void rotate_Z(double sigma, double& x0, double& y0, const double& z0) throw ()
	{
		double cosine = cos(sigma);
		double sine = sin(sigma);
		double x1 = x0 * cosine - y0 * sine;
		double y1 = x0 * sine + y0 * cosine;

		x0 = x1;
		y0 = y1;
	}

} /* namespace kerbal */
