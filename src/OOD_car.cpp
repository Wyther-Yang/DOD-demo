#include "OOD_car.h"

CarBase::CarBase(uint16_t ioID, Vector2D const& ioPosition, Vector2D const& ioDirection)
        : m_ID(ioID),
        m_IsActivated(State::Activated),
        m_HealthPoint(100.0f),
        m_Position(ioPosition),
        m_Direction(ioDirection),
        m_RemainingFuel(125.0f),
        m_Speed(5.0f),
        m_Car(GetCarInfo())
{}

Van::Van(uint64_t ioID, Vector2D const& ioPosition, Vector2D const& ioDirection)
        : CarBase(ioID, ioPosition, ioDirection),
        m_FuelConsumptionPerMeter(10.0f)
{}

void Van::UpdateDirection(float const ioAngleMovdification)
{
        if (IsActivated() && !IsDead() && DoesCarHaveFuel())
                m_Direction.RotateDeg(ioAngleMovdification);
}
void Van::UpdateSpeed(float const ioSpeedMovdication) 
{
        if (IsActivated() && !IsDead() && DoesCarHaveFuel())
                m_Speed += ioSpeedMovdication;
}
void Van::UpdateMovement(float const ioTimeDelta) 
{
        if (IsActivated() && !IsDead() && DoesCarHaveFuel()) {
                Vector2D const new_pos = m_Position + m_Direction * (m_Speed * ioTimeDelta);
                float distance = (m_Position - new_pos).Length();
                m_RemainingFuel -= distance * m_FuelConsumptionPerMeter;
                m_Position = new_pos;
        }
}




