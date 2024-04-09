#ifndef C_PROJECTS_VECTOR2_H
#define C_PROJECTS_VECTOR2_H

#include <vector>

class Vector2D {
protected:
    float X;
    float Y;
public:
    void setX(float x);
    void setY(float y);
    float getX();
    float getY();
    //x == y
    Vector2D(float x);
    //x != y
    Vector2D(float x, float y);
    //Absolutely vector
    Vector2D Abs(Vector2D v);
    //Sum vector
    Vector2D Add(Vector2D v1, Vector2D v2);
    //min >= v >= max
    Vector2D Clamp(Vector2D v, Vector2D v_max, Vector2D v_min);
    //vectot -> array
    void CopyTo(std::vector<float> v);
    //vectot -> array[i]
    void CopyTo(std::vector<float> v, int index);
    //dist v1 <-> v2
    float Distance(Vector2D v1, Vector2D v2);
    //dist^2 v1 <-> v2
    float DistanceSquared(Vector2D v1, Vector2D v2);
    //vector / const
    Vector2D Divide(Vector2D v, float a);
    //vector / vector
    Vector2D Divide(Vector2D v1, Vector2D v2);
    //(vector1, vector2)
    float Dot(Vector2D v1, Vector2D v2);
    //vector =?= object
    template<class T>
    bool Equals(T obj);
    //vector1 =?= vector2
    bool Equals(Vector2D v);
    //|vector|
    float Length();
    //|vector|^2
    float LengthSquared();
    //vector(max x, max y)
    Vector2D Max(Vector2D v1, Vector2D v2);
    //vector(min x, min y)
    Vector2D Min(Vector2D v1, Vector2D v2);
    //const * vector
    Vector2D Multiply(float a, Vector2D v);
    //vector * const
    Vector2D Multiply(Vector2D x, float a);
    //vector * vector
    Vector2D Multiply(Vector2D v1, Vector2D v2);
    //vector -> -vector
    Vector2D Negate(Vector2D v);
    //vector / len
    Vector2D Normalize(Vector2D v);
    //vector -> (plane) vector
    Vector2D Reflect(Vector2D v, Vector2D n);
    //vector(x^2, y^2)
    Vector2D SquareRoot(Vector2D v);
    //vector1 - vector2
    Vector2D Subtract(Vector2D v1, Vector2D v2);
    //<x, y>
    std::string ToString();
};
//vector(x1+x2, y1+y1)
Vector2D operator+(Vector2D &v1, Vector2D &v2);
//vector(x/a, y/a)
Vector2D operator/(Vector2D &v, float a);
//vector1 =?= vector2
bool operator==(Vector2D &v1, Vector2D &v2);
//vector1 !?= vector2
bool operator!=(Vector2D &v1, Vector2D &v2);
//vector(x*a, y*a)
Vector2D operator*(Vector2D &v, float a);
//vector(x*a, y*a)
Vector2D operator*(float a, Vector2D &v);
//vector(x1*x2, y1*y2)
Vector2D operator*(Vector2D &v1, Vector2D &v2);
//vector1 - vector2
Vector2D operator-(Vector2D &v1, Vector2D &v2);
//vector(-x, -y)
Vector2D operator-(Vector2D &v);

#endif //C_PROJECTS_VECTOR2_H
