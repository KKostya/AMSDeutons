
// This thing here is needed because stupid C++ doensn't allow for 
// partial function template specializaion
// http://stackoverflow.com/questions/5101516/why-function-template-cannot-be-partially-specialized
namespace {
namespace detail {
    template<typename T, int N>
    struct dump { static Eigen::Tensor<T, N> impl();};

    template<typename T>
    struct dump<T, 1> {
        static void impl(const Eigen::Tensor<T, 1> & x) {
            for(int i = 0; i < x.dimension(0); i++ ) { std::cout << x(i) << ", "; }
            std::cout << "\n";
        }
    };

    template<typename T>
    struct dump<T, 2> {
        static void impl(const Eigen::Tensor<T, 2> & x) {
            for(int i = 0; i < x.dimension(0); i++ )
            {
                for(int j = 0; j < x.dimension(1); j++ ) { std::cout << x(i,j) << ", "; }
                std::cout << "\n";
            }
        }
    };

    template<typename T>
    struct dump<T, 3> {
        static void impl(const Eigen::Tensor<T, 3> & x) {
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
    };
}} 

template<typename T, int N> 
void dump(const Eigen::Tensor<T, N> & x) { detail::dump<T,N>::impl(x); }
