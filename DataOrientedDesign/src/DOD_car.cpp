#include "DOD_car.h"

namespace Detail {

        void SelectCarsToPipe(CarsStore const& inStore,
                                unsigned int const inNumOfcars,
                                vector<unsigned int>& outCarsToUpdate);

        void TransfersDirectionDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                                vector<Vector2D> const& inDirections,
                                                vector<Vector2D>& outDirectionsToUpdate);
        void UpdateDirections(vector<float> const& ioAngleGapData,
                                vector<Vector2D>& outDirectionsToUpdate);

        void TransfersSpeedDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                        vector<float> const& inSpeedData,
                                        vector<float>& outSpeedDataToUpdate);

        void UpdateSpeedData(vector<float> const& ioSpeedModificationData,
                                vector<float>& outSpeedDataToUpdate);

        void TransfersMovementDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                                vector<Vector2D> const& inPositions,
                                                vector<Vector2D> const& inDirections,
                                                vector<float> const& inSpeedData,
                                                vector<MovementData>& outMovementDataToUpdate);

        void UpdateMovementData(float const ioTimeGapData, vector<MovementData>& outMovementDataToUpdate);

        void TransferFuelDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                        vector<float> const& inFuelData,
                                        vector<float> const& inFuelConsumptionPerMeter,
                                        vector<MovementData> const& inMovementDataToUpdate,
                                        vector<FuelData>& outFuelDataToUpdate);     

        void UpdateFuelData(vector<FuelData>&  outFuelDataToUpdate);                                                                                                                          



        void CarsStoreTransientData::clear()
        {
                m_CarsToUpdate.clear();
                m_DirectionsToUpdate.clear();
                m_SpeedDataToUpdate.clear();
                m_MovementDataToUpdate.clear();
                m_FuelDataToUpdate.clear();
        }


} // namespace Detail

CarsStore::CarsStore() : m_TransientData(new Detail::CarsStoreTransientData{}),
                                m_NumOfCars(0)
{}

void CarsStore::ToDemageCars(unsigned int const ioCarIdx, float const inDemage)
{
        m_HealthData[ioCarIdx] -= inDemage;
}

void CarsStore::CreateCar(uint64_t const ioCarId, 
                                Vector2D const& ioPosition, 
                                Vector2D const& ioDirection)
{
        m_IDs.emplace_back(ioCarId);
        m_ActivatedStates.emplace_back(State::Activated);
        m_Positions.emplace_back(ioPosition);
        m_Directions.emplace_back(ioDirection);
        m_speedData.emplace_back(1.0f);
        m_FuelData.emplace_back(100.0f);
        m_FuelConsumptionPerMeterData.emplace_back(1.0f);
        m_HealthData.emplace_back(100.0f);
        m_CarInfoData.emplace_back(GetCarInfo());

        ++m_NumOfCars;
}

void CarsStore::ToUpdateCars(float const ioTimeGapData, 
                                vector<float> const& ioAngleGapData,
                                vector<float> const& ioSpeedModificationData)
{
        using namespace Detail;

        SelectCarsToPipe
        (
                *this,
                m_NumOfCars,
                m_TransientData->m_CarsToUpdate
        );

        TransfersDirectionDataToPipe
        (
                m_TransientData->m_CarsToUpdate,
                m_Directions,
                m_TransientData->m_DirectionsToUpdate
        );

        UpdateDirections
        (
                ioAngleGapData,
                m_TransientData->m_DirectionsToUpdate
        );

        TransfersSpeedDataToPipe
        (
                m_TransientData->m_CarsToUpdate,
                m_speedData,
                m_TransientData->m_SpeedDataToUpdate
        );

        UpdateSpeedData
        (
                ioSpeedModificationData,
                m_TransientData->m_SpeedDataToUpdate
        );

        TransfersMovementDataToPipe
        (
                m_TransientData->m_CarsToUpdate,
                m_Positions,
                m_Directions,
                m_speedData,
                m_TransientData->m_MovementDataToUpdate
        );

        UpdateMovementData
        (
                ioTimeGapData,
                m_TransientData->m_MovementDataToUpdate
        );

        TransferFuelDataToPipe
        (
                m_TransientData->m_CarsToUpdate,
                m_FuelData,
                m_FuelConsumptionPerMeterData,
                m_TransientData->m_MovementDataToUpdate,
                m_TransientData->m_FuelDataToUpdate
        );

        UpdateFuelData
        (
                m_TransientData->m_FuelDataToUpdate
        );

        int i = 0;
        for (auto& car_idx : m_TransientData->m_CarsToUpdate) {
                WriteDataBack(m_Directions[car_idx], m_TransientData->m_DirectionsToUpdate[i]);
                WriteDataBack(m_speedData[car_idx], m_TransientData->m_SpeedDataToUpdate[i]);
                WriteDataBack(m_Positions[car_idx], m_TransientData->m_MovementDataToUpdate[i].m_Position);
                WriteDataBack(m_FuelData[car_idx], m_TransientData->m_FuelDataToUpdate[i].m_Surplus);

                ++i;
        }

        // clear pipeline
        m_TransientData->clear();
}


namespace Detail {

        void SelectCarsToPipe(CarsStore const& inStore,
                                unsigned int const inNumOfcars,
                                vector<unsigned int>& outCarsToUpdate)
        {
                for (unsigned int i = 0; i < inNumOfcars; ++i) {
                        if (inStore.IsCarActivated(i) &&
                                inStore.DoesCarHaveFuel(i) &&
                                        !inStore.IsCarDead(i))
                        outCarsToUpdate.emplace_back(i);                                        
                }
        }                                

        void TransfersDirectionDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                                vector<Vector2D> const& inDirections,
                                                vector<Vector2D>& outDirectionsToUpdate)
        {
                for (unsigned int cur_idx : inCarsToUpdate) 
                        outDirectionsToUpdate.emplace_back(inDirections[cur_idx]);
                
        }

        void UpdateDirections(vector<float> const& ioAngleGapData,
                                vector<Vector2D>& outDirectionsToUpdate)
        {
                int idx = 0;
                for (Vector2D& direction : outDirectionsToUpdate) 
                        direction.RotateDeg(ioAngleGapData[idx++]);
                
        }                                

        void TransfersSpeedDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                        vector<float> const& inSpeedData,
                                        vector<float>& outSpeedDataToUpdate)
        {
                for (auto cur_idx : inCarsToUpdate)
                        outSpeedDataToUpdate.emplace_back(inSpeedData[cur_idx]);
        }                                        

        void UpdateSpeedData(vector<float> const& ioSpeedModificationData,
                                vector<float>& outSpeedDataToUpdate)
        {
                int i = 0;
                for (auto& cur_speed : outSpeedDataToUpdate)
                        cur_speed += ioSpeedModificationData[i++];
        }                                

        void TransfersMovementDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                                vector<Vector2D> const& inPositions,
                                                vector<Vector2D> const& inDirections,
                                                vector<float> const& inSpeedData,
                                                vector<MovementData>& outMovementDataToUpdate)
        {
                for (auto cur_idx : inCarsToUpdate) {
                        outMovementDataToUpdate.push_back
                        ({
                                inPositions[cur_idx],
                                inDirections[cur_idx],
                                inSpeedData[cur_idx],
                                0.0f
                        });
                }
        }                                                

        void UpdateMovementData(float const ioTimeGapData, vector<MovementData>& outMovementDataToUpdate)
        {
                for (auto& movement_data : outMovementDataToUpdate) {
                        Vector2D const& pos = movement_data.m_Position;
                        Vector2D const& dir = movement_data.m_Direction;
                        float const speed = movement_data.m_Speed * ioTimeGapData;
                        Vector2D const new_position = pos + dir * speed;
                        movement_data.m_Position = new_position;
                        movement_data.m_Distance = (pos - new_position).Length();
                }
        }

        void TransferFuelDataToPipe(vector<unsigned int> const& inCarsToUpdate,
                                        vector<float> const& inFuelData,
                                        vector<float> const& inFuelConsumptionPerMeter,
                                        vector<MovementData> const& inMovementDataToUpdate,
                                        vector<FuelData>& outFuelDataToUpdate)
        {
                int i = 0;
                for (auto cur_idx : inCarsToUpdate) {
                        outFuelDataToUpdate.push_back
                        ({
                                inFuelData[cur_idx],
                                inFuelConsumptionPerMeter[cur_idx],
                                inMovementDataToUpdate[i].m_Distance
                        });

                        ++i;
                }
        }                                        

        void UpdateFuelData(vector<FuelData>&  outFuelDataToUpdate)
        {
                for (auto& fuel_data : outFuelDataToUpdate) 
                        fuel_data.m_Surplus -= fuel_data.m_Distance * fuel_data.m_FuelComsumptionPerMeter;
        }

} // namespace Detail