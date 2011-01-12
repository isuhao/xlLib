//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTypeList.h
//    Author:      Streamlet
//    Create Time: 2011-01-12
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLTYPELIST_H_E9C48089_4173_48B2_9442_5D9B052D5652_INCLUDED__
#define __XLTYPELIST_H_E9C48089_4173_48B2_9442_5D9B052D5652_INCLUDED__


#include <xl/Meta/xlMacros.h>

namespace xl
{
    struct NullType;

    template <typename H, typename T>
    struct TypeList
    {
        typedef H Head;
        typedef T Tail;
    };

    template <typename TL>
    struct TLLength;

    template <>
    struct TLLength<NullType>
    {
        enum { Value = 0 };
    };

    template <typename H>
    struct TLLength<TypeList<H, NullType>>
    {
        enum { Value = 1 };
    };

    template <typename H, typename T>
    struct TLLength<TypeList<H, T>>
    {
        enum { Value = 1 + TLLength<T>::Value };
    };

    template <typename TL, size_t i>
    struct TLAt;

    template <typename H, typename T>
    struct TLAt<TypeList<H, T>, 0>
    {
        typedef H Type;
    };

    template <typename H, typename T, size_t i>
    struct TLAt<TypeList<H, T>, i>
    {
        typedef typename TLAt<T, i - 1>::Type Type;
    };

    template <typename TL, typename T>
    struct TLMerge;

    template <>
    struct TLMerge<NullType, NullType>
    {
        typedef NullType Type;
    };

    template <typename A>
    struct TLMerge<NullType, A>
    {
        typedef TypeList<A, NullType> Type;
    };

    template <typename H, typename T>
    struct TLMerge<NullType, TypeList<H, T>>
    {
        typedef TypeList<H, T> Type;
    };

    template <typename H, typename T, typename A>
    struct TLMerge<TypeList<H, T>, A>
    {
        typedef TypeList<H, typename TLMerge<T, A>::Type> Type;
    };

    template <typename TL, size_t i>
    struct TLSplit;

    template <typename H, typename T>
    struct TLSplit<TypeList<H, T>, 0>
    {
        typedef NullType Front;
        typedef TypeList<H, T> Back;
    };

    template <typename H, typename T>
    struct TLSplit<TypeList<H, T>, 1>
    {
        typedef typename TLMerge<NullType, H>::Type Front;
        typedef typename TLMerge<NullType, T>::Type Back;
    };

    template <typename H, typename T, size_t i>
    struct TLSplit<TypeList<H, T>, i>
    {
        typedef typename TLMerge<typename TLMerge<NullType, H>::Type, typename TLSplit<T, i - 1>::Front>::Type Front;
        typedef typename TLSplit<T, i - 1>::Back Back;
    };

    template <typename TL, size_t i>
    struct TLRSplit
    {
        typedef typename TLSplit<TL, TLLength<TL>::Value - i>::Front Front;
        typedef typename TLSplit<TL, TLLength<TL>::Value - i>::Back Back;
    };

    template <typename TL, typename F, typename R>
    struct TLReplace;

    template <typename F, typename R>
    struct TLReplace<NullType, F, R>
    {
        typedef NullType Type;
    };

    template <typename T, typename F, typename R>
    struct TLReplace<TypeList<F, T>, F, R>
    {
        typedef typename TLMerge<typename TLMerge<NullType, R>::Type, typename TLReplace<T, F, R>::Type>::Type Type;
    };

    template <typename H, typename T, typename F, typename R>
    struct TLReplace<TypeList<H, T>, F, R>
    {
        typedef typename TLMerge<typename TLMerge<NullType, H>::Type, typename TLReplace<T, F, R>::Type>::Type Type;
    };

    template <typename TL>
    struct TLReverse;

    template <>
    struct TLReverse<NullType>
    {
        typedef NullType Type;
    };

    template <typename H>
    struct TLReverse<TypeList<H, NullType>>
    {
        typedef TypeList<H, NullType> Type;
    };

    template <typename H, typename T>
    struct TLReverse<TypeList<H, T>>
    {
        typedef typename TLMerge<typename TLReverse<T>::Type, typename TLMerge<NullType, H>::Type>::Type Type;
    };

} // namespace xl

#endif // #ifndef __XLTYPELIST_H_E9C48089_4173_48B2_9442_5D9B052D5652_INCLUDED__