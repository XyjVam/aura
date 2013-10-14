#ifndef AURA_BACKEND_OPENCL_FFT_HPP
#define AURA_BACKEND_OPENCL_FFT_HPP

#include <tuple>
#include <boost/move/move.hpp>
#include <aura/backend/opencl/call.hpp>
#include <aura/backend/opencl/memory.hpp>
#include <aura/detail/svec.hpp>
#include <aura/backend/opencl/device.hpp>

namespace aura {
namespace backend_detail {
namespace opencl {

typedef svec<int, 3> fft_dim;
typedef svec<int, 3> fft_embed;

/**
 * fft class
 */
class fft {

private:
  BOOST_MOVABLE_BUT_NOT_COPYABLE(fft)
  typedef std::tuple<clfftPrecision, clfftLayout, clfftLayout> clfft_type;

public:
  enum type {
    r2c,  // real to complex  
    c2r,  // complex to real 
    c2c,  // complex to complex  
    d2z,  // double to double-complex 
    z2d,  // double-complex to double 
    z2z   // double-complex to double-complex
  };

  enum direction {
    fwd = CLFFT_FORWARD,
    inv = CLFFT_BACKWARD 
  };

  /**
   * create empty fft object without device and stream
   */
  inline explicit fft() { 
    // FIXME 
  }

  /**
   * create fft 
   *
   * @param d device to create fft for
   */
  inline explicit fft(device & d, const fft_dim & dim, const fft::type & type,
    std::size_t batch = 1, 
    const fft_embed & iembed = fft_embed(),
    std::size_t istride = 1, std::size_t idist = 0,
    const fft_embed & oembed = fft_embed(),
    std::size_t ostride = 1, std::size_t odist = 0) : device_(&d), 
    type_(type)
  {
  }

  /**
   * move constructor, move fft information here, invalidate other
   *
   * @param f fft to move here
   */
  fft(BOOST_RV_REF(fft) f)
  {  
    // FIXME 
  }

  /**
   * move assignment, move fft information here, invalidate other
   *
   * @param f fft to move here
   */
  fft& operator=(BOOST_RV_REF(fft) f)
  {
    // FIXME 
    return *this;
  }

  /**
   * destroy fft
   */
  inline ~fft() {
    device_->set();
    AURA_CUFFT_SAFE_CALL(cufftDestroy(handle_));
    device_->unset();
  }

  /**
   * set feed
   */
  void set_feed(const feed & f) {
    AURA_CUFFT_SAFE_CALL(cufftSetStream(handle_, f.get_stream()));
  }

  /**
   * return fft handle
   */
  const cufftHandle & get_handle() const {
    return handle_;
  }
  
  /**
   * return fft type
   */
  const type & get_type() const {
    return type_;
  }

  /// map fft type to cufftType
  cufftType map_type(fft::type type) {
    switch(type) {
      case r2c: 
        return CUFFT_R2C;
      case c2r: 
        return CUFFT_C2R;
      case c2c: 
        return CUFFT_C2C;
      case d2z: 
        return CUFFT_D2Z;
      case z2d: 
        return CUFFT_Z2D;
      case z2z: 
        return CUFFT_Z2Z;
      default:
        return (cufftType)0;
    }
  }

protected:
  /// device handle
  device * device_;
  
private:
    /// in-place plan 
   	clfftPlanHandle inplace_handle_; 

    /// out-of-place plan  
   	clfftPlanHandle outofplace_handle_; 

    /// fft type
    type type_;

// give free functions access to device
friend void fft_forward(memory & dst, memory & src, 
  fft & plan, const feed & f);
friend void fft_inverse(memory & dst, memory & src, 
  fft & plan, const feed & f);

};

/// initialize fft library
inline void fft_initialize() {
  clfftSetup();
}
/// finish using fft library and release all associated resources
inline void fft_terminate() {
  clfftTeardown();
}

/**
 * @brief calculate forward fourier transform
 * 
 * @param dst pointer to result of fourier transform
 * @param src pointer to input of fourier transform
 * @param plan that is used to calculate the fourier transform
 * @param f feed the fourier transform should be calculated in
 */
inline void fft_forward(memory & dst, memory & src, 
  fft & plan, const feed & f) {

}


/**
 * @brief calculate forward fourier transform
 * 
 * @param dst pointer to result of fourier transform
 * @param src pointer to input of fourier transform
 * @param plan that is used to calculate the fourier transform
 * @param f feed the fourier transform should be calculated in
 */
inline void fft_inverse(memory & dst, memory & src, 
  fft & plan, const feed & f) {

}

} // opencl 
} // backend_detail
} // aura

#endif // AURA_BACKEND_OPENCL_FFT_HPP
