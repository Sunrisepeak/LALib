#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <ostream>

namespace Matrix {

    /**
     * 
     * pre-declaration of template-friend in Vector
     * 
    */

    template<typename, typename>
    class Vector;

    template<typename T, typename SC>
    std::ostream &
    operator<<(std::ostream &, const Vector<T, SC> &);

    template<typename T, typename SC>
    Vector<T, SC> 
    operator+(const Vector<T, SC> &, const Vector<T, SC> &);

    template<typename T, typename SC>
    T operator*(const Vector<T, SC> &, const Vector<T, SC> &);

    template<typename T, typename SeqContainer = std::vector<T>>
    class Vector {

        /**
         * IO and Op : one-to-one of relationship between template-instance and template-instance 
        */

        friend std::ostream &
        operator<<<T, SeqContainer>(std::ostream &, const Vector &);

        friend Vector
        operator+<T, SeqContainer>(const Vector &, const Vector &);
        
        friend T 
        operator*<T, SeqContainer>(const Vector &, const Vector &);

    public:

        using valueType        = typename SeqContainer::value_type;
        using reference         = typename SeqContainer::reference;
        using const_reference   = typename SeqContainer::const_reference;
        using sizeType         = typename SeqContainer::size_type;
        using containerType    = SeqContainer;

        /* ctor */

        Vector() = default;

        Vector(const sizeType &);

        Vector(const sizeType &, const T &);

        Vector(const Vector &);

        Vector(SeqContainer);

        ~Vector();

        sizeType
        size() const;

        T & 
        operator[](const sizeType &index);

        Vector
        operatorX(const Vector &obj);


    private:
        SeqContainer c;
    };  // Vector_End
    
    /**
     * contructor function
     * 
    */
    template<typename T, typename SC>
    Vector<T, SC>::Vector(const sizeType &sz) : c(sz, 0) {}

    template<typename T, typename SC>
    Vector<T, SC>::Vector(const sizeType &sz, const T &obj) : c(sz, obj) {}

    template<typename T, typename SC>
    Vector<T, SC>::Vector(const Vector<T, SC> &obj) : c{ obj.c } {}

    template<typename T, typename SC>
    Vector<T, SC>::Vector(SC sc) : c{ sc } {}

    template<typename T, typename SC>
    Vector<T, SC>::~Vector() {}

    /**
     * basic function
     * 
     * 
    */
    template<typename T, typename SC>   
    typename Vector<T, SC>::sizeType
    Vector<T, SC>::size() const { return c.size(); }
    

    /**
     * overload operator
     * 
     * 
    */
    template<typename T, typename SC>
    T & Vector<T, SC>::operator[](const sizeType &index) {
        if (index >= size() && index < 0)
            throw std::out_of_range("index is out of range: " + std::to_string(index));
        return c[index];
    }

    /**
     * friend function of Vector
     * 
    */
    
    template<typename T, typename SC>
    std::ostream &
    operator<<(std::ostream &out, const Vector<T, SC> &vct) {
        out << "[" << vct.c[0];
        for (typename Vector<T, SC>::sizeType i = 1; i < vct.c.size(); i++) {
            out << ", " << vct.c[i];
        }
        out << "]";
        return out;
    }

    template<typename T, typename SC>
    Vector<T, SC> 
    operator+(const Vector<T, SC> &v1, const Vector<T, SC> &v2) {
        if(v1.c.size() != v2.c.size())
            throw std::invalid_argument("size1 != size2");
        auto temp = Vector<T, SC>(v1.c.size());
        for (decltype(v1.size()) i = 0; i < v1.size(); i++) {
            temp[i] = v1.c[i] + v2.c[i];
        }
        return temp;
    }

    template<typename T, typename SC>
    T operator*(const Vector<T, SC> &v1, const Vector<T, SC> &v2) {
        if (v1.size() != v2.size())
            throw std::invalid_argument("size1 != size2");
        T ans = 0;
        for (decltype(v1.size()) i = 0; i < v1.size(); i++) {
            ans += v1.c[i] * v2.c[i];
        }
        return ans;
    }

    

    /*  v1 x v2 */
    template<typename T, typename SC>
    Vector<T, SC>
    Vector<T, SC>::operatorX(const Vector<T, SC> &obj) {
        if (c.size() != 3 || obj.c.size() != 3) 
            throw std::runtime_error("must have at least one dimension with 3 elements");
        return SC{
            c[1] * obj.c[2] - c[2] * obj.c[1],      //  | i  j  k |
            c[2] * obj.c[0] - c[0] * obj.c[2],      //  | x  y  z | -> c
            c[0] * obj.c[1] - c[1] * obj.c[0]       //  | a  b  c | -> obj.c
        };
    }
    
};  // namespace_End

#endif
