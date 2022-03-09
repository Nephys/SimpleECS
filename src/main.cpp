#include <iostream>
#include <time.h>
#include <random>

#include <scene.h>


// Config
const int TOTAL_RUNTIME = 10;
const int TOTAL_ENTITY_COUNT = 10500;
const float DEFAULT_GRAVITY_MPS = 9.806;


// Sample components
struct vec3 {
    float x = 0;
    float y = 0;
    float z = 0;
};

struct Transform : public Component<Transform> {
    vec3 position;
    vec3 rotation;
    vec3 scale;
};

struct RigidBody : public Component<RigidBody> {
    vec3 velocity;
    float gravity = DEFAULT_GRAVITY_MPS;
};

struct Script : public Component<Script> {
    char path[512] = "scripts/sample.lua";
};


int main(int argc, char* argv[]) {
    printf("Registering components\n");
    ComponentManager::RegisterComponent<Transform>();
    ComponentManager::RegisterComponent<RigidBody>();
    ComponentManager::RegisterComponent<Script>();

    printf("Creating scene & %d entities\n", TOTAL_ENTITY_COUNT);
    Scene* scene = new Scene();
    
    printf("\n-------------[ENTITIES]-------------\n");
    for (int i = 0; i < TOTAL_ENTITY_COUNT; i++) {
        Entity entity = scene->CreateEntity();
        Transform* entityTransform = scene->AddComponent<Transform>(entity);
        RigidBody* entityRigidBody = scene->AddComponent<RigidBody>(entity);
        
        if(i % 3 == 0) {
            scene->AddComponent<Script>(entity);
        }

        vec3 position;
        position.x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 50.025;
        position.y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * i * 100.25;
        position.z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * -i * 200.5;

        entityTransform->position = position;
        if(i < 10) {
            printf("Entity%u starting position: (%.2f, %.2f, %.2f)\n", entity, position.x, position.y, position.z);
        }
    }
    printf("-------------[ENTITIES]-------------\n\n");

    printf("Running sample gravity system for %ds with gravity set to %.2fm/s\n", TOTAL_RUNTIME, DEFAULT_GRAVITY_MPS);

    double runtime = 0;
    clock_t timer = clock();
    while (runtime < TOTAL_RUNTIME) {
        double deltaTime = ((double)clock() - timer) / CLOCKS_PER_SEC;
        timer = clock();

        for(Entity entity : scene->Fetch<Transform, RigidBody>()) {
            Transform* transform = scene->GetComponent<Transform>(entity);
            RigidBody* rigidbody = scene->GetComponent<RigidBody>(entity);

            rigidbody->velocity.y = deltaTime * -rigidbody->gravity;        // Not necessary but why not this is a demo
            transform->position.y += rigidbody->velocity.y;

            // Uncomment the line below to nuke your CPU :D
            // printf("%.2fs - [%u] transform->position.y = %.2f\n", runtime, entity, transform->position.y);
        }

        for(Entity entity : scene->Fetch<Script>()) {
            Script* script = scene->GetComponent<Script>(entity);
            // Do something with the script
        }
        runtime += deltaTime;
    }

    printf("\n-------------[ENTITIES]-------------\n");
    for (int i = 0; i < 10; i++) {
        Entity entity = (Entity)i;
        vec3 position = scene->GetComponent<Transform>(entity)->position;
        printf("Entity%u final position: (%.2f, %.2f, %.2f)\n", entity, position.x, position.y, position.z);
    }
    printf("-------------[ENTITIES]-------------\n\n");
    
    return 0;
}