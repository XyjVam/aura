
#ifndef AURA_BACKEND_HPP 
#define AURA_BACKEND_HPP

#include <aura/config.hpp>

#if AURA_BACKEND_CUDA

#include <aura/backend/cuda/args.hpp>
#include <aura/backend/cuda/bundle.hpp>
#include <aura/backend/cuda/call.hpp>
#include <aura/backend/cuda/device.hpp>
#include <aura/backend/cuda/feed.hpp>
#include <aura/backend/cuda/fft.hpp>
#include <aura/backend/cuda/mesh.hpp>
#include <aura/backend/cuda/init.hpp>
#include <aura/backend/cuda/invoke.hpp>
#include <aura/backend/cuda/kernel.hpp>
#include <aura/backend/cuda/memory.hpp>
#include <aura/backend/cuda/module.hpp>
#include <aura/backend/cuda/p2p.hpp>

#elif AURA_BACKEND_OPENCL

#include <aura/backend/opencl/args.hpp>
#include <aura/backend/opencl/bundle.hpp>
#include <aura/backend/opencl/call.hpp>
#include <aura/backend/opencl/device.hpp>
#include <aura/backend/opencl/feed.hpp>
#if AURA_FFT_CLFFT
#include <aura/backend/opencl/fft.hpp>
#endif // AURA_FFT_CLFFT
#include <aura/backend/opencl/mesh.hpp>
#include <aura/backend/opencl/init.hpp>
#include <aura/backend/opencl/invoke.hpp>
#include <aura/backend/opencl/kernel.hpp>
#include <aura/backend/opencl/memory.hpp>
#include <aura/backend/opencl/module.hpp>

#endif

#include <aura/backend/shared/call.hpp>

namespace aura {

namespace backend = backend_detail::AURA_BACKEND_LC;
 
}

#endif // AURA_BACKEND_HPP

