#include <vector>
#include <cmath>
#include <typeinfo>
#include <string>
#include "Vector2D.h"

Vector2D::Vector2D(float x) {
    this->X = x;
    this->Y = x;
}

Vector2D::Vector2D(float x, float y) {
    this->X = x;
    this->Y = y;
}

void Vector2D::setX(float x) {
    this->X = x;
}

void Vector2D::setY(float y) {
    this->Y = y;
}

float Vector2D::getX() {
    return this->X;
}

float Vector2D::getY() {
    return this->Y;
}

Vector2D Vector2D::Abs(Vector2D v) {
    float x, y;
    v.getX() < 0 ? x = -1 * v.getX() : x = v.getX();
    v.getY() < 0 ? y = -1 * v.getY() : y = v.getY();
    return Vector2D(x, y);
}

Vector2D Vector2D::Add(Vector2D v1, Vector2D v2) {
    return Vector2D(v1.getX() + v2.getX(), v1.getY() + v2.getY());
}

Vector2D Vector2D::Clamp(Vector2D v, Vector2D v_max, Vector2D v_min) {
    float x, y;
    v.getX() > v_max.getX() ? x = v_max.getX() : x = v.getX();
    v.getY() > v_max.getY() ? y = v_max.getY() : y = v.getY();
    v.getX() < v_min.getX() ? x = v_min.getX() : x = v.getX();
    v.getY() < v_min.getY() ? y = v_min.getY() : y = v.getY();
    return Vector2D(x, y);
}

void Vector2D::CopyTo(std::vector<float> v) {
    v.push_back(this->getX());
    v.push_back(this->getY());
}

void Vector2D::CopyTo(std::vector<float> v, int index) {
    v[index] = this->getX();
    v[index + 1] = this->getY();
}

float Vector2D::DistanceSquared(Vector2D v1, Vector2D v2) {
    return (pow(v1.getX() - v2.getX(), 2) + pow(v1.getY() - v2.getY(), 2));
}

float Vector2D::Distance(Vector2D v1, Vector2D v2) {
    return sqrt(DistanceSquared(v1, v2));
}

Vector2D Vector2D::Divide(Vector2D v, float a) {
    return Vector2D(v.getX() / a, v.getY() / a);
}

Vector2D Vector2D::Divide(Vector2D v1, Vector2D v2) {
    return Vector2D(v1.getX() / v2.getX(), v1.getY() / v2.getY());
}

float Vector2D::Dot(Vector2D v1, Vector2D v2) {
    return (v1.getX() * v2.getX() + v1.getY() * v2.getY());
}

bool Vector2D::Equals(Vector2D v) {
    if (this->getX() == v.getX() && this->getY() == v.getY())
        return true;
    return false;
}

template<typename T>
bool Vector2D::Equals(T obj) {
    if (typeid(obj) == typeid(this)) {
        if (Equals(this, obj))
            return true;
    }
    return false;
}

float Vector2D::LengthSquared() {
    return (pow(this->getX(), 2) + pow(this->getY(), 2));
}

float Vector2D::Length() {
    return sqrt(this->LengthSquared());
}

Vector2D Vector2D::Max(Vector2D v1, Vector2D v2) {
    float x, y;
    v1.getX() > v2.getX() ? x = v1.getX() : x = v2.getX();
    v1.getY() > v2.getY() ? y = v1.getY() : y = v2.getY();
    return Vector2D(x, y);
}

Vector2D Vector2D::Min(Vector2D v1, Vector2D v2) {
    float x, y;
    v1.getX() < v2.getX() ? x = v1.getX() : x = v2.getX();
    v1.getY() < v2.getY() ? y = v1.getY() : y = v2.getY();
    return Vector2D(x, y);
}

Vector2D Vector2D::Multiply(float a, Vector2D v) {
    return Vector2D(a * v.getX(), a * v.getY());
}

Vector2D Vector2D::Multiply(Vector2D v, float a) {
    Multiply(a, v);
}

Vector2D Vector2D::Multiply(Vector2D v1, Vector2D v2) {
    return Vector2D(v1.getX() * v2.getX(), v1.getY() * v2.getY());
}

Vector2D Vector2D::Negate(Vector2D v) {
    return Vector2D(-1 * v.getX(), -1 * v.getY());
}

Vector2D Vector2D::Normalize(Vector2D v) {
    float l = v.Length();
    return Vector2D(v.getX() / l, v.getY() / l);
}

Vector2D Vector2D::Reflect(Vector2D v, Vector2D n) {
    float cos = Dot(v, n);
    float sin = sqrt(1 - pow(cos, 2));
    Vector2D pr(v.getX() * sin, v.getY() * sin);
    return Vector2D(2 * pr.getX() - v.getX(), 2 * pr.getY() - v.getY());
}

Vector2D Vector2D::SquareRoot(Vector2D v) {
    return Vector2D(pow(v.getX(), 2), pow(v.getX(), 2));
}

Vector2D Vector2D::Subtract(Vector2D v1, Vector2D v2) {
    return Vector2D(v1.getX() - v2.getX(), v1.getY() - v2.getY());
}

std::string Vector2D::ToString() {
    return "<" + std::to_string(this->getX()) + "; " + std::to_string(this->getY()) + ">";
}

Vector2D operator+(Vector2D &v1, Vector2D &v2) {
    Vector2D new_v = Vector2D(v1.getX() + v2.getX(), v1.getY() + v2.getY());
    return new_v;
}

Vector2D operator/(Vector2D &v, float a) {
    Vector2D new_v = Vector2D(v.getX() / a, v.getY() / a);
    return new_v;
}

bool operator==(Vector2D &v1, Vector2D &v2) {
    return v1.getX() == v2.getX() and v1.getY() == v2.getY();
}

bool operator!=(Vector2D &v1, Vector2D &v2) {
    return v1.getX() != v2.getX() or v1.getY() != v2.getY();
}

Vector2D operator*(Vector2D &v, float a) {
    Vector2D new_v = Vector2D(v.getX() * a, v.getY() * a);
    return new_v;
}

Vector2D operator*(float a, Vector2D &v) {
    Vector2D new_v = Vector2D(v.getX() * a, v.getY() * a);
    return new_v;
}

Vector2D operator*(Vector2D &v1, Vector2D &v2) {
    Vector2D new_v = Vector2D(v1.getX() * v2.getX(), v1.getY() * v2.getY());
    return new_v;
}

Vector2D operator-(Vector2D &v1, Vector2D &v2) {
    Vector2D new_v = Vector2D(v2.getX() - v1.getX(), v2.getY() - v1.getY());
    return new_v;
}

Vector2D operator-(Vector2D &v) {
    Vector2D new_v = Vector2D(-v.getX(), -v.getY());
    return new_v;
}

