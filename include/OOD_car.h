#pragma once

#include "carinfo.h"
#include "random.h"
#include "vector2D.h"

#include <memory>


class CarBase
{
public:
        enum class State
        {
                Activated,
                Deactivaed
        };

        CarBase(uint16_t ioID, Vector2D const& ioPosition, Vector2D const& ioDirection);

        virtual ~CarBase() = default;

        // Update API
        virtual void UpdateDirection(float const ioAngleMovdification) = 0;
        virtual void UpdateSpeed(float const ioSpeedMovdication) = 0;
        virtual void UpdateMovement(float const ioTimeDelta) = 0;
        

        // State API
        inline void SetCarActivated()
        { m_IsActivated = State::Activated; }
        inline void SetCarDeactivated()
        { m_IsActivated = State::Deactivaed; }

        // Query API
        bool IsActivated()
        { return m_IsActivated == State::Activated; }
        bool DoesCarHaveFuel()
        { return m_RemainingFuel > 0.0f; }
        bool IsDead()
        { return m_HealthPoint <= 0.0f; }

        // Action API
        void TakeDemage(float const ioDemage)
        { m_HealthPoint -= ioDemage; }


private:
        uint64_t m_ID;
        State m_IsActivated;
        float m_HealthPoint;

protected:
        Vector2D m_Position;
        Vector2D m_Direction;
        float m_RemainingFuel;
        float m_Speed;
        
        CarInfo m_Car;
};

class Van : public CarBase
{
public:
        Van(uint64_t ioID, Vector2D const& ioPosition, Vector2D const& ioDirection);

        virtual ~Van() = default;

        virtual void UpdateDirection(float const ioAngleMovdification) override;
        virtual void UpdateSpeed(float const ioSpeedMovdication) override;
        virtual void UpdateMovement(float const inTimeDelta) override;

private:
        float m_FuelConsumptionPerMeter;
};