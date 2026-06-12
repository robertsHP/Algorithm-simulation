


//https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern

// class Singleton
// {
//     public:
//         static Singleton& getInstance()
//         {
//             static Singleton    instance; // Guaranteed to be destroyed.
//                                   // Instantiated on first use.
//             return instance;
//         }
//     private:
//         Singleton() {}                    // Constructor? (the {} brackets) are needed here.

//     public:
//         Singleton(Singleton const&) = delete;
//         void operator=(Singleton const&)  = delete;

//         // Note: Scott Meyers mentions in his Effective Modern
//         //       C++ book, that deleted functions should generally
//         //       be public as it results in better error messages
//         //       due to the compilers behavior to check accessibility
//         //       before deleted status
// };


//https://stackoverflow.com/questions/34519073/inherit-singleton


#include <type_traits>

template<typename T>
class Singleton {
    protected:
        Singleton() noexcept = default;
        Singleton(const Singleton&) = delete;

        Singleton& operator=(const Singleton&) = delete;

        virtual ~Singleton() = default; // to silence base class Singleton<T> has a
        // non-virtual destructor [-Weffc++]

    public:
        static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
        {
            // Guaranteed to be destroyed.
            // Instantiated on first use.
            // Thread safe in C++11
            static T instance{};

            return instance;
        }
};

