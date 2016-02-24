#include <iostream>
#include <Eigen/CXX11/Tensor>
#include <Eigen/SVD>

void f(void)
{
    Eigen::Tensor<double, 2> t(4,3);
    t.setValues({{0, 100, 200}, {300, 400, 500},
                 {600, 700, 800}, {900, 1000, 1100}});
    std::cout << "Here is the tensor t:" << std::endl << t << std::endl;
    
    Eigen::Map<Eigen::MatrixXd> m(t.data(), 4, 3);
    std::cout << "Here is the matrix m:" << std::endl << m << std::endl;
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(m, Eigen::ComputeThinU | Eigen::ComputeThinV);
    std::cout << "Its singular values are:" << std::endl << svd.singularValues() << std::endl;
    std::cout << "Its left  singular vectors are the columns of the thin U matrix:" << std::endl << svd.matrixU() << std::endl;
    std::cout << "Its right singular vectors are the columns of the thin V matrix:" << std::endl << svd.matrixV() << std::endl;
    Eigen::Vector4d rhs(1, 0, 0, 0);
    std::cout << "Now consider this rhs vector:" << std::endl << rhs << std::endl;
    std::cout << "A least-squares solution of m*x = rhs is:" << std::endl << svd.solve(rhs) << std::endl;
}

void r(void)
{
    int R = 4;
    Eigen::VectorXd v(20);
    v << 0,1,2,3,4,4,3,2,1,0;

    Eigen::MatrixXd m(R)
}



int main(void)
{
    f();
    return 0;
}
