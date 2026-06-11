#pragma once

#include <algorithm>
#include <cstddef>
#include <format>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <utility>

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
            *this = std::move(temp);
            
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
            if (pos >= mLen)
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
        const size_t* getData() const { return mData; };
        
        std::span<size_t> span() { return std::span<size_t>(mData, mLen); }
        std::span<const size_t> span() const { return std::span<const size_t>(mData, mLen);};

        bool containsZero()
        {
            for (size_t i = 0; i < mLen; ++i)
                if (mData[i] == 0)
                    return true;

            return false;
        };
    };
}

template <size_t N>
std::ostream& operator<<(std::ostream& os, const mlt::compute::core::SizeArray<N>& arr)
{
    if (arr.size() == 0)
        return os << "SizeArray()";

    os << "SizeArray(";

    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (i > 0)
            os << ", ";
            
        os << arr[i];
    }
    
    return os << ")";
}

template <size_t N>
struct std::formatter<mlt::compute::core::SizeArray<N>>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }
    
    auto format(const mlt::compute::core::SizeArray<N>& arr,
                std::format_context& ctx) const
    {
        auto out = ctx.out();
        
        if (arr.size() == 0)
            return std::format_to(out, "SizeArray()");
        
        out = std::format_to(out, "SizeArray(");
    
        for (size_t i = 0; i < arr.size(); ++i)
        {
            if (i)
                out = std::format_to(out, ", ");
            out = std::format_to(out, "{}", arr[i]);
        }
    
        return out;
    }
};

