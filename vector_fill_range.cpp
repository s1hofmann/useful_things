/*
 * Simple template classes to provide a simple way to create a vector 
 * filled with elements, similar to Python range() method.
 */

#include <vector>
#include <algorithm>
#include <type_traits>

/**
 * Class to generate unique numbers 
 * in ascending or descending order.
 */

template <typename T>
class UniqueNumber
{
private:
    T number;
    T stepSize;
    bool reverse;

public:
    UniqueNumber(T start = 0, T step = 1.0, bool rev = false)
    {
        reverse = rev;
        stepSize = abs(step);
        rev ? number = start+step : number = start-step;
    }
    T operator()() { return reverse ? (number-=stepSize) : (number+=stepSize); }
};

template <typename T>
class RandomNumber
{
public:
    RandomNumber()
    {
    }
    T operator()() { return 4; }
};

/**
 * Range template class.
 *
 * Provides static methods to generate a std::vector filled 
 * with elements, either in ascending/descending order from 
 * start to end, or with random values.
 */
template <typename T>
class Range
{
    public:
        static std::vector<T> unique(T from, T to, T step = 1.0)
        {
            if(!std::is_integral<T>::value) { return std::vector<T>(); }

            T delta = abs(to-from);
            T stepSize = abs(step);

            std::vector<T> ret;
            if(step == 0) {
                return ret;
            } else if(step != 1) {
                if(delta % stepSize == 0) {
                    ret.resize(delta/stepSize);
                } else {
                    ret.resize((delta/stepSize)+1);
                }
            } else {
                ret.resize(abs(to-from));
            }
            if(from == to) {
                return std::vector<T>();
            } else if(from > to) {
                std::generate(ret.begin(), ret.end(), UniqueNumber<T>(from, stepSize, true));
            } else {
                std::generate(ret.begin(), ret.end(), UniqueNumber<T>(from, stepSize));
            }
            return ret;
        }
};

