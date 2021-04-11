#ifndef STDLIB__FUNCS
#define STDLIB__FUNCS

template<class Arg1, class Arg2, class Result>
struct binary_function
{
    typedef Arg1 first_arg_type;
    typedef Arg2 second_arg_type;
    typedef Result result_type;
};

template <class T>
struct less: binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::second_arg_type
        second_arg_type;
    typedef typename binary_function<T, T, bool>::first_arg_type
        first_arg_type;
    typedef typename binary_function<T, T, bool>::result_type
        result_type;

    result_type operator() (const first_arg_type &x, const second_arg_type &y) const {
        return x < y;
    }
};

#endif // STDLIB__FUNCS
