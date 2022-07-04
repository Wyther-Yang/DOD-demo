#include "carinfo.h"
#include "vector2D.h"
#include "random.h"

#include <vector>
#include <memory>
#include <utility>

namespace Detail {

        struct MovementData
        {
                Vector2D m_Position;
                Vector2D m_Direction;
                float m_Speed;
                float m_Distance;
        };

        struct FuelData
        {
                float m_Surplus;
                float m_FuelComsumptionPerMeter;
                float m_Distance;
        };

        struct CarsStoreTransientData
        {
                vector<unsigned int> m_CarsToUpdate;
                vector<Vector2D> m_DirectionsToUpdate;
                vector<float> m_SpeedDataToUpdate;
                vector<MovementData> m_MovementDataToUpdate;
                vector<FuelData> m_FuelDataToUpdate;

                void clear();
        };


        template<typename T>
        inline void WriteDataBack(T& inLeft, T& inRight)
        {
                inLeft = inRight;
        }
        
} // namespace Detail

class CarsStore
{
public: 
        enum class State
        {
                Activated,
                Deactivated
        };

        CarsStore();
        ~CarsStore() = default;
        CarsStore(CarsStore const&) = delete;
        CarsStore& operator=(CarsStore const&) = delete;

        //  State API
        inline void SetCarActivated(unsigned int ioCarIdx)
        { m_ActivatedStates[ioCarIdx] = State::Activated; }

        inline void SetCarDeactivated(unsigned int ioCarIdx)
        { m_ActivatedStates[ioCarIdx] = State::Deactivated; }

        // Init API
        void CreateCar(uint64_t const ioCarId, Vector2D const& ioPosition, Vector2D const& inDirection);
        
        // Action API
        void ToDemageCars(unsigned int const inCarIdx, float const inDemage);
        void ToUpdateCars(float const ioTimeGapData, vector<float> const& ioAngleGapData, vector<float> const& ioSpeedModificationData);

        // query API
        inline bool IsCarActivated(unsigned int const inCarIdx) const
        { return m_ActivatedStates[inCarIdx] == State::Activated; }

        inline bool DoesCarHaveFuel(unsigned int const inCarIdx) const
        { return m_FuelData[inCarIdx] > 0.0f; }
        
        inline bool IsCarDead(unsigned int const inCarIdx) const
        { return m_HealthData[inCarIdx] <= 0.0f; }

private:
        // data
        vector<uint64_t> m_IDs;
        vector<State> m_ActivatedStates;
        vector<Vector2D> m_Positions;
        vector<Vector2D> m_Directions;
        vector<float> m_speedData;
        vector<float> m_FuelData;
        vector<float> m_FuelConsumptionPerMeterData;
        vector<float> m_HealthData;
        vector<CarInfo> m_CarInfoData;

        // pipeline factory
        unique_ptr<Detail::CarsStoreTransientData> m_TransientData;

        // total num of cars
        unsigned int m_NumOfCars;
};