#ifndef NGX_STRING_HPP
#define NGX_STRING_HPP

#include <string>
#include <boost/next_prior.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/iterator/iterator_traits.hpp>

#include "NgxWrapper.hpp"
/*typedef struct
{
    size_t len;
    u_char *data;
}ngx_str_t;
*/
class NgxString final: public NgxWrapper<ngx_str_t>
{
    public:
        typedef NgxWrapper<ngx_str_t> super_type;
        typedef NgxString this_type;
        typedef boost::string_ref string_ref_type;
    public:
        NgxString(ngx_str_t& str):super_type(str){}
        ~NgxString()=default;
    public:
        const char *data()const
        {
            return reinterpret_cast<const char *>(get()->data);
        }
        std::size_t size()const
        {
            return get()->len;
        }
        bool empty()const
        {
            return !get()->data||!get()->len;
        }
        string_ref_type str()const
        {
            return string_ref_type(data(),size());
        }
    public:
        typedef u_char  char_type;
        typedef u_char* iterator;
        typedef iterator const_iterator;
        typedef boost::iterator_difference<iterator> difference_type;
    public:
        const_iterator begin()const
        {
            return get()->data;
        }
        const_iterator end()const
        {
            return get()->data+get()->len;
        }
        const char_type& front()const
        {
            return *begin();
        }
        const char_type& back()const
        {
            return *boost::prior(end());
        }
    public:
        operator ngx_int_t ()const
        {
            return ngx_atoi(get()->data,get()->len);
        }
        friend  bool operator ==(const this_type& l,const this_type& r)
        {
            return l.size()==r.size() && ngx_strncmp(l.data(),r.data(),l.size())==0;
        }
        template<typename ... Args>
        void printf(const Args& ... args)const
        {
            auto p=ngx_snprintf(get()->data,get()->len,args ...);
            get()->len=static_cast<std::size_t>(p->get()->data);
        }
        template<typename T>
        friend T& operator<<(T& o,const this_type& s)
        {
            o.write(s.data(),s.size());
            return o;
        }
};
#endif