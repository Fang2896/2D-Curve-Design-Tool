//
// Created by fangl on 2023/8/31.
//

#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <QVector3D>
#include <utility>


class Point
{
public:
    Point(const QVector3D& position, QColor color, float size)
        : id(nextID++) ,m_position(position), m_color(std::move(color)), m_size(size) { }

    explicit Point(const QVector3D& position)
        : id(nextID++), m_position(position)
    {
        m_color = Qt::white;
        m_size = 0.1f;
    }

    int getID() const {
        return id;
    }

    // getter and setter for position
    QVector3D position() const { return m_position; }
    void setPosition(const QVector3D& position) { m_position = position; }

    // getter and setter for color
    QColor color() const { return m_color; }
    void setColor(const QColor& color) { m_color = color; }

    // getter and setter for size
    float size() const { return m_size; }
    void setSize(float size) { m_size = size; }

    bool operator==(const Point& other) const {
        return id == other.id;
    }

private:
    int id;
    static int nextID;

    QVector3D m_position;
    QColor m_color;
    float m_size;   // display size
};


#endif //POINT_H
