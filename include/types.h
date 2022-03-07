#ifndef _ECS_TYPES_H_
#define _ECS_TYPES_H_

#include <stdint.h>
#include <bitset>

using Entity = uint32_t;
using ComponentType = uint8_t;
using SystemID = uint32_t;

const Entity MAX_ENTITIES = 1000000;        // 1 000 000 entities
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif // _ECS_TYPES_H_