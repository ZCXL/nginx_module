#ifndef NGX_WRAPPER_HPP
#define NGX_WRAPPER_HPP
#include <boost/type_traits.hpp>
template<class T>
class NgxWrapper
{
    public:
        typedef typename boost::remove_pointer<T>::type wrapped_type;
        typedef wrapped_type* pointer_type;
        typedef wrapped_type& reference_type;
    private:
        pointer_type m_ptr = nullptr;
    protected:
        NgxWrapper(pointer_type p):m_ptr(p){}
        NgxWrapper(reference_type x):m_ptr(&x){}
        ~NgxWrapper()=default;
    public:
        pointer_type get()const
        {
            return m_ptr;
        }
        explicit operator bool()const
        {
            return get();    
        }
        operator pointer_type ()const
        {
            return get();
        }
        pointer_type operator->()const
        {
            return get();
        }
};
#endif