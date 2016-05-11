#ifndef NDG_TEST_CONF_HPP
#define NDG_TEST_CONF_HPP
#include "NgxAll.hpp"
class NdgTestConf final
{
    public:
        typedef NdgTestConf this_type;
    public:
        NdgTestConf()=default;
        ~NdgTestConf()=default;
    public:
        ngx_flag_t enabled=NgxUnsetValue::get();
    public:
        static void *create(ngx_conf_t* cf)
        {
            return NgxPool(cf).alloc<NdgTestConf>();
        }
};
#endif