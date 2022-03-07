#ifndef _ECS_COMPONENT_H_
#define _ECS_COMPONENT_H_

#include <types.h>

struct BaseComponent {
private:
    inline static ComponentType _typeCount = 0;
protected:
    inline static const ComponentType GetType() {
        return _typeCount++;
    };
};

template<typename T>
struct Component : public BaseComponent {
    static const ComponentType Type;
    static const size_t Size;
};

template<typename T>
const ComponentType Component<T>::Type = BaseComponent::GetType();

template<typename T>
const size_t Component<T>::Size = sizeof(T);

#endif // _ECS_COMPONENT_H_