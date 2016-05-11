#ifndef NGD_TEST_HANDLER_HPP
#define NGD_TEST_HANDLER_HPP
#include "NdgTestConf.hpp"
class NdgTestHandler final
{
    public:
        typedef NdgTestHandler this_type;
    public:
        static ngx_int_t handler(ngx_http_request_t* r)
        {
            NgxLogError(r).print("hello nginx");
            return NGX_DECLINED;
        }
        static ngx_int_t init(ngx_conf_t* cf)
        {
            auto cmcf=reinterpret_cast<ngx_http_core_main_conf_t*>(ngx_http_conf_get_module_main_conf(cf,ngx_http_core_module));
            NgxArray<ngx_http_handler_pt>arr(cmcf->phases[NGX_HTTP_REWRITE_PHASE].handlers);
            arr.push(handler);
            return NGX_OK;
        }
        static void* create(ngx_conf_t* cf)
        {
            return NgxPool(cf).alloc<NdgTestConf>();
        }
};
#endif