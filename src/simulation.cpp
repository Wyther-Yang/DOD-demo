#include "cars.h"

void DoSimilateForDOD(int args, char** argv)
{
        int ioNumOfCars = atoi(argv[1]);
        int ioNumOfFrame = atoi(argv[2]);

        CarsStore store;

        vector<float> direction_modification_input;
        vector<float> speed_modification_input;

        // init stage
        for (int i = 0; i < ioNumOfCars; ++i) 
        {
                uint64_t const id = RandomInt();
                auto const pos = Vector2D(RandomFloat(), RandomFloat());
                auto const dir = Vector2D(RandomFloat(), RandomFloat()).Normalized();
                store.CreateCar(id, pos, dir);

                if (unlikely((i % 10) == 0))
                        store.SetCarDeactivated(i);
                
                direction_modification_input.emplace_back(RandomFloat(-2.5f, -2.5f));
                speed_modification_input.emplace_back(RandomFloat(0.0f, 0.2f));
        }

        // refresh frame
        for (int i = 0; i < ioNumOfFrame; ++i) 
        {
                for (int j = 0; j < ioNumOfCars; ++j) 
                {
                        if (j % 2 == 0 && !store.IsCarDead(j))
                                store.ToDemageCars(j, 5.0f);
                }   
                
                float const for_time = RandomTime();
                store.ToUpdateCars
                (       for_time, 
                        direction_modification_input, 
                        speed_modification_input
                );
        }
}

void DoSimilateForOOD(int args, char** argv)
{
        int ioNumOfCars = atoi(argv[1]);
        int ioNumOfFrame = atoi(argv[2]);

        vector<unique_ptr<CarBase>> cars;

        for (int i = 0; i < ioNumOfCars; ++i) 
        {
                uint64_t const id = RandomInt();
                auto const pos = Vector2D(RandomFloat(), RandomFloat());
                auto const dir = Vector2D(RandomFloat(), RandomFloat()).Normalized();
                cars.emplace_back(make_unique<Van>(id, pos, dir));

                if (i % 10 == 0)
                        cars[i]->SetCarDeactivated();
        }

        for (int i = 0; i < ioNumOfFrame; ++i) 
        {
                for (int j = 0; j < ioNumOfCars; ++j) 
                {
                        if (j % 2 == 0 && !cars[j]->IsDead())
                                cars[j]->TakeDemage(5.0f);
                
                        cars[j]->UpdateDirection(RandomFloat());
                        cars[j]->UpdateSpeed(RandomFloat());
                        cars[j]->UpdateMovement(RandomTime());
                }   
        }
}