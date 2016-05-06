#ifndef NGX_POOL_HPP
#define NGX_POOL_HPP
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
};
#endif
