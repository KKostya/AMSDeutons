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

template<typename Scalar, int DIM> struct tensor_trait{};

template<> struct tensor_trait<double, 3>  { typedef TH3D roottype; };
template<> struct tensor_trait<double, 2>  { typedef TH2D roottype; };
template<> struct tensor_trait<double, 1>  { typedef TH1D roottype; };
                                                                      
template<> struct tensor_trait< float, 3>  { typedef TH3F roottype; };
template<> struct tensor_trait< float, 2>  { typedef TH2F roottype; };
template<> struct tensor_trait< float, 1>  { typedef TH1F roottype; };
                                                                      
template<> struct tensor_trait<   int, 3>  { typedef TH3I roottype; };
template<> struct tensor_trait<   int, 2>  { typedef TH2I roottype; };
template<> struct tensor_trait<   int, 1>  { typedef TH1I roottype; };

// This thing here is needed because stupid C++ doensn't allow for 
// partial function template specializaion
// http://stackoverflow.com/questions/5101516/why-function-template-cannot-be-partially-specialized
namespace {
namespace detail {

    // r2t are the implementaions of the root_to_tensor function
    template<typename T, int N>
    struct r2t { static Eigen::Tensor<typename hist_trait<T>::type, N> impl();};

    template<typename T>
    struct r2t<T, 1> {
        typedef Eigen::Tensor<typename hist_trait<T>::type, 1> TensorType;
        static TensorType impl(T * hist, bool overflow) { 
            int xt = overflow ? 1 : 0;
            int nx = hist->GetNbinsX() + 2*xt;
            TensorType result(nx);
            for(int i=0; i<nx; i++) result(i) = hist->GetBinContent(i+1-xt);
            return result;
        }
    };

    template<typename T>
    struct r2t<T, 2> {
        typedef Eigen::Tensor<typename hist_trait<T>::type, 2> TensorType;
        static TensorType impl(T * hist, bool overflow) { 
            int xt = overflow ? 1 : 0;
            int nx = hist->GetNbinsX() + 2 * xt;
            int ny = hist->GetNbinsY() + 2 * xt;
            TensorType result(nx, ny);
            for(int i = 0; i < nx; i++) 
                for(int j = 0; j < ny; j++) 
                    result(i,j) = hist->GetBinContent(i+1-xt,j+1-xt);
            return result;
        }
    };

    template<typename T>
    struct r2t<T, 3> {
        typedef Eigen::Tensor<typename hist_trait<T>::type, 3> TensorType;
        static TensorType impl(T * hist, bool overflow) { 
            int xt = overflow ? 1 : 0;
            int nx = hist->GetNbinsX() + 2*xt;
            int ny = hist->GetNbinsY() + 2*xt;
            int nz = hist->GetNbinsZ() + 2*xt;
            TensorType result(nx, ny, nz);
            for(int i=0; i<nx; i++) 
                for(int j=0; j<ny; j++) 
                    for(int k=0; k<nz; k++) 
                        result(i,j,k) = hist->GetBinContent(i+1-xt,j+1-xt,k+1-xt);
            return result;
        }
    };


    // t2r are the implementaions of the tensor_to_root function
    template<typename T, int N>
    struct t2r { static T * impl(const Eigen::Tensor<typename hist_trait<T>::type, N> & tensor, T *);};

    template<typename Scalar>
    struct t2r<Scalar, 1> {
        typedef typename tensor_trait<Scalar, 1>::roottype  HistType;
        static HistType * impl( const Eigen::Tensor<Scalar, 1> & tensor, HistType * hist, bool overflow) { 
            int xt = overflow ? 1 : 0;
            int nx = hist->GetNbinsX() + 2*xt;
            for(int i=0; i<nx; i++) hist->SetBinContent(i+1-xt, tensor(i));
            return hist;
        }
    };

    template<typename Scalar>
    struct t2r<Scalar, 2> {
        typedef typename  tensor_trait<Scalar, 2>::roottype  HistType;
        static HistType * impl( const Eigen::Tensor<Scalar, 2> & tensor, HistType * hist, bool overflow) { 
            int xt = overflow ? 1 : 0;
            int nx = hist->GetNbinsX() + 2 * xt;
            int ny = hist->GetNbinsY() + 2 * xt;
            for(int i = 0; i < nx; i++) 
                for(int j = 0; j < ny; j++) 
                    hist->SetBinContent(i+1-xt,j+1-xt, tensor(i,j));
            return hist;
        }
    };

    template<typename Scalar>
    struct t2r<Scalar, 3> {
        typedef typename tensor_trait<Scalar, 3>::roottype  HistType;
        static HistType * impl( const Eigen::Tensor<Scalar, 3> & tensor, HistType * hist, bool overflow) { 
            int xt = overflow ? 1 : 0;
            int nx = hist->GetNbinsX() + 2*xt;
            int ny = hist->GetNbinsY() + 2*xt;
            int nz = hist->GetNbinsZ() + 2*xt;
            for(int i=0; i<nx; i++) 
                for(int j=0; j<ny; j++) 
                    for(int k=0; k<nz; k++) 
                        hist->SetBinContent(i+1-xt,j+1-xt,k+1-xt,tensor(i,j,k));
            return hist;
        }
    };

}} 

template<typename T>
Eigen::Tensor< typename hist_trait<T>::type, hist_trait<T>::ndim > 
root_to_tensor(T * hist, bool overflow = false) { 
    return detail::r2t<T, hist_trait<T>::ndim>::impl(hist, overflow); 
}

template<typename Scalar, int N>
typename tensor_trait<Scalar,N>::roottype * tensor_to_root(
    const Eigen::Tensor<Scalar, N> & tensor, 
    typename tensor_trait<Scalar, N>::roottype * hist,  
    bool overflow = false){
    return detail::t2r<Scalar, N>::t2r::impl(tensor, hist, overflow);
}
