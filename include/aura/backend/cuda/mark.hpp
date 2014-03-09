#ifndef AURA_BACKEND_CUDA_MARK_HPP
#define AURA_BACKEND_CUDA_MARK_HPP

#include <cuda.h>
#include <boost/move/move.hpp>
#include <aura/backend/cuda/call.hpp>
#include <aura/backend/cuda/device.hpp>

namespace aura
{
namespace backend_detail
{
namespace cuda 
{


/**
 * mark class
 */
class mark 
{

private:
	BOOST_MOVABLE_BUT_NOT_COPYABLE(mark)

public:
	/**
	 * create empty mark
	 */
	inline explicit mark() : event_(nullptr)
	{
	}

	/**
	 * create mark 
	 *
	 * @param f feed to create mark in 
	 */
	inline explicit mark(feed & f) : event_(new CUevent)
	{
		f.set();
		AURA_CUDA_SAFE_CALL(cuEventCreate(event_, CU_EVENT_DEFAULT));
		AURA_CUDA_SAFE_CALL(cuEventRecord(*event_, 
					f.get_backend_stream()));
		f.unset();
	}

	/**
	 * move constructor, move mark information here, invalidate other
	 *
	 * @param m mark to move here
	 */
	mark(BOOST_RV_REF(mark) m) : event_(m.event_)
	{
		m.event_ = nullptr;
	}

	/**
	 * move assignment, move mark information here, invalidate other
	 *
	 * @param m mark to move here
	 */
	mark& operator=(BOOST_RV_REF(mark) m)
	{
		finalize();
		event_ = m.event_;
		m.event_ = nullptr;
		return *this;
	}

	/**
	 * destroy mark 
	 */
	inline ~mark()
	{
		finalize();
	}

	
private:
	/// finalize object (called from dtor and move assign)
	void finalize()
	{
		if(nullptr != event_) {
			AURA_CUDA_SAFE_CALL(cuEventDestroy(*event_));
			delete event_;
		}
	}

	/// pointer to event
	CUevent* event_;

friend void insert(feed & f, mark & m);
friend void wait_for(mark & m);

};

/// insert marker into feed
void insert(feed & f, mark & m) 
{
	m.finalize();
	m.event_ = new CUevent;
	f.set();
	AURA_CUDA_SAFE_CALL(cuEventCreate(m.event_, CU_EVENT_DEFAULT));
	AURA_CUDA_SAFE_CALL(cuEventRecord(*m.event_, f.get_backend_stream()));
	f.unset();
}


void wait_for(mark & m) 
{
	AURA_CUDA_SAFE_CALL(cuEventSynchronize(*m.event_));

}

} // cuda 
} // backend_detail
} // aura

#endif // AURA_BACKEND_CUDA_MARK_HPP

