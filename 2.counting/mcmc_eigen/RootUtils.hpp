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
namespace {
namespace detail {
    template<typename T, int N>
    struct r2t { static Eigen::Tensor<typename hist_trait<T>::type, N> impl();};

    template<typename T>
    struct r2t<T, 1> {
        typedef Eigen::Tensor<typename hist_trait<T>::type, 1> TensorType;
        static TensorType impl(T * hist) { 
            int nx = hist->GetNbinsX();
            TensorType result(nx);
            for(int i=0; i<nx; i++) result(i) = hist->GetBinContent(i);
            return result;
        }
    };

    template<typename T>
    struct r2t<T, 2> {
        typedef Eigen::Tensor<typename hist_trait<T>::type, 2> TensorType;
        static TensorType impl(T * hist) { 
            int nx = hist->GetNbinsX();
            int ny = hist->GetNbinsY();
            TensorType result(nx, ny);
            for(int i=0; i<nx; i++) 
                for(int j=0; j<ny; j++) 
                    result(i,j) = hist->GetBinContent(i,j);
            return result;
        }
    };

    template<typename T>
    struct r2t<T, 3> {
        typedef Eigen::Tensor<typename hist_trait<T>::type, 3> TensorType;
        static TensorType impl(T * hist) { 
            int nx = hist.GetNbinsX();
            int ny = hist.GetNbinsY();
            int nz = hist.GetNbinsZ();
            TensorType result(nx, ny);
            for(int i=0; i<nx; i++) 
                for(int j=0; j<ny; j++) 
                    for(int k=0; k<nz; k++) 
                        result(i,j,k) = hist->GetBinContent(i,j,k);
            return result;
        }
    };
}} 

template<typename T>
Eigen::Tensor< typename hist_trait<T>::type, hist_trait<T>::ndim > 
root_to_tensor(T * hist) { 
    return detail::r2t<T, hist_trait<T>::ndim>::impl(hist); 
}

