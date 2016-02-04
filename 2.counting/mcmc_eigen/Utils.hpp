

template<int N> void dump(const Eigen::Tensor<double, N> & x) {}

template<>
void dump<3>(const Eigen::Tensor<double, 3> & x)
{
    for(int i = 0; i < x.dimension(0); i++ )
    {
        for(int k = 0; k < x.dimension(2); k++ ) 
        {
            for(int j = 0; j < x.dimension(1); j++ ) { std::cout << x(i,j,k) << ", "; }
            std::cout << " | ";
        }
        std::cout << "\n";
    }
}

template<>
void dump<2>(const Eigen::Tensor<double, 2> & x)
{
    for(int i = 0; i < x.dimension(0); i++ )
    {
        for(int j = 0; j < x.dimension(1); j++ ) { std::cout << x(i,j) << ", "; }
        std::cout << "\n";
    }
}
