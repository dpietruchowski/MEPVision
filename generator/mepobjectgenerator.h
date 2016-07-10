#ifndef MEPOBJECTGENERATOR_H
#define MEPOBJECTGENERATOR_H

#include "generator.h"

#include <map>
#include <memory>

class MEPObject;
typedef std::shared_ptr<MEPObject> MEPObjectPtr;

class MEPObjectGenerator
{
public:
    typedef MEPObjectPtr (*CreateObjectFunction)(unsigned int);

public:
    MEPObjectGenerator();
public:
    MEPObjectPtr createRandomPtr();
    void registerObject(double probability, CreateObjectFunction function);

private:
    Generator<CreateObjectFunction> generator_;
};

#endif // MEPOBJECTGENERATOR_H