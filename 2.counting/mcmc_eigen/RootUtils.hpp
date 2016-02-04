#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include <Eigen/CXX11/Tensor>

template<typename T> struct hist_trait{};

template<> struct hist_trait<TH1I>{typedef    int type; enum { ndim = 1}; };
template<> struct hist_trait<TH1F>{typedef  float type; enum { ndim = 1}; };
template<> struct hist_trait<TH1D>{typedef double type; enum { ndim = 1}; };

template<> struct hist_trait<TH2I>{typedef    int type; enum { ndim = 2}; };
template<> struct hist_trait<TH2F>{typedef  float type; enum { ndim = 2}; };
template<> struct hist_trait<TH2D>{typedef double type; enum { ndim = 2}; };

template<> struct hist_trait<TH3I>{typedef    int type; enum { ndim = 3}; };
template<> struct hist_trait<TH3F>{typedef  float type; enum { ndim = 3}; };
template<> struct hist_trait<TH3D>{typedef double type; enum { ndim = 3}; };


// This thing here is needed because stupid C++ doensn't allow for 
// partial function template specializaion
// http://stackoverflow.com/questions/5101516/why-function-template-cannot-be-partially-specialized
namespace detail {
    template<typename T, int N>
    struct F { static Eigen::Tensor<T, N> impl();};

    template<typename T>
    struct F<T, 1> {
        static Eigen::Tensor<T, 1> impl(const T & hist) { 
            int nx = hist.GetNbinsX();
            Eigen::Tensor<T, 1> result(nx);
            for(int i=0; i<nx; i++) result(i) = hist.GetBinContent(i);
            return result;
        }
    };

    template<typename T>
    struct F<T, 2> {
        static Eigen::Tensor<T, 2> impl(const T & hist) { 
            int nx = hist.GetNbinsX();
            int ny = hist.GetNbinsY();
            Eigen::Tensor<T, 2> result(nx, ny);
            for(int i=0; i<nx; i++) 
                for(int j=0; j<ny; j++) 
                    result(i,j) = hist.GetBinContent(i,j);
            return result;
        }
    };

    template<typename T>
    struct F<T, 3> {
        static Eigen::Tensor<T, 3> impl(const T & hist) { 
            int nx = hist.GetNbinsX();
            int ny = hist.GetNbinsY();
            int nz = hist.GetNbinsZ();
            Eigen::Tensor<T, 3> result(nx, ny);
            for(int i=0; i<nx; i++) 
                for(int j=0; j<ny; j++) 
                    for(int k=0; k<nz; k++) 
                        result(i,j,k) = hist.GetBinContent(i,j,k);
            return result;
        }
    };
} 

template<typename T>
Eigen::Tensor< hist_trait<T>::type, hist_trait<T>::ndim > 
toRoot(const T & hist) { 
    return detail::F<hist_trait<T>::type, hist_trait<T>::ndim>impl(hist); 
}

