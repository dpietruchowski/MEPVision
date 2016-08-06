#ifndef GENERATOR_H
#define GENERATOR_H
#include <map>

template <typename T>
struct CreationCounter
{
    T callbackFunction;
    int nCreation;
};

template <typename T>
class Generator
{
public:
    Generator();
public:
    void registerCallback(double probability, T callback);
    const CreationCounter<T>& createRandom();
private:
    typedef std::map<double, CreationCounter<T>> Callbacks;
    Callbacks callbacks_;
};

template <typename T>
Generator<T>::Generator()
{

}

template <typename T>
void Generator<T>::registerCallback(double probability,
                                    T callback)
{
    if(callbacks_.empty())
    {
        CreationCounter<T> counter = { callback, 0 };
        callbacks_.insert(std::make_pair(probability, counter));
    } else
    {
        //Check if adding probability is greater than 1
        //If yes throw exception
        typename Callbacks::iterator last = callbacks_.end();
        last--;
        double threshold = last->first + probability;

        if(threshold > 1)
            throw "Nie mozna dodac. Za duze prawdopodobienstwo";

        CreationCounter<T> counter = { callback, 0 };
        callbacks_.insert(std::make_pair(threshold, counter));
    }
}

template <typename T>
const CreationCounter<T>& Generator<T>::createRandom()
{
    double random = double(std::rand()) / (RAND_MAX);

    if(callbacks_.empty())
        throw "Pusto. Nie mozna wylosowac";

    //Check if sum of probabilities is equal to 1
    //If not throw exception
    typename Callbacks::const_iterator last = callbacks_.end();
    last--;

    if(last->first != 1)
        throw "Suma prawdopodobienstw nie jest rowna jeden";

    typename Callbacks::iterator it = callbacks_.lower_bound(random);
    //it--;

    it->second.nCreation++;
    return it->second;
}

#endif // GENERATOR_H
