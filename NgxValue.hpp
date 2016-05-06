#ifndef NGX_VALUE_HPP
#define NGX_VALUE_HPP
#include<NgxUnsetValue.hpp>
class NgxValue final
{
    public:
        NgxValue() = default;
        ~NgxValue() = default;
    public:
        template<typename T>
        static bool invalid(const T &x)
        {
            return v== static_cast<T>(NgxUnsetValue::get());
        }
        template<typename T,typename U>
        static void init(T& x,const U&v)
        {
            if(invalid(x)){
                x=v;
            }
        }
        template<typename T,typename U,typename V>
        static void merge(T& c,const U& p,const V &d)
        {
            if(invalid(c)){
                c=invalid(p)?d:p;
            }
        }
        template<typename T,typename ... Args>
        static void unset(T& v,Args& ... args)
        {
            v=NgxUnsetValue::get();
            unset(args...);
        }
        static void unset(){}
};
#endif