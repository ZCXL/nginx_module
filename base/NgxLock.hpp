#ifndef NGX_LOCK_HPP
#define NGX_LOCK_HPP
/*
typedef struct
{
    time_t sec;
    ngx_uint_t msec;
    ngx_int_t gmtoff;
}ngx_time_t;
*/
class NgxLock final
{
    public:
        NgxLock()=default;
        ~NgxLock()=default;
    private:
        ngx_time_t m_time=now();
    public:
        /*
        extern volatile ngx_time_t *ngx_cached_time;
        #define ngx_time() ngx_cached_time->sec
        #define ngx_timeofday() (ngx_time_t *)ngx_cached_time
        */
        static const ngx_time_t& now()
        {
            ngx_time_update();
            return *ngx_timeofday();
        }
    public:
        ngx_time_t delta()const
        {
            auto t=now();
            t.sec-=m_time.sec;
            t.msec-=m_time.msec;
            return t;
        }
        double elapsed() const
        {
            auto t=delta();
            return t.sec+t.msec*1.0/1000;
        }
        void reset()
        {
            m_time=now();
        }
};
#endif