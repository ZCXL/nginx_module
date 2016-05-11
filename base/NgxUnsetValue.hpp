#ifndef NGX_UNSET_VALUE_HPP
#define NGX_UNSET_VALUE_HPP
class NgxUnsetValue final
{
    public:
        template<typename T>
        operator T ()const
        {
            return static_cast<T>(-1);
        }
        template<typename T>
        operator T *()const
        {
            return reinterpret_cast<T*>(-1);
        }
    public:
        static const NgxUnsetValue& get()
        {
            static NgxUnsetValue const v ={};
            return v;
        }
};
#endif