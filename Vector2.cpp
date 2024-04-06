#include <vector>
#include <cmath>
#include <typeinfo>
#include "Vector2.h"

Vector2::Vector2(float x) {
    this->X = x;
    this->Y = x;
}

Vector2::Vector2(float x, float y) {
    this->X = x;
    this->Y = y;
}

void Vector2::setX(float x) {
    this->X = x;
}

void Vector2::setY(float y) {
    this->Y = y;
}

float Vector2::getX() {
    return this->X;
}

float Vector2::getY() {
    return this->Y;
}

Vector2 Vector2::Abs(Vector2 v) {
    float x, y;
    v.getX() < 0 ? x = -1 * v.getX() : x = v.getX();
    v.getY() < 0 ? y = -1 * v.getY() : y = v.getY();
    return Vector2(x, y);
}

Vector2 Vector2::Add(Vector2 v1, Vector2 v2) {
    return Vector2(v1.getX()+v2.getX(), v1.getY()+v2.getY());
}

Vector2 Vector2::Clamp(Vector2 v, Vector2 v_max, Vector2 v_min) {
    float x, y;
    v.getX() > v_max.getX() ? x = v_max.getX() : x = v.getX();
    v.getY() > v_max.getY() ? y = v_max.getY() : y = v.getY();
    v.getX() < v_min.getX() ? x = v_min.getX() : x = v.getX();
    v.getY() < v_min.getY() ? y = v_min.getY() : y = v.getY();
    return Vector2(x, y);
}

void Vector2::CopyTo(std::vector<float> v) {
    v.push_back(this->getX());
    v.push_back(this->getY());
}

void Vector2::CopyTo(std::vector<float> v, int index) {
    v[index] = this->getX();
    v[index+1] = this->getY();
}

float Vector2::DistanceSquared(Vector2 v1, Vector2 v2) {
    return (pow(v1.getX()-v2.getX(), 2) + pow(v1.getY()-v2.getY(), 2));
}

float Vector2::Distance(Vector2 v1, Vector2 v2) {
    return sqrt(DistanceSquared(v1, v2));
}

Vector2 Vector2::Divide(Vector2 v, float a) {
    return Vector2(v.getX()/a, v.getY()/a);
}

Vector2 Vector2::Divide(Vector2 v1, Vector2 v2) {
    return Vector2(v1.getX()/v2.getX(), v1.getY()/v2.getY());
}

float Vector2::Dot(Vector2 v1, Vector2 v2) {
    return (v1.getX()*v2.getX() + v1.getY()*v2.getY());
}

bool Vector2::Equals(Vector2 v) {
    if (this->getX() == v.getX() && this->getY() == v.getY())
        return true;
    return false;
}

template<typename T>
bool Vector2::Equals(T obj) {
    if (typeid(obj) == typeid(this)) {
        if (Equals(this, obj))
            return true;
    }
    return false;
}

float Vector2::LengthSquared() {
    return (pow(this->getX(), 2) + pow(this->getY(), 2));
}

float Vector2::Length() {
    return sqrt(this->LengthSquared());
}

Vector2 Vector2::Max(Vector2 v1, Vector2 v2) {
    float x, y;
    v1.getX() > v2.getX() ? x = v1.getX() : x = v2.getX();
    v1.getY() > v2.getY() ? y = v1.getY() : y = v2.getY();
    return Vector2(x, y);
}

Vector2 Vector2::Min(Vector2 v1, Vector2 v2) {
    float x, y;
    v1.getX() < v2.getX() ? x = v1.getX() : x = v2.getX();
    v1.getY() < v2.getY() ? y = v1.getY() : y = v2.getY();
    return Vector2(x, y);
}

Vector2 Vector2::Multiply(float a, Vector2 v) {
    return Vector2(a*v.getX(), a*v.getY());
}

Vector2 Vector2::Multiply(Vector2 v, float a) {
    Multiply(a, v);
}

Vector2 Vector2::Multiply(Vector2 v1, Vector2 v2) {
    return Vector2(v1.getX()*v2.getX(), v1.getY()*v2.getY());
}

Vector2 Vector2::Negate(Vector2 v) {
    return Vector2(-1 * v.getX(), )
}