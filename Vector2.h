#ifndef C_PROJECTS_VECTOR2_H
#define C_PROJECTS_VECTOR2_H

#include <vector>

class Vector2 {
protected:
    float X;
    float Y;
public:
    void setX(float x);
    void setY(float y);
    float getX();
    float getY();
    //x == y
    Vector2(float x);
    //x != y
    Vector2(float x, float y);
    //Absolutely vector
    Vector2 Abs(Vector2 v);
    //Sum vector
    Vector2 Add(Vector2 v1, Vector2 v2);
    //min >= v >= max
    Vector2 Clamp(Vector2 v, Vector2 v_max, Vector2 v_min);
    //vectot -> array
    void CopyTo(std::vector<float> v);
    //vectot -> array[i]
    void CopyTo(std::vector<float> v, int index);
    //dist v1 <-> v2
    float Distance(Vector2 v1, Vector2 v2);
    //dist^2 v1 <-> v2
    float DistanceSquared(Vector2 v1, Vector2 v2);
    //vector / const
    Vector2 Divide(Vector2 v, float a);
    //vector / vector
    Vector2 Divide(Vector2 v1, Vector2 v2);
    //(vector1, vector2)
    float Dot(Vector2 v1, Vector2 v2);
    //vector =?= object
    template<class T>
    bool Equals(T obj);
    //vector1 =?= vector2
    bool Equals(Vector2 v);
    //vector(max x, max y)
    Vector2 Max(Vector2 v1, Vector2 v2);
    //vector(min x, min y)
    Vector2 Min(Vector2 v1, Vector2 v2);
    //const * vector
    Vector2 Multiply(float a, Vector2 v);
    //vector * const
    Vector2 Multiply(Vector2 x, float a);
    //vector * vector
    Vector2 Multiply(Vector2 v1, Vector2 v2);
    //vector -> -vector
    Vector2 Negate(Vector2 v);


    //|vector|
    float Length();
    //|vector|^2
    float LengthSquared();
};


#endif //C_PROJECTS_VECTOR2_H
