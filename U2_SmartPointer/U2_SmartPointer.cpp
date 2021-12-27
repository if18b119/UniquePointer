#include <iostream>
#include <memory>
#include "MyUniquePointer.h"
#include <string.h>
#include <cassert>
using namespace thebettersmartpointer;
class Entity {
private:
    int id=NULL;
public:
    Entity()
    {
    }
    Entity(int id)
    {
        this->id = id;
    }
    int GetID() noexcept { return id; }
    void SetID(int id) { this->id = id; }
};

void TestWorkingSmartPointer()
{
    int i = 0;
    MyUniquePointer<Entity> entityPointer(new Entity(1));
    MyUniquePointer<std::string> stringPointer(new std::string("Hello World"));   
    assert(*stringPointer.get() == "Hello World");
}

void TestSwap()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    MyUniquePointer<Entity> entityPointer2(new Entity(2));

    entityPointer1.swap(entityPointer2);
    assert(entityPointer1->GetID()== 2);
    assert(entityPointer2->GetID()== 1);
}


void TestSwapWithInSelf()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    entityPointer1.swap(entityPointer1);
    assert(entityPointer1->GetID() == 1);
}

void TestSwapWithNullptr()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    MyUniquePointer<Entity> null_ptr;
    entityPointer1.swap(null_ptr);
    assert(!entityPointer1);
    assert(null_ptr);


}

void TestBoolOperator()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    MyUniquePointer<Entity> null_ptr;
    entityPointer1.swap(null_ptr);
    assert(!entityPointer1);
    assert(null_ptr);
}

void TestRelease()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    MyUniquePointer<Entity> entityPointer12(entityPointer1.release());
    assert(entityPointer12->GetID() == 1);
    assert(!entityPointer1);
}

void TestMoveConstructor()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    MyUniquePointer<Entity> entityPointer12 (std::move(entityPointer1));
    assert(entityPointer12->GetID()== 1);
    assert(!entityPointer1);
}

void TestMoveAssignment()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    MyUniquePointer<Entity> entityPointer12 = std::move(entityPointer1);
    assert(entityPointer12->GetID() == 1);
    assert(!entityPointer1);
}

void TestReset()
{
    MyUniquePointer<Entity> entityPointer1(new Entity(1));
    entityPointer1.reset();
    assert(!entityPointer1);
}

void RunTests()
{
    std::cout << "Running Test 1 - ";
    TestWorkingSmartPointer();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 2 - ";
    TestSwap();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 3 - ";
    TestSwapWithInSelf();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 4 - ";
    TestSwapWithNullptr();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 5 - ";
    TestBoolOperator();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 6 - ";
    TestRelease();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 7 - ";
    TestMoveConstructor();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 8 - ";
    TestMoveAssignment();
    std::cout << "Passed!" << std::endl;
    std::cout << "Running Test 9 - ";
    TestReset();
    std::cout << "Passed!" << std::endl;
}

int main()
{
  
    RunTests();


    
}

