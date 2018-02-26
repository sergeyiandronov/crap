
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>

using namespace std;


void finit()
{
    ofstream fout;
    fout.open("A.txt");
    fout << "3, 3\n2 2 2\n2 2 2\n2 2 2";
    fout.close();

    fout.open("B.txt");
    fout << "2, 2\n1 1 1\n1 1 1\n1 1 1";
    fout.close();

    fout.open("C.txt");
    fout << "3, 3\n1 2 2\n0 4 4\n0 4 0";
    fout.close();

    fout.open("D.txt");
    fout << "3, 3\n1 2 3\n4 5 6\n7 8 9";
    fout.close();
}

class matrix_t {
    int** data;
    unsigned int rows;
    unsigned int collumns;

public:
    matrix_t(){
        data=nullptr;
        rows=0;
        collumns=0;
    }
    void create_matrix(unsigned int columns,
    unsigned int rows)
    {
         data = new int*[rows];
         for (unsigned int i = 0; i < rows; ++i) {
              matrix[i] = new int[columns];
              for (unsigned int j = 0; j < columns; ++j) {
                   matrix[i][j] = 0.0f;
              }
         }
         this->rows=rows;
         this->collumns=collumns;
    
    }
    ~matrix_t(){
            for (unsigned int i = 0; i < rows; ++i) {
                delete[] elements[i];
            }
            delete[] elements;
        
    }
    matrix_t add(matrix_t& other)
    {
        matrix_t result;

        assert(collumns != other.collumns || rows != other.rows) ;
            
        
        result.data = create_matrix(rows, collumns);
        result.rows = rows;
        result.collumns = collumns;
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < collumns; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    };
  
    matrix_t sub(matrix_t& other)
    {
        matrix_t result;

        if (collumns != other.collumns || rows != other.rows) {
            result.data = nullptr;
            destroy(data, rows);
            destroy(other.data, other.rows);
            return result;
        }
        result.data = create_matrix(rows, collumns);
        result.rows = rows;
        result.collumns = collumns;
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < collumns; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }
    matrix_t mul(matrix_t& other)
    {
        matrix_t result;
        if (collumns != other.rows) {
            result.data = nullptr;
            destroy(data, rows);
            destroy(other.data, other.rows);
            return result;
           
        }
        result.data = create_matrix(other.collumns, rows);
        for (unsigned int i= 0; i < rows; i++) {
            for (unsigned int j = 0; j < other.collumns; j++) {
                float y = 0;
                for (unsigned int z = 0; z < collumns; z++) {
                    y += data[i][z] * other.data[z][j];
                }
                result.data[i][j] = y;
            }
        }
        result.collumns = other.collumns;
        result.rows = rows;
        return result;
    }
    matrix_t trans()
    {
        matrix_t result;
        result.data = create_matrix(rows, collumns);

        for (unsigned int i = 0; i < collumns; i++) {
            for (unsigned int j = 0; j < rows; j++) {
                result.data[i][j] = data[j][i];
            }
        }
        result.collumns = rows;
        result.rows = collumns;
        return result;
    }

    ifstream& read(ifstream& stream)
    {
        string header;

        char razdel;
        getline(stream, header);
        istringstream str(header);
        if (!((str >> rows) && (str >> razdel) && (str >> collumns) && (razdel == ','))) {
            stream.setstate(std::ios::failbit);
        }

        data = create_matrix(collumns, rows);
        for (unsigned int i = 0; i< rows; i++) {
            string new_row;
            getline(stream, new_row);

            istringstream sstream(new_row);
            for (unsigned int j = 0; j< collumns; j++) {
                if (!(sstream >> data[i][j])) {
                    destroy(data, rows);
                    stream.setstate(std::ios::failbit);
                    break;
                }
            }
        }

        return stream;
    };
    ostream& write(ostream& stream)
    {
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < collumns; j++) {

                stream << data[i][j] << '\t';
            }
            stream << '\n';
        }
        return stream;
    };
};
bool getcommandifile(ifstream& fs1, ifstream& fs2, char& op)
{
    op = 'q';
    string fn;
    getline(cin, fn);

    istringstream sfn(fn);
    string name1 = "";
    string name2 = "";
    char hop;
    while (sfn >> hop) {
        if (hop != '+' && hop != '-' && hop != 'T' && hop != '*') {
            name1 += hop;
        }
        if (hop == '+' || hop == '-' || hop == '*') {
            op = hop;
            while (sfn >> hop) {
                if (hop != '+' && hop != '-' && hop != 'T' && hop != 'R' && hop != '*') {
                    name2 += hop;
                }
                else {
                    return false;
                }
            }
            break;
        }
        if (hop == 'T') {
            op = hop;
            break;
        }
    }
    if (name1 != "") {
        fs1.open(name1);
    }
    if (name2 != "") {
        fs2.open(name2);
    }
    if (fs1.is_open() && (op == 'T')) {
        return true;
    }
    else if (fs1.is_open() && fs2.is_open() && op != 'q') {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    char com;
    finit();
    ifstream mtr1, mtr2;
    matrix_t matrix1, matrix2, matrix3;
    if (!getcommandifile(mtr1, mtr2, com)) {

        cout << "An error has occured while reading input data";
        exit(0);
    }

    if (!matrix1.read(mtr1)) {
        cout << "An error has occured while reading input data";
        mtr1.close();
        mtr2.close();
        exit(0);
    }
    if (com == 'T') {
        matrix3 = matrix1.trans();
        matrix3.write(cout);
        matrix1.clearmem();
        matrix3.clearmem();
        mtr1.close();
        mtr2.close();

        exit(0);
    }
    else if (com != '+' && com != '-' && com != '*') {
        cout << "An error has occured while reading input data";
        matrix1.clearmem();
        mtr1.close();
        mtr2.close();
        exit(0);
    }
    if (!matrix2.read(mtr2)) {
        cout << "An error has occured while reading input data";
        matrix1.clearmem();
        mtr1.close();
        mtr2.close();
        exit(0);
    }
    switch (com) {
    case '+':
        matrix3 = matrix1.add(matrix2);
        break;
    case '-':
        matrix3 = matrix1.sub(matrix2);
        break;
    case '*':
        matrix3 = matrix1.mul(matrix2);
        break;
    }
    if (!matrix3.isnull()) {
        matrix3.write(cout);
        matrix1.clearmem();
        matrix2.clearmem();
        matrix3.clearmem();
        mtr1.close();
        mtr2.close();
    }
    else {
        cout << "Wrong matrixes";
        mtr1.close();
        mtr2.close();
    }

    return 0;
}
