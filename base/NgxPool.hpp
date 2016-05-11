#ifndef NGX_POOL_HPP
#define NGX_POOL_HPP
#include <boost/type_traits.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/tti/has_member_data.hpp>
#include <boost/tti/member_type.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/string_ref.hpp>
#include "NgxWrapper.hpp"
#include "NgxException.hpp"

class NgxPool final : public NgxWrapper<ngx_pool_t>
{
    public:
        typedef NgxWrapper<ngx_pool_t> super_type;
        typedef NgxPool this_type;
    public:
        NgxPool(ngx_pool_t* p):super_type(p){}
        ~NgxPool() = default;
        template<typename T>
        NgxPool(T *x): NgxPool(x->pool){}
    public:
        template<typename T, bool no_exception = false>
        T * palloc()const
        {
            auto p=ngx_pcalloc(get(),sizeof(T));
            if(!p){
                if(no_exception)
                    return nullptr;
                NgxException::raise();
            }
            assert(p);
            return new (p) T();
        }
    public:
        template<typename T>
        T* alloc()const
        {
            return palloc<T,false>();
        }
    public:
        template<typename T>
        T* alloc_noexcept()const
        {
            return palloc<T,true>();
        }
    public:
        template<typename T>
        T* nalloc(std::size_t n)const
        {
            auto p=ngx_pcalloc(get(),n);
            NgxException::require(p);
            return reinterpret_cast<T*>(p);
        }
    public:
        template<typename T,typename ... Args>
        T* construct(const Args& ...args)const
        {
            auto p=ngx_pcalloc(get(),sizeof(T));
            NgxException::require(p);
            return new (p) T(args ...);
        }
    public:
        template<typename F,typename T>
        ngx_pool_cleanup_t* cleanup(F func,T* data,std::size_t size=0)const
        {
            auto p=ngx_pool_cleanup_add(get(),size);
            NgxException::require(p);
            p->handler=func;
            if(data)
                p->data=data;
            return p;
        }
    public:
        template<typename T>
        static void destory(void* p)
        {
            (reinterpret_cast<T*>(p))->~T();
        }
    public:
        template<typename T>
        void cleanup(T* data)const
        {
            cleanup(&this_type::destory<T>,data);
        }
    public:
        template<typename T>
        ngx_array_t* array(ngx_uint_t n=10)const
        {
            auto p=ngx_array_create(get(),n,sizeof(T));
            NgxException::require(p);
            return p;
        }
};
#endif
