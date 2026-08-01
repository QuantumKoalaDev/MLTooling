module;

#include <algorithm>
#include <cstddef>
#include <expected>
#include <initializer_list>
#include <new>


export module mlt.internal.compute.core.sizearray;

import mlt.core.error;

export namespace mlt::compute::core 
{
    inline constexpr size_t DEFAULT_DIM = 6;
    inline constexpr size_t SMALL_DIM = 4;
    inline constexpr size_t MID_DIM = 8;
    inline constexpr size_t LARGE_DIM = 16;

    template <size_t inlineSize = DEFAULT_DIM>
    class SizeArray
    {
        private:
        size_t mInlineData[inlineSize];
        size_t* mData = nullptr;
        size_t mLen;
        bool mIsHeap;

        public:
        SizeArray() : mData(mInlineData), mLen(inlineSize), mIsHeap(false)
        {}

        ~SizeArray()
        {
            if (mIsHeap)
                delete[] mData;
        }
    
        SizeArray(const SizeArray& other) = delete; 
        SizeArray& operator=(const SizeArray& other) = delete;

        SizeArray(SizeArray&& other) noexcept
            : mLen(other.mLen), mIsHeap(other.mIsHeap)
        {
            if (mIsHeap)
            {
                mData = other.mData;
                other.mData = nullptr;
            }
            else
            {
                mData = mInlineData;
                std::copy(other.mInlineData, other.mInlineData + other.mLen, mData);
            }
            
            other.mLen = 0;
            other.mIsHeap = false;
        }

        SizeArray& operator=(SizeArray&& other) noexcept
        {
            if (this == &other)
                return *this;
            
            if (mIsHeap)
                delete[] mData;
            
            mLen = other.mLen;
            mIsHeap = other.mIsHeap;

            if (mIsHeap)
            {
                mData = other.mData;
                other.mData = nullptr;
                other.mIsHeap = false;
            }
            else
            {
                mData = mInlineData;
                std::copy(other.mInlineData, other.mInlineData + other.mLen, mInlineData);
            }
            
            other.mLen = 0;
            other.mIsHeap = false;
            
            return *this;
        }

        size_t& operator[](size_t pos) noexcept
        {
            return mData[pos];
        }
        
        size_t operator[](size_t pos) const noexcept
        {
            return mData[pos];
        }

        size_t size() const noexcept { return mLen; }       
        bool hasHeap() const noexcept { return mIsHeap; }

        size_t* getData() noexcept { return mData; }
        const size_t* getData() const noexcept { return mData; }

        static std::expected<SizeArray<inlineSize>, mlt::core::MltError> from(size_t len) noexcept
        {
            SizeArray<inlineSize> arr;

            if (inlineSize < len)
            {
                size_t* data = new (std::nothrow) size_t[len];

                if (!data)
                    return std::unexpected(mlt::core::MltError::make(mlt::core::MltErrorType::OutOfMemory));

                arr.mData = data;
                arr.mIsHeap = true;
                arr.mLen = len;
            }
            
            return arr;
        }

        static std::expected<SizeArray, mlt::core::MltError> from(std::initializer_list<size_t> initList) noexcept
        {
            std::expected<SizeArray, mlt::core::MltError> result = from(initList.size());
            
            if (!result)
                return result;
        
            std::copy(initList.begin(), initList.end(), result.value().mData);

            return result;
        }
        
        static std::expected<SizeArray, mlt::core::MltError> copyFrom(const SizeArray& other) noexcept
        {
            std::expected<SizeArray, mlt::core::MltError> arr = from(other.mLen);
            
            if (!arr)
                return arr;

            std::copy(other.mData, other.mData + other.mLen, arr.value().mData);
            
            return arr;
        }
    };

    using DefaultSizeArray = SizeArray<>;
}
