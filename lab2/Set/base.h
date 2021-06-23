#ifndef BASE_
#define BASE_

#include <cstddef>

class base {
    protected:
        size_t size = 0;

    public:
        virtual bool empty() const { return size == 0; } 
        virtual void clear() = 0;
        virtual ~base() = default;
};




#endif // BASE_
