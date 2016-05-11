#ifndef NGX_LOG_HPP
#define NGX_LOG_HPP
#include "NgxWrapper.hpp"
/*
struct ngx_log_s {
    ...
    ngx_uint_t log_level;
    ngx_log_t* next;
}ngx_log_t;
#define NGX_LOG_STDERR  0
#define NGX_LOG_EMERG   1
#define NGX_LOG_ALERT   2
#define NGX_LOG_CRIT    3
#define NGX_LOG_ERR     4
#define NGX_LOG_WARN    5
#define NGX_LOG_NOTICE  6
#define NGX_LOG_INFO    7
#define NGX_LOG_DEBUG   8
*/
template<ngx_uint_t level=NGX_LOG_DEBUG>
class NgxLog final: public NgxWrapper<ngx_log_t>
{
    public:
        typedef NgxWrapper<ngx_log_t> super_type;
        typedef NgxLog this_type;
    public:
        NgxLog(ngx_log_t* l):super_type(l){}
        NgxLog(ngx_log_t& l):super_type(l){}
        template<typename T>
        NgxLog(T* x):super_type(x->log){}
        NgxLog(ngx_http_request_t* r):NgxLog(r->connection){}
        ~NgxLog()=default;
    public:
        template<typename ... Args>
        void print(const char* fmt,const Args& ... args)const
        {
            ngx_log_error(level,get(),0,fmt,args...);
        }
        template<typename ... Args>
        void print(ngx_err_t err,const Args& ... args)const
        {
            ngx_log_error(level,get(),err,args...);
        }
};
typedef NgxLog<NGX_LOG_DEBUG>   NgxLogDebug;
typedef NgxLog<NGX_LOG_INFO>    NgxLogInfo;
typedef NgxLog<NGX_LOG_WARN>    NgxLogWarning;
typedef NgxLog<NGX_LOG_ERR>     NgxLogError;
#endif