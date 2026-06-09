#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <sstream>

namespace mlt::compute::core
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
    
        explicit SizeArray(size_t length) : mLen(length)
        {
            if (inlineSize < length)
            {
                mData = new size_t[length];
                mIsHeap = true;
            }
            else
            {
                mData = mInlineData;
                mIsHeap = false;
            }
        }

        SizeArray(std::initializer_list<size_t> initList) : mLen(initList.size())
        {
            if (inlineSize < mLen)
            {
                mData = new size_t[mLen];
                mIsHeap = true;
            }
            else
            {
                mData = mInlineData;
                mIsHeap = false;
            }

            std::copy(initList.begin(), initList.end(), mData);
        }
        
        SizeArray(const SizeArray& other) 
            : mLen(other.mLen), mIsHeap(other.mIsHeap)
        {
            if (mIsHeap)
            {
                mData = new size_t[mLen];
            }
            else
            {
                mData = mInlineData;
            }
            
            std::copy(other.mData, other.mData + mLen, mData);
        }

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
                std::copy(other.mInlineData, other.mInlineData + mLen, mInlineData);
            }
            
            other.mLen = 0;
            other.mIsHeap = false;
        }

        SizeArray& operator=(const SizeArray& other)
        {
            if (this == &other)
                return *this;
            
            SizeArray temp(other);
            *this = std::move(other);
            
            return *this;
        }
    
        SizeArray& operator=(SizeArray&& other) noexcept
        {
            if (this == &other)
                return *this;
            
            if (mIsHeap)
                delete[] mData;
            
            mLen = other.mLen;
            mIsHeap = other.mIsHeap;

            if (other.mIsHeap)
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

            return *this;
        }

        size_t operator[](size_t pos) const
        {
            if (pos >= mLen)
                throw std::out_of_range("");

            return mData[pos];
        }

        size_t& operator[](size_t pos)
        {
            if (pos > mLen)
                throw std::out_of_range("");

            return mData[pos];
        }

        ~SizeArray()
        {
            if (mIsHeap)
                delete[] mData;
        }

        size_t size() const { return mLen; }

        bool hasHeap() const { return mIsHeap; }

        size_t* getData() { return mData; }

        bool containsZero()
        {
            for (size_t i = 0; i < mLen; ++i)
                if (mData[i] == 0)
                    return true;

            return false;
        };

        std::string toString()
        {
            std::stringstream s;
            s << "SizeArray(";

            for (size_t i = 0; i < mLen-1; ++i)
                s << mData[i] << ", ";
            
            s << mData[mLen-1] << ")";

            return s.str();
        }
    };
}
