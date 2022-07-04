#include "vector2D.h"

Vector2D operator+ (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X + inB.m_X, inA.m_Y + inB.m_Y);
}

Vector2D operator- (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X - inB.m_X, inA.m_Y - inB.m_Y);
}

Vector2D operator* (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X * inB.m_X, inA.m_Y * inB.m_Y);
}

Vector2D operator/ (const Vector2D& inA, const Vector2D& inB)
{
    return Vector2D(inA.m_X / inB.m_X, inA.m_Y / inB.m_Y);
}

Vector2D operator+ (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue + inVector.m_X, inValue + inVector.m_Y);
}

Vector2D operator- (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue - inVector.m_X, inValue - inVector.m_Y);
}

Vector2D operator* (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue * inVector.m_X, inValue * inVector.m_Y);
}

Vector2D operator/ (const Vector2D& inVector, const float inValue)
{
    return Vector2D(inValue / inVector.m_X, inValue / inVector.m_Y);
}

float Distance(const Vector2D& inA, const Vector2D& inB)
{
    return sqrt((inA.m_X - inB.m_X) * (inA.m_X - inB.m_X) + (inA.m_Y - inB.m_Y) * (inA.m_Y - inB.m_Y));
}
