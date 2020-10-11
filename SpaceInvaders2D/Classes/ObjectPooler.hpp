//
//  ObjectPooler.hpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 5.10.2020.
//

#ifndef ObjectPooler_hpp
#define ObjectPooler_hpp

#include <list>

template <class T> class ObjectPooler
{
public:
    ObjectPooler() { }

public:
    void pushBackToPool(T* obj) {
        _pool.push_back(obj);
    }
    
    T* createOne() {
        if (_pool.empty()) {
            return new T;
        }
        T* first = _pool.front();
        _pool.pop_front();
        return first;
    }

    void destroy() {
        typename std::list<T*>::iterator it;
        for (it = _pool.begin(); it != _pool.end(); ++it) {
            delete *it;
        }
    }
    
    int count()
    {
        return _pool.size();
    }

protected:
    std::list<T*> _pool;
};

#endif /* ObjectPooler_hpp */
