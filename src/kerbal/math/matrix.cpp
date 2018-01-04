#include "matrix.hpp"

#include <algorithm>
#include "../string_serve.hpp"

#if __cplusplus < 201103L //C++0x
#	pragma message("\n"\
"			* Matrix 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性\n"\
"					* Matrix 为 C++ 11 准备的新特性: 转移构造函数\n"\
"					* Matrix 为 C++ 11 准备的新特性: 利用一维初始化列表进行构造\n"\
"					* Matrix 为 C++ 11 准备的新特性: 利用二维初始化列表进行构造\n"\
"					* Matrix 为 C++ 11 准备的新特性: 转移赋值运算符"\
)
#endif //C++0x

namespace std
{
	void swap(kerbal::math::matrix::Matrix &a, kerbal::math::matrix::Matrix &b)
	{
		swap(a.row, b.row);
		swap(a.column, b.column);
		swap(a.p, b.p);
	}
}

namespace kerbal
{
	namespace math
	{
		namespace matrix
		{
			namespace
			{
				using namespace string_serve;
			}

			using namespace kerbal::data_struct::array_2d;

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

			void Matrix::print(Matrix::Frame_style frame, bool print_corner, std::ostream &output) const
			{
				//Frame frame 默认= Fr_RtMatrix, bool print_corner 默认= true, ostream &output = output
				//static const std::string Corner_RtMatrix[] = { "┌", "┐", "└", "┘", "│" };

				static const char Corner_RdMatrix[5][5] = { "╭", "╮", "╰", "╯", "│" };
				static const char Corner_Det[5][5] = { " ", " ", " ", " ", "│" };
				static const char Corner_double[5][5] = { " ", " ", " ", " ", "││" };

				const char (*corner)[5] = NULL;
				switch (frame) {
					case Matrix::rt_corner:
						if (print_corner) {
							Array_2d<double>::print(Array_2d<double>::frame_with_corner, output);
						} else {
							Array_2d<double>::print(Array_2d<double>::frame_only, output);
						}
						return;
					case Matrix::none:
						Array_2d<double>::print(Array_2d<double>::none, output);
						return;
					case Matrix::rd_corner:
						corner = Corner_RdMatrix;
						break;
					case Matrix::single_det:
						corner = Corner_Det;
						break;
					case Matrix::double_det:
						corner = Corner_double;
						break;
				}

				output << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格

				int i, j;
				output << corner[0];
				for (j = 0; j < column; j++) {
					output << "  " << std::setw(12) << " ";
				}
				output << " " << corner[1] << std::endl;

				for (i = 0; i < row; i++) {
					output << corner[4];

					for (j = 0; j < column; j++) {
						output << "  " << std::setw(12) << p[i][j];
					}
					output << " " << corner[4] << std::endl;
				}

				output << corner[2];
				for (j = 0; j < column; j++) {
					output << "  " << std::setw(12) << " ";
				}
				output << " " << corner[3];
				if (print_corner) {
					output << " " << row << " × " << column;
				}
				output << std::endl;
			}

			void Matrix::save(std::ofstream & fout) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind)
			{
				const size_t sizeof_row = sizeof(row);
				const size_t sizeof_column = sizeof(column);
				const size_t sizeof_element = sizeof(p[0][0]);

				/* 输出位宽信息 */
				try {
					switch (sizeof(size_t)) {
						case 4: //size_t 32位版本
							fout.write((const char*) &sizeof_row, 4); //输出变量row在内存中所占的长度
							fout.write("\0\0\0\0", 4); //不足8位补4个零
							fout.write((const char*) &sizeof_column, 4);
							fout.write("\0\0\0\0", 4);
							fout.write((const char*) &sizeof_element, 4);
							fout.write("\0\0\0\0", 4);
							break;
						case 8: //size_t 64位版本
							fout.write((const char*) &sizeof_row, 8); //输出变量row在内存中所占的长度
							fout.write((const char*) &sizeof_column, 8);
							fout.write((const char*) &sizeof_element, 8);
							break;
						default:
							throw std::runtime_error("不支持的位宽");
					}

					fout.write((const char*) &row, sizeof_row); //输出矩阵行数
					fout.write((const char*) &column, sizeof_column); //输出矩阵列数
					for (int i = 0; i < row; i++) {
						for (int j = 0; j < column; j++) {
							fout.write((const char*) (p[i] + j), sizeof_element); //输出矩阵元素
						}
					}
				} catch (...) {
					fout.close();
					throw;
				}
			}

			void Matrix::save(const char * file_name) const throw (std::runtime_error, __cxxabiv1:: __forced_unwind)
			{
				std::ofstream fout(file_name, std::ios::out | std::ios::binary);
				if (!fout) {
					throw std::runtime_error("文件打开失败");
				}
				this->save(fout);
				fout.close();
			}

			const Matrix load_from(std::ifstream & fin) throw (std::runtime_error)
			{
				size_t size_of_row_in_file;
				size_t size_of_column_in_file;
				size_t size_of_ele_in_file;

				fin.read((char*) &size_of_row_in_file, 4);
				fin.ignore(4);
				fin.read((char*) &size_of_column_in_file, 4);
				fin.ignore(4);
				fin.read((char*) &size_of_ele_in_file, 4);
				fin.ignore(4);

				static const size_t size_of_row = sizeof(Matrix::row);
				static const size_t size_of_column = sizeof(Matrix::column);
				static const size_t size_of_ele = sizeof(double);

				if (size_of_row != size_of_row_in_file

				|| size_of_column != size_of_column_in_file

				|| size_of_ele != size_of_ele_in_file) {

					fin.close();
					throw std::runtime_error("位宽不兼容");
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
				return tmp;
			}

			const Matrix load_from(const char * file_name) throw (std::runtime_error)
			{
				std::ifstream fin(file_name, std::ios::in | std::ios::binary);
				if (!fin) {
					throw std::runtime_error("文件打开失败");
				}
				const Matrix tmp = load_from(fin);
				fin.close();
				return tmp;
			}

			void Matrix::switch_rows(const int row1, const int row2)
			{
				this->test_row(row1);
				this->test_row(row2);
				std::swap(p[row1], p[row2]);
			}

			void Matrix::switch_columns(const int column1, const int column2)
			{
				this->test_column(column1);
				this->test_column(column2);

				for (int i = 0; i < row; i++) {
					std::swap(p[i][column1], p[i][column2]);
				}
			}

			void Matrix::kmr(const double k, const int row_dest)
			{
				test_row(row_dest);

				for (int i = 0; i < column; i++) {
					p[row_dest][i] *= k;
				}
			}

			void Matrix::kmr_plus_to_another(const double k, const int row_from, const int row_dest)
			{
				test_row(row_from);
				test_row(row_dest);

				for (int i = 0; i < column; i++) {
					p[row_dest][i] += k * p[row_from][i];
				}
			}

			void Matrix::kmc(const double k, const int column_dest)
			{
				test_column(column_dest);

				for (int i = 0; i < row; i++) {
					p[i][column_dest] *= k;
				}
			}

			void Matrix::kmc_plus_to_another(const double k, const int column_from, const int column_dest)
			{
				test_column(column_from);
				test_column(column_dest);

				for (int i = 0; i < row; i++) {
					p[i][column_dest] += k * p[i][column_from];
				}
			}

			void Matrix::do_optimize_rows() throw (std::invalid_argument)
			{
				//将行列式针对行进行优化
				test_square();
				bool k = false; //是否取相反数
				const int &n = row;
				for (int i = 1; i < n; i++) {
					for (int j = 0; j < n - i; j++) {

						if (p[j][0] != 0) {
							if (p[j + 1][0] == 0 || fabs(p[j][0]) < fabs(p[j + 1][0])) {
								std::swap(p[j], p[j + 1]);
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

			double Matrix::det() const throw (std::invalid_argument)
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
							Matrix daishu = cofactor_of(*this, i, 0);
							daishu.do_optimize_rows();
							sum += p[i][0] * daishu.det(); //i为偶数
						}
					}
					for (int i = 1; i < n; i += 2) { //i为奇数
						if (p[i][0] != 0.0) { //p[0][i]!=0
							Matrix daishu = cofactor_of(*this, i, 0);
							daishu.do_optimize_rows();
							sum -= p[i][0] * daishu.det(); //i为奇数

						}
					}
				} else {
					for (int i = 0; i < n; i += 2) { //i为偶数
						if (p[i][0] != 0.0) { //p[0][i]!=0
							Matrix daishu = cofactor_of(*this, i, 0);
							sum += p[i][0] * daishu.det(); //i为偶数
						}
					}
					for (int i = 1; i < n; i += 2) { //i为奇数
						if (p[i][0] != 0.0) { //p[0][i]!=0
							Matrix daishu = cofactor_of(*this, i, 0);
							sum -= p[i][0] * daishu.det(); //i为奇数
						}
					}
				}
#		undef n
				return sum;
			}

			Matrix Matrix::Adjugate_matrix() const throw (std::invalid_argument)
			{
//返回本方阵的伴随矩阵

				this->test_square();
				Matrix result(row, column);
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < column; j++) {
						if ((i + j) % 2) {
							//i+j为奇数
							result.p[j][i] = -cofactor_of(*this, i, j).det();
						} else {
							//i+j为偶数
							result.p[j][i] = cofactor_of(*this, i, j).det();
						}
					}
				}
				return result;
			}

			Matrix Matrix::Inverse_matrix() const throw (std::invalid_argument)
			{
//返回本方阵的逆矩阵
				this->test_square();

				double D = this->det();
				if (D == 0.0) {
					throw std::invalid_argument("A does not have an inverse matrix");
				}
				const double k = 1.0 / D;
				return Matrix(k * this->Adjugate_matrix());
			}

//运算符重载
			const Matrix operator+(const Matrix &A, const Matrix &B)
			{ //检查A,B是否同样大小
				if (A.row != B.row) {
					throw std::invalid_argument("error: row(A) ≠ row(B)");
				}
				if (A.column != B.column) {
					throw std::invalid_argument("error: column(A) ≠ column(B)");
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

			const Matrix operator-(const Matrix &A, const Matrix &B)
			{ //检查A,B是否同样大小
				if (A.row != B.row) {
					throw std::invalid_argument("error: row(A) ≠ row(B)");
				}
				if (A.column != B.column) {
					throw std::invalid_argument("error: column(A) ≠ column(B)");
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

			const Matrix operator*(const double k, const Matrix &A)
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

			const Matrix operator*(const Matrix &A, const double k)
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

			const Matrix operator*(const Matrix &A, const Matrix &B) throw (std::invalid_argument)
			{ //矩阵乘矩阵

//检查A的列数是否等于B的行数
				if (A.column != B.row) {
					throw std::invalid_argument("error: column(A) ≠ row(B)");
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

			const Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C)
			{ // A * B + C

				//检查A的列数是否等于B的行数
				if (A.column != B.row) {
					throw std::invalid_argument("error: column(A) ≠ row(B)");
				}
				const int &row = A.row;
				const int &column = B.column;
				if (row != C.row || column != C.column) {
					throw std::invalid_argument("error: size(A*B) ≠ size(C)");
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

			const Matrix dot_product(const Matrix &A, const Matrix &B)
			{ //矩阵点乘矩阵

				if (A.row == 1 && A.column == 1) {
					return A.p[0][0] * B;
				} else if (B.row == 1 && B.column == 1) {
					return B.p[0][0] * A;
				} else if (A.row != B.row) { //检查A,B是否同样大小
					throw std::invalid_argument("error: row(A) ≠ row(B)");
				} else if (A.column != B.column) { //检查A,B是否同样大小
					throw std::invalid_argument("error: column(A) ≠ column(B)");
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

			const Matrix operator^(const Matrix &A, const int n)
			{ //计算矩阵A的n次方

				if (n >= 4) {
					Matrix tmp = A ^ (n / 2);
					tmp = tmp * tmp;
					if (n % 2) {
						//指数为奇数
						tmp = tmp * A;
					}
					return tmp;
				} else if (n == 3) {
					return A * A * A;
				} else if (n < 0) {
					return A.Inverse_matrix() ^ -n;
				} else if (n == 2) {
					return A * A;
				} else if (n == 1) {
					return A;
				} else { //n == 0
					A.test_square();
					return eye(A.row);
				}
			}

			const Matrix operator&&(const Matrix &A, const Matrix &B)
			{ //将两个矩阵按竖直方向连接
				/*   A
				 *  ---
				 *   B  */

				if (A.column != B.column) {
					throw std::invalid_argument("串联的矩阵的列数不一致");
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

			const Matrix operator||(const Matrix &A, const Matrix &B)
			{ //将两个矩阵按水平方向连接
				/*   A | B   */

				if (A.row != B.row) {
					throw std::invalid_argument("串联的矩阵的行数不一致");
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

			Matrix& Matrix::operator+=(const Matrix &with)
			{
				if (row != with.row) {
					throw std::invalid_argument("error: row(A) ≠ row(B)");
				}
				if (column != with.column) {
					throw std::invalid_argument("error: column(A) ≠ column(B)");
				}

				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						p[i][j] += with.p[i][j];
					}
				}

				return *this;
			}

			Matrix& Matrix::operator-=(const Matrix &with)
			{
				if (row != with.row) {
					throw std::invalid_argument("error: row(A) ≠ row(B)");
				}
				if (column != with.column) {
					throw std::invalid_argument("error: column(A) ≠ column(B)");
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

			const Matrix Matrix::sub_of(int up, int down, int left, int right) const throw (std::invalid_argument, std::out_of_range)
			{
				if (up >= down || left >= right) {
					throw new std::invalid_argument("up >= down or left >= right");
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

			const Matrix pow(const Matrix &A, const int n)
			{
				return A ^ n;
			}

			double tr(const Matrix &src) throw (std::invalid_argument)
			{ //返回方阵的迹
				src.test_square();
				double result = 0;
				for (int i = 0; i < src.row; i++) {
					result += src.p[i][i];
				}
				return result;
			}

			void Matrix::test_row(const int row_test) const throw (std::out_of_range)
			{
#			if __cplusplus >= 201103L
				using std::to_string;
#			else
				using kerbal::string_serve::to_string;
#			endif

				if (row_test < 0 || row_test >= this->row) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " × " + to_string(this->column)
									+ " Matrix doesn't have the no." + to_string(row_test) + " row!");
				}
			}

			void Matrix::test_column(const int column_test) const throw (std::out_of_range)
			{
#			if __cplusplus >= 201103L
				using std::to_string;
#			else
				using kerbal::string_serve::to_string;
#			endif

				if (column_test < 0 || column_test >= this->column) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " × " + to_string(this->column)
									+ " Matrix doesn't have the no." + to_string(column_test) + " column!");
				}
			}

			void Matrix::test_square() const throw (std::invalid_argument)
			{
				if (row != column) {
					throw std::invalid_argument("A is not a square matrix");
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
									std::cout << A.p[m][n] << "*" << core.p[m - i][n - j] << "   ";
								}
								std::cout << std::endl;
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

			const Matrix transpose_of(const Matrix &A)
			{ //返回矩阵A的转置矩阵

				Matrix result(A.column, A.row);
				for (int i = 0; i < result.row; i++) {
					for (int j = 0; j < result.column; j++) {
						result.p[i][j] = A.p[j][i];
					}
				}
				return result;
			}

			const Matrix cofactor_of(const Matrix &A, const int row_tar, const int column_tar) throw (std::out_of_range)
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

			void Matrix::do_cofactor(const int row_tar, const int column_tar) throw (std::out_of_range)
			{ //返回一个矩阵划去row_tar 行和 column_tar 列后的矩阵
				*this = cofactor_of(*this, row_tar, column_tar);
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

		}/* namespace matrix */

	}/* namespace math */

} /* namespace kerbal */

