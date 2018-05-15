//
//  main.cpp
//  Matrix_calculator
//
//  Created by Leo Jia on 2018-03-19.
//  Copyright © 2018 Leo Jia. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void get_matrix(int **ar, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int num = 0;
            cout<<"Please enter the number for row"<<i+1<<" colunm"<<j+1<<": ";
            cin>>num;
            ar[i][j] = num;
        }
    }
}

void print_matrix(int **ar, int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            cout<<ar[i][j]<<' ';
        }
        cout<<"\n";
    }
    cout<<endl;
}

void fix_matrix(int **ar, int dim) {
    int row = 0;
    int col = 0;
    int num = 0;
    printf("Enter the position that you want to change. \n");
    cout<<"Row: ";
    cin>>row;
    cout<<"Column: ";
    cin>>col;
    cout<<"Correct number: ";
    cin>>num;
    while (1) {
        if ((col <= dim) && (row <= dim)) {
            break;
        }
        if (row > dim) {
            printf("Invalid row! Please enter correct row: ");
            cin>>row;
        }
        if (col > dim) {
            printf("Invalid column! Please enter correct column: ");
            cin>>col;
        }
    }
    ar[row-1][col-1] = num;
}

void enter_matrix(int **matrix, int dim) {
    char ans = 0;
    char ans_corr = 0;
    get_matrix(matrix, dim);
    printf("Is this matrix that you enter? Enter 'y' for Yes, 'n' for No\n");
    print_matrix(matrix, dim);
    while (1) {
        cin>>ans;
        if (ans == 'n' || ans == 'N' || ans == 'y' || ans == 'Y') {
            break;
        }
        else {
            printf("Invalid answer, please enter 'y' for Yes, 'n' for No\n ");
        }
    }
    if (ans == 'n' || ans == 'N') {
        while (1) {
            fix_matrix(matrix, dim);
            printf("Is this matrix that you enter? Enter 'y' for Yes, 'n' for No\n");
            print_matrix(matrix, dim);
            cin>>ans_corr;
            if (ans_corr == 'y' || ans_corr == 'Y') {
                break;
            }
        }
    }
}

void row_reduction(int **matrix, int dim) {
    int index = 0;
    if (matrix[0][0] == 0) {                              // find the row whose pivot is not 0
        for (int i = 0; i < dim; i++) {
            if (matrix[i][0] != 0) {
                index = i;
                break;
            }
        }
        for (int i = 0; i < dim; i++) {                   // swap first row whose pivot is 0 with the index(th) row whose pivot != 0
            int tempt = matrix[0][i];
            matrix[0][i] = matrix[index][i];
            matrix[index][i] = tempt;
        }
    }
    cout<<endl;
    print_matrix(matrix, dim);
    
    for (int i = 1; i < dim; i++) {
        for (int j = 0; j < i; j++) {
            if (matrix[i][j] != 0) {
                int scalar = matrix[i][j];
                for (int k = j; k < dim; k++) {
                    matrix[i][k] = matrix[i][k] * matrix[j][j] - matrix[j][k] * scalar;
                }
            }
        }
    }
}

void num_multiplication(int **matrix, int dim, int num) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matrix[i][j] *= num;
        }
    }
}

int matrx_cal(int **matrix, int **mew, int dim, int row, int col) {
    int result = 0;
    for (int i = 0; i < dim; i++) {
        result += matrix[row][i] * mew[i][col];
    }
    return result;
}

void matrix_matrix_mult(int **matrix, int **copy, int dim) {
    int **new_one= new int*[dim * dim];
    for (int i = 0; i < dim; i++) {
        new_one[i] = new int[dim];
    }
    enter_matrix(new_one, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matrix[i][j] = matrx_cal(copy, new_one, dim, i, j);
        }
    }
}


void matrix_matrix_add(int **matrix, int **copy, int dim) {
    int **new_one= new int*[dim * dim];
    for (int i = 0; i < dim; i++) {
        new_one[i] = new int[dim];
    }
    enter_matrix(new_one, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim;  j++) {
            matrix[i][j] = new_one[i][j] + copy[i][j];
        }
    }
}

void matrix_matrix_sub(int **matrix, int **copy, int dim) {
    int **new_one= new int*[dim * dim];
    for (int i = 0; i < dim; i++) {
        new_one[i] = new int[dim];
    }
    enter_matrix(new_one, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim;  j++) {
            matrix[i][j] = copy[i][j] - new_one[i][j];
        }
    }
}


int **deep_copy (int **matrix, int dim) {
    int **copy = new int*[dim * dim];
    for (int i = 0; i < dim; i++) {
        copy[i] = new int[dim];
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}



int main(void) {
    int dim = 0;
    cout<<"Please enter the dimension of the square matrix: ";
    cin>>dim;
    int **matrix= new int*[dim * dim];
    for (int i = 0; i < dim; i++) {
        matrix[i] = new int[dim];
    }
    enter_matrix(matrix, dim);
    int **copy = deep_copy(matrix, dim);
    cout<<"Do anything you want, 1 for row reduce, 2 for number mulitplication, 3 for matrix_matrix mulitplication, 4 for matrix_matrix addition, "<<endl;
    cout<<"5 for matrix_matrix_substraction."<<endl;
    int chck = 0;
    cin>>chck;
    if (chck == 1) {
        row_reduction(copy, dim);
        cout<<"After row reduction: "<<endl;
        print_matrix(copy, dim);
    } else if (chck == 2) {
        int num = 0;
        cout<<"Please enter the number you want to multiply."<<endl;
        cin>>num;
        num_multiplication(copy, dim, num);
        cout<<"The matrix after number multiplication is: "<<endl;
        print_matrix(copy, dim);
    } else if (chck == 3) {
        matrix_matrix_mult(copy, matrix, dim);
        cout<<"The matrix after multiplicaition: "<<endl;
        print_matrix(copy, dim);
    } else if (chck == 4) {
        matrix_matrix_add(copy, matrix, dim);
        cout<<"The matrix after addition is: "<<endl;
        print_matrix(copy, dim);
    } else if (chck == 5) {
        matrix_matrix_sub(copy, matrix, dim);
        cout<<"The matrix after subtraction is: "<<endl;
        print_matrix(copy, dim);
    }
    cout<<"Do you want to get the orginal matrix! y/n "<<endl;
    char anw;
    cin>>anw;
    while (anw != 'y' && anw != 'n') {
        cout<<"Please enter y for yes, n for no! "<<endl;
        cin>>anw;
    }
    if (anw == 'y'){
        copy = deep_copy(matrix, dim);
        print_matrix(copy, dim);
    }
    for (int i = 0; i < dim; i++) {
        delete[] matrix[i];
        delete[] copy[i];
    }
    delete []copy;
    delete []matrix;
    return 0;
}











