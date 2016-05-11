#ifndef NGX_ARRAY_HPP
#define NGX_ARRAY_HPP
#include "NgxWrapper.hpp"
#include "NgxPool.hpp"
/*
typedef struct
{
    void *elts;
    ngx_uint_t  nelts;
    size_t      size;
    ngx_uint_t nalloc;
    ngx_pool_t* pool;
}ngx_array_t;
*/
template<typename T>
class NgxArray final:public NgxWrapper<ngx_array_t>
{
    public:
        typedef NgxWrapper<ngx_array_t> super_type;
        typedef NgxArray    this_type;
    public:
        NgxArray(const NgxPool&p,ngx_uint_t n=10):super_type(p.array<T>(n)){}
        NgxArray(ngx_array_t* arr):super_type(arr){}
        NgxArray(ngx_array_t& arr):super_type(arr){}
        ~NgxArray()=default;
    private:
        T* elts()const
        {
            return reinterpret_cast<T*>(get()->elts);
        }
    public:
        ngx_uint_t size()const
        {
            return get()?get()->size:0;
        }
        T& operator[](ngx_uint_t i)const
        {
            NgxException::require(i<size()&&get());
            return elts()[i];
        }
    public:
        T& prepare()const
        {
            auto tmp=ngx_array_push(get());
            NgxException::require(tmp);
            return *reinterpret_cast<T*>(tmp);
        }
        void push(const T&x)const
        {
            prepare()=x;
        }
    public:
        template<typename V>
        void visit(V v)const
        {
            auto p=elts();
            for(ngx_uint_t i=0;i<size();i++)
                v(p[i]);
        }
};
#endif