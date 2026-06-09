#pragma once

#ifdef MLT_DEBUG_MEMORY
    #define REF_LOG(x) std::cout << x << std::endl;
#else
    #define REF_LOG(x)
#endif

#include <atomic>

namespace mlt::compute::core
{
    class RefCounted
    {
        public:
            mutable std::atomic_size_t mRefCount {0};
    
            void incRefCount() const noexcept
            {
                mRefCount.fetch_add(1, std::memory_order_relaxed);
            }
            
            void decRefCount() const noexcept
            {   
                mRefCount.fetch_sub(1, std::memory_order_acq_rel);
            }

            size_t getRefCount() const
            {
                return mRefCount.load();
            }
    };
    
    template <typename T>
    class Ref
    {
        private:
        T* mInstance = nullptr;

        void incRef()
        {
            if (mInstance)
            {
                mInstance->incRefCount();
                REF_LOG("incRef " << this << ": " << mInstance->mRefCount.load())
            }
        }
        
        void decRef()
        {
            if (mInstance)
            {
                REF_LOG("decRef " << this << ": " << mInstance->mRefCount.load())
                
                if (mInstance->mRefCount.fetch_sub(1, std::memory_order_acq_rel) == 1)
                {
                    REF_LOG("deleteRef: " << this)
                    delete mInstance;
                    mInstance = nullptr;
                }
            }
        }
        
        public:
        Ref() = default;
    
        Ref(T* instance) : mInstance(instance)
        {
            incRef();
        }

        Ref(const Ref& other) : mInstance(other.mInstance)
        {
            incRef();
        } 

        Ref(Ref&& other) noexcept
            : mInstance(other.mInstance)
        {
            other.mInstance = nullptr;
        }

        Ref& operator=(const Ref& other)
        {
            if (this != &other)
            {
                decRef();
                mInstance = other.mInstance;
                incRef();
            }

            return *this;           
        }

        Ref& operator=(Ref&& other) noexcept
        {
            if (this != &other)
            {
                decRef();
                mInstance = other.mInstance;
                other.mInstance = nullptr;
            }

            return *this;
        }
        
        ~Ref()
        {
            decRef();
        }

        T* operator->() const { return mInstance; }
        T& operator*() const { return *mInstance; }
        explicit operator bool() const { return mInstance != nullptr; }
    };
}

