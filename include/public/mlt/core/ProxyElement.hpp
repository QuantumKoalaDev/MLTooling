#pragma once

#include <array>
#include <cstddef>
#include <mutex>
#include <shared_mutex>

template <typename Parent, typename T, size_t Dim> class ProxyElement
{
    using SetterType = void (*)(Parent, const std::array<size_t, Dim>&, T);
    using GetterType = T (*)(Parent, const std::array<size_t, Dim>&);

    std::array<size_t, Dim> mIdx;
    std::shared_mutex& mMut;
    Parent mParent;
    SetterType mSetter;
    GetterType mGetter;

  public:
    ProxyElement(
        Parent parent, std::shared_mutex& mut, SetterType setter, GetterType getter, std::array<size_t, Dim> index
    ) : mMut(mut), mParent(parent), mSetter(setter), mGetter(getter), mIdx(index)
    {
    }

    ProxyElement& operator=(const T& value)
    {
        std::unique_lock<std::shared_mutex> lock(mMut);
        mSetter(mParent, mIdx, value);

        return *this;
    }

    operator T() const
    {
        std::shared_lock<std::shared_mutex> lock(mMut);
        return mGetter(mParent, mIdx);
    }
};
