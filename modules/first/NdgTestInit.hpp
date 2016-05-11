#ifndef NDG_TEST_INIT_HPP
#define NDG_TEST_INIT_HPP

#include "NdgTestConf.hpp"
#include "NdgTestHandler.hpp"

class NdgTestInit final
{
public:
    typedef NdgTestConf conf_type;
    typedef NdgTestHandler handler_type;
    typedef NdgTestInit this_type;
    public:
        static ngx_command_t* cmds()
        {
            static ngx_command_t n[] =
            {
                {
                    ngx_string("ndg_test"),
                    NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
                    ngx_conf_set_flag_slot,
                    NGX_HTTP_LOC_CONF_OFFSET,
                    offsetof(conf_type, enabled)
                },

                ngx_null_command
            };

            return n;
        }   
    public:
        static ngx_http_module_t* ctx()
        {
            static ngx_http_module_t c=
            {
                nullptr,
                &NdgTestHandler::init,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                &NdgTestHandler::create,
                nullptr
            };
            return &c;
        }
    public:
        static const ngx_module_t& module(){
            static ngx_module_t m=
            {
                NGX_MODULE_V1,
                ctx(),
                cmds(),
                NGX_HTTP_MODULE,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                NGX_MODULE_V1_PADDING
            };
            return m;
        }
};
#endif