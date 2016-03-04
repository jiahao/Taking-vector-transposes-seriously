// Eigen test program

// Version tested: Eigen 3.2.6
//
// Reference: http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html
//
// Matrix type: Eigen::MatrixXd
// Vector type: Eigen::VectorXd
// Scalar type: double
// Multiplication operator: *
// Division operator: /
// Transpose operator: .transpose()
//

#include <iostream>
#include <typeinfo>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;

MatrixXd make_matrix(int m, int n)
{
    int i, j;

    MatrixXd M(m,n);
    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            M(i,j) = 1.0;
        }
    }

    return M;
}

MatrixXd make_matrix(int n)
{
    return make_matrix(n, n);
}

VectorXd make_vector(int n)
{
    int i;

    VectorXd a(n);
    for(i=0; i<n; i++)
    {
        a(i) = 1.0;
    }
    return a;
}


int main()
{
    const int n = 4;

    MatrixXd A = make_matrix(n);
    MatrixXd B = make_matrix(n);
    MatrixXd Scal = make_matrix(1);
    assert (A.rows() == n);
    assert (A.cols() == n);

    MatrixXd rowmat = make_matrix(1, n);
    assert (rowmat.rows() == 1);
    assert (rowmat.cols() == n);

    MatrixXd colmat = make_matrix(n, 1);
    assert (colmat.rows() == n);
    assert (colmat.cols() == 1);

    VectorXd x = make_vector(n);
    VectorXd y = make_vector(n);
    VectorXd z = make_vector(n);
    assert (x.rows() == n); //row major
    assert (x.cols() == 1); //Note implicit singleton dimension rule

    VectorXd v1 = make_vector(1);

    double alpha = 1.0;
    double beta = 1.0;

    ///////////////////////////////
    // Test elementary behaviors //
    ///////////////////////////////
    //
    //With a compiled language, if the program compiles, then it is proof
    //that the declared output type is correct
    //

    // Assignability
    ////////////////

    // scalar to vector
    // VectorXd scaltovec = alpha;
    // Result: compile-time error
    // no viable conversion from 'double' to 'VectorXd' (aka 'Matrix<double, Dynamic, 1>')

    // scalar to matrix
    // MatrixXd scaltomat = alpha;
    // Result: compile-time error
    // no viable conversion from 'double' to 'MatrixXd' (aka 'Matrix<double, Dynamic, Dynamic>')

    // vector to scalar
    // double vectoscal = x;
    // Result: compile-time error
    // no viable conversion from 'VectorXd' (aka 'Matrix<double, Dynamic, 1>') to 'double'
    // The same error is thrown for 1-vectors
    // double vectoscal = make_vector(1);

    // vector to matrix
    MatrixXd vectomat = x;
    assert (vectomat == x);
    // Note that vectomat and x are NOT of the same type!
    // You can use C++'s RTTI (run time type introspection) capability, like so:
    // cout << typeid(x).name() << endl
    //     << typeid(vectomat).name() << endl;
    // but since typeinfo.name() produces an implementation-specific string that
    // is mangled, it is often easier to try to assign the expression to a new
    // variable of definitely incompatible type, e.g. a std::string, and read off
    // the compiler error:
    // std::string foo = x;
    // x is of type MatrixXd, a type alias for Matrix<double, Dynamic, Dynamic>
    // vectomat is of type VectorXd, a type alias for Matrix<double, Dynamic, 1>
    // so this equality can only be done when C++/Eigen can figure out that the
    // second template parameter is 1, i.e. at run time.

    // matrix to scalar
    // double mattoscal = A;
    // Result: compile-time error
    // no viable conversion from 'MatrixXd' (aka 'Matrix<double, Dynamic, Dynamic>') to 'double'
    // The same error is thrown for 1x1 matrices
    // double mattoscal = make_matrix(1,1);

    // matrix to vector
    // VectorXd mattovec = A;
    // Result: run time assertion failure
    // Assertion failed: (other.rows() == 1 || other.cols() == 1), function resizeLike,

    // row matrix to vector
    // VectorXd rowmattovec = rowmat;
    // Result: run time assertion failure
    // Assertion failed: (rows() == other.rows() && cols() == other.cols()), function lazyAssign

    // column matrix to vector
    VectorXd colmattovec = colmat;
    assert (colmattovec == colmat);
    assert (colmattovec.rows() == n);
    assert (colmattovec.cols() == 1);


    // Products expressible using *
    ///////////////////////////////

    //matmat (matmul)
    //The result is a special type
    //ProductReturnType<Matrix<double, -1, -1, 0,
    //  -1, -1>, Matrix<double, -1, 1, 0, -1, 1> >
    //that is assignable to a matrix
    MatrixXd matmul = A*B;
    assert (matmul.rows() == n);
    assert (matmul.cols() == n);

    //or a vector if the result has 1 column
    VectorXd matcolmatmul = A*colmat;
    assert (matcolmatmul.rows() == n);
    assert (matcolmatmul.cols() == 1);

    //but not if the result has 1 row
    //VectorXd rowmatmatmul = rowmat*A;
    //Result: run-time assertion failure
    //Assertion failed: (dst.rows()==m_lhs.rows() && dst.cols()==m_rhs.cols()), function scaleAndAddTo

    //Eigen doesn't allow automatic depromotion of 1x1 matrices to scalars
    //
    //MatrixXd matscalmul = Scal*A;
    //Result: run-time assertion failure
    //Assertion failed: (a_lhs.cols() == a_rhs.rows() && "invalid matrix product" && "if you wanted a coeff-wise or a dot product use the respective explicit functions"), function ProductBase
    //MatrixXd scalmatmul = A*Scal;
    //Result: run-time assertion failure
    //Assertion failed: (a_lhs.cols() == a_rhs.rows() && "invalid matrix product" && "if you wanted a coeff-wise or a dot product use the respective explicit functions"), function ProductBase
    //matvec
    //The result is a special type
    //ProductReturnType<Matrix<double, -1, -1, 0,
    //  -1, -1>, Matrix<double, -1, 1, 0, -1, 1> >
    //that is assignable to a matrix or vector
    VectorXd matvec = A*x;
    assert (matvec.rows() == n);
    assert (matvec.cols() == 1);

    MatrixXd matvecasmat = A*x;
    assert (matvecasmat.rows() == n);
    assert (matvecasmat.cols() == 1);

    //double rowmatasscal = rowmat*x;
    //VectorXd rowmatvec = rowmat*x;
    //MatrixXd rowmatvecasmat = rowmat*x;

    //matscal
    //The result is a special type
    //ScalarMultipleReturnType
    //that is assignable to a matrix
    MatrixXd matscal = A*alpha;
    assert (matscal.rows() == n);
    assert (matscal.cols() == n);

    //or a vector if it is a column matrix
    VectorXd matscalcol = colmat*alpha;

    //vecmat

    //You can't in the general case
    //cout << x*A << endl;
    //Result: run time assertion failure
    // Assertion failed: a_lhs.cols() == a_rhs.rows(), function ProductBase
    // invalid matrix product
    // if you wanted a coeff-wise or a dot product use the respective explicit functions

    //You can if the matrix is a row matrix
    MatrixXd vecrowmat = x*rowmat;
    assert (vecrowmat.rows() == n);
    assert (vecrowmat.cols() == n);


    //vecvec

    //You can't in the general case
    //cout << x*x << endl;
    //Result: run time assertion failure
    // Assertion failed: a_lhs.cols() == a_rhs.rows(), function ProductBase
    // invalid matrix product
    // if you wanted a coeff-wise or a dot product use the respective explicit functions

    //You can if the right vector is of length 1

    //cout << v1*x << endl;
    //Result: run time assertion failure
    // Assertion failed: a_lhs.cols() == a_rhs.rows(), function ProductBase
    // invalid matrix product
    // if you wanted a coeff-wise or a dot product use the respective explicit functions

    VectorXd vecv1 = x*v1;
    assert (vecv1.rows() == n);
    assert (vecv1.cols() == 1);
    MatrixXd vecv1asmat = x*v1;
    assert (vecv1asmat.rows() == n);
    assert (vecv1asmat.cols() == 1);
    assert (vecv1 == vecv1asmat);

    //double v1v1 = v1*v1;
    //Result: compile-time error
    //no viable conversion from 'const typename ProductReturnType<Matrix<double, -1, 1, 0, -1, 1>, Matrix<double, -1, 1, 0, -1, 1> >::Type'
    //(aka 'const GeneralProduct<Eigen::Matrix<double, -1, 1, 0, -1, 1>, Eigen::Matrix<double, -1, 1, 0, -1, 1>, 2>') to 'double'

    //vecscal
    //The result is a special type
    //ScalarMultipleReturnType
    //that is assignable to a matrix or vector

    VectorXd vecscal = x*alpha;
    assert (vecscal.rows() == n);
    assert (vecscal.cols() == 1);

    MatrixXd vecscalasmat = x*alpha;
    assert (vecscalasmat.rows() == n);
    assert (vecscalasmat.cols() == 1);
    assert (vecscalasmat == vecscal);

    //scalmat
    //The result is a special type
    //ScalarMultipleReturnType
    //that is assignable to a matrix, or vector for a column matrix
    MatrixXd scalmat = alpha*A;
    assert (scalmat.rows() == n);
    assert (scalmat.cols() == n);

    VectorXd scalcolmatasvec = alpha*colmat;
    assert (scalcolmatasvec.rows() == n);
    assert (scalcolmatasvec.cols() == 1);

    //VectorXd scalrowmatasvec = alpha*rowmat;
    //assert (scalrowmatasvec.rows() == 1);
    //assert (scalrowmatasvec.cols() == n);

    //scalvec
    //The result is a special type
    //ScalarMultipleReturnType
    //that is assignable to a matrix or vector
    VectorXd scalvec = x*alpha;
    assert (scalvec.rows() == n);
    assert (scalvec.cols() == 1);

    MatrixXd scalvecasmat = x*alpha;
    assert (scalvecasmat.rows() == n);
    assert (scalvecasmat.cols() == 1);
    assert (scalvecasmat == scalvec);

    //scalscal
    double scalscal = alpha * beta;



    // Quotients expressible using /
    ////////////////////////////////

    //matmatdiv
    //cout << A/B <<endl;
    //Result: compile-time error
    //invalid operands to binary expression ('MatrixXd' (aka 'Matrix<double, Dynamic, Dynamic>') and 'MatrixXd')

    //matvecdiv
    //cout << A/x << endl;
    //Result: compile-time error
    //invalid operands to binary expression ('MatrixXd' (aka 'Matrix<double, Dynamic, Dynamic>') and 'VectorXd'
    //  (aka 'Matrix<double, Dynamic, 1>'))

    //matscaldiv
    //The result is a special type
    //CwiseUnaryOp<internal::scalar_quotient1_op<typename
    //internal::traits<Matrix<double, -1, -1, 0, -1, -1> >::Scalar>, const Eigen::Matrix<double, -1, -1, 0, -1, -1> >
    //assignable to a matrix
    MatrixXd matscaldiv = A/alpha;
    assert (matscaldiv.rows() == n);
    assert (matscaldiv.cols() == n);

    VectorXd colmatscaldiv = colmat/alpha;
    assert (colmatscaldiv.rows() == n);
    assert (colmatscaldiv.cols() == 1);

    //VectorXd rowmatscaldiv = rowmat/alpha;
    //Result: run time assertion failure
    //Assertion failed: (rows() == other.rows() && cols() == other.cols()), function lazyAssign

    //vecmatdiv
    //cout << x/A << endl;
    //Result: compile-time error
    //invalid operands to binary expression ('VectorXd' (aka 'Matrix<double, Dynamic, 1>') and 'MatrixXd'
    //  (aka 'Matrix<double, Dynamic, Dynamic>'))

    //vecvecdiv
    //cout << x/y << endl;
    //Result: compile-time error
    // invalid operands to binary expression ('VectorXd' (aka 'Matrix<double, Dynamic, 1>') and 'VectorXd')

    //vecscaldiv
    //The result is a special type
    // CwiseUnaryOp<internal::scalar_quotient1_op<typename internal::traits<Matrix<double, -1, 1, 0, -1, 1> >::Scalar>, const Eigen::Matrix<double, -1, 1, 0, -1, 1> >
    //that is assignable to a vector or matrix

    VectorXd vecscaldiv = x/alpha;
    assert (vecscaldiv.rows() == n);
    assert (vecscaldiv.cols() == 1);

    MatrixXd vecscaldivasmat = x/alpha;
    assert (vecscaldivasmat.rows() == n);
    assert (vecscaldivasmat.cols() == 1);
    assert (vecscaldiv == vecscaldivasmat);

    //scalmatdiv
    //cout << alpha/A << endl;
    //Result: compile-time error
    // invalid operands to binary expression ('double' and 'MatrixXd' (aka 'Matrix<double, Dynamic, Dynamic>'))

    //scalvecdiv
    //cout << alpha/x << endl;
    //Result: compile-time error
    //invalid operands to binary expression ('double' and 'VectorXd' (aka 'Matrix<double, Dynamic, 1>'))

    //scalscaldiv
    double scalscaldiv = alpha/beta;



    // Transposes expressible using .transpose()
    ////////////////////////////////////////////

    //mattrans
    //The result of .transpose() in Eigen is a special type
    //Transpose<Matrix<double, -1, -1, 0, -1, -1> >
    //that is assignable to a matrix
    //std::string foo = A.transpose();
    //cout << typeid(A.transpose()).name() << endl;
    MatrixXd mattrans = A.transpose();
    assert (mattrans.rows() == n);
    assert (mattrans.cols() == n);

    VectorXd rowmattrans = rowmat.transpose();
    assert (rowmattrans.rows() == n);
    assert (rowmattrans.cols() == 1);

    //this is a run time assertion error
    //VectorXd colmattrans = colmat.transpose();


    //vectrans

    // The default output is a special type
    // Transpose<Matrix<double, -1, 1, 0, -1, 1> >
    // which is default matrix-like in that remembers its row shape;
    // (see a dynamic instantiation, e.g. in
    // cout << x.transpose() << endl;
    // ) that is assignable to a matrix or vector
    MatrixXd vectransasmat = x.transpose();
    assert (vectransasmat.cols() == n);
    assert (vectransasmat.rows() == 1);

    VectorXd vectrans = x.transpose();
    assert (vectrans.cols() == 1);
    assert (vectrans.rows() == n);

    //In general you cannot coerce a 1xn matrix into a n-vector:
    //VectorXd s = rowmat;
    //Result: run-time assertion failure
    //Assertion failed: (rows() == other.rows() && cols() == other.cols()), function lazyAssign

    //double foo = v1.transpose();
    //Result: compile-time error
    // no viable conversion from 'Eigen::Transpose<Matrix<double, -1, 1, 0, -1, 1> >' to 'double'

    //scaltrans
    // cout << alpha.transpose() << endl;
    //Result: compile-time error
    // error: member reference base type 'float' is not a structure or union
    // (This is a syntax error since alpha is a base type, not a class, so it
    // cannot have a transpose method defined on it.)

    //////////////////////
    // Test expressions //
    //////////////////////

    //inner product
    //The result is a special type
    //ProductReturnType<Transpose<Matrix<double, -1, 1, 0, -1, 1> >, Matrix<double, -1, 1, 0, -1, 1> >
    //that is assignable to a scalar, vector or matrix
    double innerpdtasscal = x.transpose()*y;

    VectorXd innerpdtasvec = x.transpose()*y;
    assert (innerpdtasvec.rows() == 1);
    assert (innerpdtasvec.cols() == 1);

    MatrixXd innerpdtasmat = x.transpose()*y;
    assert (innerpdtasmat.rows() == 1);
    assert (innerpdtasmat.cols() == 1);

    assert (innerpdtasmat == innerpdtasvec);

    //assert (innerpdtasmat == innerpdtasscal);
    //Result: compile-time error
    // invalid operands to binary expression ('MatrixXd' (aka 'Matrix<double, Dynamic, Dynamic>') and 'double')

    //assert (innerpdtasvec == innerpdtasscal);
    //Result: compile-time error
    // invalid operands to binary expression ('VectorXd' (aka 'Matrix<double, Dynamic, 1>') and 'double')

    //outer product
    MatrixXd outerpdt = x*y.transpose();
    assert (outerpdt.rows() == n);
    assert (outerpdt.cols() == n);

    VectorXd outerpdtxv1 = x*v1.transpose();

    //VectorXd outerpdtv1x = v1*x.transpose();
    //Result: run-time assertion failure
    //(rows() == other.rows() && cols() == other.cols()), function lazyAssign

    //quadratic form
    //cout << typeid(x.transpose()*A*x).name() << endl;
    //The result of this expression is a special internal type
    //ProductReturnType<GeneralProduct<Transpose<Matrix<double, -1, 1, 0, -1, 1> >, Matrix<double, -1, -1, 0, -1, -1>,4>, Matrix<double, -1, 1, 0, -1, 1> >
    //to a scalar, vector or matrix

    double qfasscal = x.transpose()*A*x;

    VectorXd qfasvec = x.transpose()*A*x;
    assert (qfasvec.rows() == 1);
    assert (qfasvec.cols() == 1);

    MatrixXd qfasmat = x.transpose()*A*x;
    assert (qfasmat.rows() == 1);
    assert (qfasmat.cols() == 1);
    assert (qfasmat == qfasvec);

    //bilinear form
    //cout << typeid(x.transpose()*A*y).name() << endl;
    //The result of this expression is a special internal type
    // ProductReturnType<GeneralProduct<Transpose<Matrix<double, -1, 1, 0, -1, 1> >, Matrix<double, -1, -1, 0, -1, -1>, 4>, Matrix<double, -1, 1, 0, -1, 1> >
    // that can be assigned to a scalar, vector or matrix
    double bfasscal = x.transpose()*A*y;

    VectorXd bfasvec = x.transpose()*A*y;
    assert (bfasvec.rows() == 1);
    assert (bfasvec.cols() == 1);

    MatrixXd bfasmat = x.transpose()*A*y;
    assert (bfasmat.rows() == 1);
    assert (bfasmat.cols() == 1);
    assert (bfasmat == bfasvec);

    //Rayleigh quotient
    //cout << typeid(x.transpose()*A*x/(x.transpose()*x)).name() << endl;
    //The result of this expression is a special internal type
    //CwiseUnaryOp<internal::scalar_quotient1_op<typename
    //  internal::traits<Matrix<double, 1, 1, 0, 1, 1> >::Scalar>, const Eigen::Matrix<double, 1, 1, 0, 1, 1> >
    //that can be assigned to a vector or matrix but not a scalar

    //double rqasscal = x.transpose()*A*x/(x.transpose()*x);
    //Result: compile-time error
    //no viable conversion from 'const CwiseUnaryOp<internal::scalar_quotient1_op<typename
    //  internal::traits<Matrix<double, 1, 1, 0, 1, 1> >::Scalar>, const Eigen::Matrix<double, 1, 1, 0, 1, 1> >' to 'double'

    VectorXd rqasvec = x.transpose()*A*x/(x.transpose()*x);
    assert (rqasvec.rows() == 1);
    assert (rqasvec.cols() == 1);

    MatrixXd rqasmat = x.transpose()*A*x/(x.transpose()*x);
    assert (rqasmat.rows() == 1);
    assert (rqasmat.cols() == 1);
    assert (rqasmat == rqasvec);

    /////////////////////
    // Test identities //
    /////////////////////

    //x'' == x?
    // The result of x'' is a special internal type
    // Transpose<Transpose<Matrix<double, -1, 1, 0, -1, 1> >>
    // that is equal to x and assignable to a matrix or vector
    // cout << typeid(x.transpose().transpose()).name() << endl;
    assert(x.transpose().transpose() == x);
    VectorXd xttasvec = x.transpose().transpose();
    MatrixXd xttasmat = x.transpose().transpose();
    assert (xttasvec == x);
    assert (xttasmat == x);
    assert (xttasvec == xttasmat);

    //LHS type: const Eigen::Transpose<const Eigen::GeneralProduct<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, 1, 0, -1, 1>, 4>>
    //RHS type: ProductReturnType<Transpose<Matrix<double, -1, 1, 0, -1, 1> >, Transpose<Matrix<double, -1, -1, 0, -1, -1> > >
    assert((A*x).transpose() == (x.transpose())*(A.transpose()));
    VectorXd Axtasvec = (A*x).transpose(); //Note that this assignment flattens the "row vector"!
    assert (Axtasvec.rows() == n);
    assert (Axtasvec.cols() == 1);
    MatrixXd Axtasmat = (A*x).transpose();
    assert (Axtasmat.rows() == 1);
    assert (Axtasmat.cols() == n);
    VectorXd xtAtasvec = (x.transpose())*(A.transpose());
    assert (xtAtasvec.rows() == n);
    assert (xtAtasvec.cols() == 1);
    MatrixXd xtAtasmat = (x.transpose())*(A.transpose());
    assert (xtAtasmat.rows() == 1);
    assert (xtAtasmat.cols() == n);
    assert (Axtasvec == xtAtasvec);
    //assert (Axtasvec == xtAtasmat); //fails!
    //assert (Axtasmat == xtAtasvec); //fails!
    assert (Axtasmat == xtAtasmat);

    //LHS type: ProductReturnType<GeneralProduct<Matrix<double, -1, 1, 0, -1, 1>, Transpose<Matrix<double, -1, 1, 0, -1, 1>>, 2>, Matrix<double, -1, 1, 0, -1, 1> >
    //RHS type: ProductReturnType<Matrix<double, -1, 1, 0, -1,1>, Matrix<double, 1, 1, 0, 1, 1> >
    assert((x*y.transpose())*z == x*(y.transpose()*z));
    VectorXd outerlhsasvec = (x*y.transpose())*z;
    MatrixXd outerlhsasmat = (x*y.transpose())*z;
    VectorXd outerrhsasvec = x*(y.transpose()*z);
    MatrixXd outerrhsasmat = x*(y.transpose()*z);
    assert (outerlhsasvec == outerrhsasvec);
    assert (outerlhsasvec == outerrhsasmat);
    assert (outerlhsasmat == outerrhsasvec);
    assert (outerlhsasmat == outerrhsasmat);

    //Test commutativity of scalmat and scalvec
    assert(scalmat==matscal);
    assert(scalvec==vecscal);

    return 0;
}
