#pragma once

#include "../pre_compiled_header.h"

#include "../point2d.h"

namespace Tobot::Math {
    /// @brief Models a Cicle in 2D space
    template <typename T = float>
        requires ArithmeticFloatingPoint<T>
    class Circle {
        public:
            /// @brief Default constructor
            Circle() = default;

            /// @brief Constructor
            /// @param center Center of the circle
            /// @param radius Radius of the circle
            Circle(const Point2D<T> & center, const T & radius);

            /// @brief Constructor
            /// @param list List of values to initialize the circle
            Circle(const std::initializer_list<T> list);

            /// @brief Copy constructor
            /// @param circle Circle to copy
            Circle(const Circle<T> & circle);

            /// @brief Move constructor
            /// @param circle Circle to move
            Circle(Circle<T> &&) noexcept;

            /// @brief Destructor
            ~Circle() = default;

            /// @brief Copy assignment operator
            /// @param circle Circle to copy
            /// @return Reference to this
            Circle<T> & operator=(const Circle<T> &);

            /// @brief Move assignment operator
            /// @param circle Circle to move
            /// @return Reference to this
            Circle<T> & operator=(Circle<T> &&) noexcept;

            /// @brief Equality operator
            /// @param circle Circle to compare
            /// @return True if equal, false otherwise
            bool operator==(const Circle<T> &) const;

            /// @brief Inequality operator
            /// @param circle Circle to compare
            /// @return True if not equal, false otherwise
            bool operator!=(const Circle<T> &) const;

            /// @brief Less than operator
            /// @param circle Circle to compare
            /// @return True if less than, false otherwise
            bool operator<(const Circle<T> &) const;

            /// @brief Greater than operator
            /// @param circle Circle to compare
            /// @return True if greater than, false otherwise
            bool operator>(const Circle<T> &) const;

            /// @brief Less than or equal operator
            /// @param circle Circle to compare
            /// @return True if less than or equal, false otherwise
            bool operator<=(const Circle<T> &) const;

            /// @brief Greater than or equal operator
            /// @param circle Circle to compare
            /// @return True if greater than or equal, false otherwise
            bool operator>=(const Circle<T> &) const;

            /// @brief Get the center of the circle
            /// @return Center of the circle
            Point2D<T> center() const;

            /// @brief Get the radius of the circle
            /// @return Radius of the circle
            T radius() const;

            /// @brief Set the center of the circle
            /// @param center Center of the circle
            void setCenter(const Point2D<T> &);

            /// @brief Set the radius of the circle
            /// @param radius Radius of the circle
            void setRadius(const T &);

            /// @brief Get the area of the circle
            /// @return Area of the circle
            T getArea() const;

            /// @brief Get the circumference of the circle
            /// @return Circumference of the circle
            T getCircumference() const;

            T getDistance(const Point2D<T> &) const;

            friend std::ostream & operator<<(std::ostream & os, const Circle<T> & circle) {
                os << "Circle: center = " << circle.m_center << ", radius = " << circle.m_radius;
                return os;
            }

        private:
            Point2D<T> m_center;
            T m_radius;
    };

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    Circle<T>::Circle(const Point2D<T> & center, const T & radius) {
        m_center = center;
        m_radius = radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    Circle<T>::Circle(std::initializer_list<T> list) {
        if (list.size() != 3) {
            throw std::invalid_argument("Circle initializer list must have 3 elements");
        }

        auto it = list.begin();
        m_center = Point2D<T>(*it, *(it + 1));
        m_radius = *(it + 2);
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    Circle<T>::Circle(const Circle<T> & circle) {
        m_center = circle.m_center;
        m_radius = circle.m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    Circle<T>::Circle(Circle<T> && circle) noexcept {
        m_center = circle.m_center;
        m_radius = circle.m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    Circle<T> & Circle<T>::operator=(const Circle<T> & circle) {
        m_center = circle.m_center;
        m_radius = circle.m_radius;
        return *this;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    Circle<T> & Circle<T>::operator=(Circle<T> && circle) noexcept {
        m_center = circle.m_center;
        m_radius = circle.m_radius;
        return *this;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T> bool
    Circle<T>::operator==(const Circle<T> & circle) const {
        return (m_center == circle.m_center) && (m_radius == circle.m_radius);
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T> bool
    Circle<T>::operator!=(const Circle<T> & circle) const {
        return (m_center != circle.m_center) || (m_radius != circle.m_radius);
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T> bool
    Circle<T>::operator<(const Circle<T> & circle) const {
        return m_radius < circle.m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T> bool
    Circle<T>::operator>(const Circle<T> & circle) const {
        return m_radius > circle.m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T> bool
    Circle<T>::operator<=(const Circle<T> & circle) const {
        return m_radius <= circle.m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T> bool
    Circle<T>::operator>=(const Circle<T> & circle) const {
        return m_radius >= circle.m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    Point2D<T> Circle<T>::center() const {
        return m_center;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    T Circle<T>::radius() const {
        return m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    void Circle<T>::setCenter(const Point2D<T> & center) {
        m_center = center;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    void Circle<T>::setRadius(const T & radius) {
        m_radius = radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    T Circle<T>::getArea() const {
        // Area of a circle is pi * radius^2
        return MATH_PI * pow(m_radius, 2);
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    T Circle<T>::getCircumference() const {
        // Circumference of a circle is 2 * pi * radius
        return 2 * MATH_PI * m_radius;
    }

    template <typename T>
        requires ArithmeticFloatingPoint<T>
    T Circle<T>::getDistance(const Point2D<T> & point) const {
        // Distance between the points subtracted by the radius of the circle
        // will give the distance from the point to the circle
        return m_center.distance(point) - m_radius;
    }

} // namespace Tobot::Math
