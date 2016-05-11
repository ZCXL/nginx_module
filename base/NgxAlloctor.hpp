#ifndef NGX_ALLOCTOR_HPP
#define NGX_ALLOCTOR_HPP
#include "NgxWrapper.hpp"
template<typename T>
class NgxAlloctor: public NgxWrapper<ngx_pool_t>
{
    public:
        typedef NgxWrapper<ngx_pool_t> super_type;
        typedef NgxAlloctor this_type;
    public:
        typedef std::size_t size_type;
        typedef T* pointer;
        typedef T value_type;
    public:
        NgxAlloctor(ngx_pool_t *p):super_type(p){}
        ~NgxAlloctor()=default;
    public:
        pointer allocate(size_type n)
        {
            return reinterpret_cast<pointer>(ngx_pnalloc(get(),n*sizeof(T)));
        }
        void deallocate(pointer ptr,size_type n)
        {
            boost::ignore_unused(n);
            ngx_pfree(get(),ptr);
        }
};
#include<vector>
template<typename T>
using NgxStdVector=std::vector<T,NgxAlloctor<T> >;
#endif